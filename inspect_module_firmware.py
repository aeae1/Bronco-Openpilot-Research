"""Inspect local, hash-pinned comparison files; never execute or change firmware."""

import binascii
import hashlib
import json
from pathlib import Path
import re
import struct
from xml.etree import ElementTree
import zlib

from fetch_module_firmware import ROOT, MANIFEST, verify_bytes


def vbf_header_end(raw):
    if not re.match(rb'vbf_version\s*=\s*[0-9.]+;', raw):
        raise ValueError('Not a VBF container')
    match = re.search(rb'\bheader\s*\{', raw)
    if match is None:
        raise ValueError('Missing VBF header')
    start = match.end() - 1
    depth = 0
    quoted = escaped = comment = False
    for i in range(start, len(raw)):
        char = raw[i]
        if comment:
            if char == 10:
                comment = False
            continue
        if quoted:
            if escaped:
                escaped = False
            elif char == 92:
                escaped = True
            elif char == 34:
                quoted = False
            continue
        if raw[i:i + 2] == b'//':
            comment = True
            continue
        if char == 34:
            quoted = True
        elif char == 123:
            depth += 1
        elif char == 125:
            depth -= 1
            if depth == 0:
                return i + 1
    raise ValueError('Unterminated VBF header')


def inspect_vbf(raw):
    end = vbf_header_end(raw)
    header = raw[:end].decode('latin1')
    # Ignore line comments when looking up field values.
    fields_text = re.sub(r'//[^\n]*', '', header)

    def field(name):
        match = re.search(r'\b' + name + r'\s*=\s*([^;]+);', fields_text)
        if match is None:
            raise ValueError(f'Missing VBF field: {name}')
        return match.group(1).strip()

    format_id = int(field('data_format_identifier'), 0)
    if format_id != 0:
        raise ValueError('Only the pinned, uncompressed VBF format is supported')
    blocks = []
    pos = end
    while pos < len(raw):
        if len(raw) - pos < 10:
            raise ValueError('Truncated VBF block header or CRC')
        address, size = struct.unpack_from('>II', raw, pos)
        if size == 0 or pos + size + 10 > len(raw):
            raise ValueError('Invalid VBF block length')
        data = raw[pos + 8:pos + 8 + size]
        stored_crc = struct.unpack_from('>H', raw, pos + 8 + size)[0]
        actual_crc = binascii.crc_hqx(data, 0xffff)
        if stored_crc != actual_crc:
            raise ValueError('VBF block CRC mismatch')
        blocks.append({
            'address': f'0x{address:08X}', 'bytes': size,
            'crc16_stored': f'0x{stored_crc:04X}',
            'crc16_computed': f'0x{actual_crc:04X}',
            'crc16_matches': True,
            'sha256': hashlib.sha256(data).hexdigest(),
        })
        pos += size + 10
    if not blocks:
        raise ValueError('VBF contains no blocks')
    stored_file_crc = int(field('file_checksum'), 0)
    actual_file_crc = zlib.crc32(raw[end:])
    if stored_file_crc != actual_file_crc:
        raise ValueError('VBF file CRC mismatch')
    return {
        'kind': 'vbf', 'header_bytes': end,
        'software_part_number': field('sw_part_number').strip('"'),
        'software_part_type': field('sw_part_type'),
        'description_lines': re.findall(r'"([^"\r\n]*)"', field('description')),
        'ecu_address': field('ecu_address'),
        'frame_format': field('frame_format'),
        'data_format_identifier': format_id,
        'file_crc32_stored': f'0x{stored_file_crc:08X}',
        'file_crc32_computed': f'0x{actual_file_crc:08X}',
        'file_crc32_matches': True, 'blocks': blocks,
        'cryptographic_signature_verified': False,
    }


def inspect_mdx(raw):
    root = ElementTree.fromstring(raw)
    if root.tag != 'MDX':
        raise ValueError('Expected an MDX diagnostic-definition document')
    identity_fields = []
    for did in root.iter('DID'):
        if did.get('ID') not in {
            'did_F111', 'did_F113', 'did_F124', 'did_F187', 'did_F188', 'did_F191'
        }:
            continue
        identity_fields.append({
            'identifier': '0x' + did.get('ID').split('_')[1],
            'label': did.findtext('NAME'),
            'bytes': int(did.findtext('BYTE_SIZE')),
        })
    return {
        'kind': 'diagnostic_definition',
        'mdx_uid': root.get('uid'), 'mdx_version': root.get('VERSION'),
        'did_definition_count': sum(1 for _ in root.iter('DID')),
        'identity_field_definitions': identity_fields,
        'limits': 'Definitions, not responses from a vehicle; not executable firmware.',
    }


def main():
    manifest = json.loads(MANIFEST.read_text())
    reports = []
    for entry in manifest['files']:
        raw = (ROOT / entry['local_path']).read_bytes()
        integrity = verify_bytes(raw, entry)
        details = inspect_vbf(raw) if entry['kind'] == 'vbf' else inspect_mdx(raw)
        reports.append({
            'filename': entry['filename'], 'module': entry['module'],
            'source_vehicle_attribution': entry['source_vehicle_attribution'],
            'owner_vehicle_match': entry['owner_vehicle_match'],
            'source_url': entry['url'], **integrity, **details,
        })
    vbfs = [r for r in reports if r['kind'] == 'vbf']
    report = {
        'research_date': manifest['research_date'],
        'summary': {
            'files': len(reports), 'vbf_containers': len(vbfs),
            'vbf_blocks': sum(len(r['blocks']) for r in vbfs),
            'all_pinned_hashes_match': True, 'all_vbf_checksums_match': True,
            'gateway_executable_acquired': False,
            'owner_module_firmware_match_established': False,
        },
        'limits': 'Integrity checks do not authenticate Ford signatures, identify the owner\'s installed software, or establish vehicle behavior or safety.',
        'files': reports,
    }
    target = ROOT / 'results/module_firmware_inventory.json'
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report['summary'], indent=2))


if __name__ == '__main__':
    main()
