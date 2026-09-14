"""Reproduce the post-validation findings from pinned files. No hardware access.

Run fetch_firmware.py and analyze_firmware.py first. This is a targeted static
check, not a simulator of the steering controller or a compatibility test.
"""
from pathlib import Path
import hashlib
import json
import struct

ROOT = Path(__file__).resolve().parent
EXPECTED = {
    'NB3C-14D003-AB_block0_0x10040000.bin': (0x40000, 'e0af7983c2650b097cbdfd8ca5ecff776dc5b1452e94394cfb155db9f230a767'),
    'NB3C-14D004-AD_block0_0x101C0000.bin': (0x1c0000, '3f97fcdb806282eee759531d9700a3d681f79750ba74f40083a474e4076c2bab'),
    'NB3C-14D007-AAB_block0_0x101D0000.bin': (0x1d0000, 'f6054e402a5b61073418b263848de24a3bbd9b3b73a4ecf1370297957699be74'),
}


def main():
    images = []
    provenance = []
    for name, (base, digest) in EXPECTED.items():
        data = (ROOT / 'results' / name).read_bytes()
        actual = hashlib.sha256(data).hexdigest()
        if actual != digest:
            raise ValueError(f'Unexpected firmware hash: {name}')
        images.append((base, data))
        provenance.append({'file': name, 'cpu_base': hex(base), 'sha256': actual})

    def read(address, length):
        for base, data in images:
            offset = address - base
            if 0 <= offset and offset + length <= len(data):
                return data[offset:offset + length]
        raise ValueError(f'Unmapped static read: {address:#x}+{length:#x}')

    def u32(address):
        return struct.unpack('<I', read(address, 4))[0]

    # These instruction bytes anchor the initialization-table layout and bounds.
    anchors = {
        0x40098: '87ffda85',       # JARL initialization routine 0xb8672
        0xb86a2: '3b0630bf1100',   # table start
        0xb86a8: '3c06e4cb1100',   # table end
        0xb86ba: '0035',           # destination word at +0
        0xb86bc: '023d',           # source word at +4
        0xb86be: '7440',           # length halfword at +8
        0xb86c0: '82ff8059',       # JARL copy routine 0xde040
        0xb86c4: '4cea',           # next 12-byte record
        0xbd0d8: 'a407d54fdcfd',   # exported LMC2 validity byte
        0xbd0e2: '8a560002',       # validity summary bit 0x200
    }
    for address, raw in anchors.items():
        assert read(address, len(bytes.fromhex(raw))) == bytes.fromhex(raw), hex(address)

    records = []
    for address in range(0x11bf30, 0x11cbe4, 12):
        dest, src = struct.unpack('<II', read(address, 8))
        length = struct.unpack('<H', read(address + 8, 2))[0]
        records.append((address, dest, src, length))
    assert len(records) == 271

    def initialized(address, size):
        """Last covering copy, in the order used by the initializer."""
        matches = [r for r in records if r[1] <= address and address + size <= r[1] + r[3]]
        if not matches:
            raise ValueError(f'No initialization copy covers {address:#x}')
        record, dest, src, length = matches[-1]
        source = src + address - dest
        value = int.from_bytes(read(source, size), 'little')
        return {'ram': hex(address), 'size': size, 'copy_record': hex(record),
                'source_cpu': hex(source), 'value': value, 'value_hex': hex(value)}

    flag = initialized(0xfef23886, 1)
    expected_code = initialized(0xfef23887, 1)
    input_code = initialized(0xfebf6b0e, 1)
    assert (flag['value'], expected_code['value'], input_code['value']) == (0, 1, 1)
    selected = flag['value'] != 0 or input_code['value'] == expected_code['value']
    assert selected

    def gp_getter(address, op):
        raw = read(address, 8)
        first, second, upper = struct.unpack('<HHh', raw[:6])
        assert first == 0x7a4 and raw[6:] == b'\x7f\x00'
        assert second >> 11 == 10
        if op == 'ld.bu':
            assert second & 15 == 5
        else:
            assert second & 31 == 7
        disp = (upper << 7) | ((second >> 4) & 127)
        return {'function': hex(address), 'ram': hex((0xfebffe7c + disp) & 0xffffffff),
                'operation': op, 'raw_hex': raw.hex()}

    getters = {name: gp_getter(address, op) for name, address, op in [
        ('selector_code', 0xbd486, 'ld.bu'), ('request_mode', 0xbd56e, 'ld.bu'),
        ('additional_lmc2_flag', 0xbd54e, 'ld.bu'), ('curvature_rate_raw', 0xbd516, 'ld.hu'),
        ('curvature_raw', 0xbd526, 'ld.hu'), ('offset_raw', 0xbd52e, 'ld.hu'),
        ('heading_raw', 0xbd536, 'ld.hu'), ('alternate_rate_raw', 0xbd51e, 'ld.hu'),
        ('alternate_request', 0xbd576, 'ld.bu'),
    ]}
    assert getters['request_mode']['ram'] == '0xfebeecfc'
    assert getters['selector_code']['ram'] == '0xfebf6b0e'

    # Independent field extraction for the two audited ST.W disp23 instructions.
    stores = []
    for address, expected_reg in [(0xd0910, 7), (0xd0cac, 18)]:
        raw = read(address, 6)
        first, second, upper = struct.unpack('<HHh', raw)
        assert first >> 5 == 0x3c and first & 31 == 4 and second & 31 == 15
        disp = (upper << 7) | (((second >> 5) & 63) << 1)
        assert second >> 11 == expected_reg and disp == -0x118ac
        stores.append({'instruction': hex(address), 'raw_hex': raw.hex(),
                       'source_register': expected_reg, 'destination': '0xfebee5d0',
                       'architectural_store_bytes': 4})

    directory = list(struct.unpack('<48I', read(0x4be4c, 192)))
    variants = []
    for i in range(18):
        address = 0x4c690 + i * 8
        source, dest, size, mode = struct.unpack('<HHHB', read(address, 7))
        variants.append({'record': hex(address), 'mode': mode, 'source_slot': source,
                         'destination_slot': dest, 'size_field': size,
                         'source_rom_pointer': hex(directory[source])})
    assert {r['destination_slot'] for r in variants} == {2, 31, 42}
    overrides = []
    for i in range(9):
        address = 0x4c720 + i * 12
        pointer, size, dest, selection = struct.unpack('<IHHB', read(address, 9))
        overrides.append({'record': hex(address), 'pointer': hex(pointer), 'size_field': size,
                          'destination_slot': dest, 'selection_code': selection})
    slot27 = [r for r in overrides if r['destination_slot'] == 27]
    assert len(slot27) == 1 and slot27[0]['pointer'] == '0xfeed8004'

    # Renesas manual: CVTF.ULD and DIVF.D, despite Ghidra's printed .S mnemonics.
    cvt = struct.unpack('<HH', read(0xb7754, 4))
    div = struct.unpack('<HH', read(0xb7762, 4))
    assert cvt == (0xe7f1, 0x5452) and div == (0x57e8, 0x847e)
    divisor = struct.unpack('<d', struct.pack('<II', 0, 0x40bf4000))[0]
    assert divisor == 8000.0

    masks = [initialized(a, 4) for a in [0xfef23860, 0xfef23868, 0xfef2386c, 0xfef23870, 0xfef2461c]]
    for row in masks:
        row['includes_lmc2_validity_bit_9'] = bool(row['value'] & 0x200)
    result = {
        'date': '2026-09-14', 'scope': 'Pinned public sample; static bytes and targeted virtual checks only',
        'firmware': provenance,
        'initialization': {'startup_call': '0x40098', 'initializer': '0xb8672', 'copy_function': '0xde040',
                           'record_count': len(records), 'record_bytes': 12,
                           'selected_records': [{'record': hex(a), 'destination': hex(d), 'source': hex(s), 'length': n}
                                                for a, d, s, n in records if a in (0x11c068, 0x11cbb4, 0x11cbc0)]},
        'source_selection': {'function': '0xf3e34', 'condition': 'flag != 0 OR input_code == expected_code',
                             'flag': flag, 'expected_code': expected_code, 'input_code': input_code,
                             'startup_default_selects_lmc2': selected, 'lmc2_branch': '0xf3ea0',
                             'alternate_branch': '0xf3e80',
                             'limit': 'Input-source selection only; no steering permission or runtime immutability claim'},
        'getters': getters,
        'validity_summary': {'function': '0xbd05c', 'lmc2_source': '0xfebeecf9', 'bit': 9,
                             'mask': '0x200', 'application_mask_defaults': masks},
        'calibration_directory': {'active_pointer': '0xfebee5d0', 'rom_default_directory': '0x4be4c',
                                  'ram_banks': ['0xfebf62c4', '0xfebf6388'], 'bank_bytes': 196,
                                  'slot_27_rom_pointer': hex(directory[27]), 'variant_records': variants,
                                  'ram_override_records': overrides,
                                  'limit': 'The 18-row selector leaves slot 27 alone; a separate guarded RAM override can replace it. Actual runtime state unknown.'},
        'stw_instructions': stores,
        'timestamp': {'function': '0xb773c', 'counter_addresses': ['0xffdd8040', '0xffdd8044'],
                      'conversion_cpu': '0xb7754', 'architectural_conversion': 'CVTF.ULD',
                      'division_cpu': '0xb7762', 'architectural_division': 'DIVF.D', 'divisor': divisor,
                      'limit': 'Counter frequency unresolved; no physical timeout unit established'},
    }
    out = ROOT / 'results/followup'
    out.mkdir(parents=True, exist_ok=True)
    (out / 'static_findings.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({'firmware_hashes_pass': len(images), 'initialization_records': len(records),
                      'startup_default_selects_lmc2': selected, 'getter_bodies_checked': len(getters),
                      'lmc2_validity_summary_bit': 9, 'stw_instructions_checked': len(stores),
                      'timestamp_divisor': divisor}, indent=2))


if __name__ == '__main__':
    main()
