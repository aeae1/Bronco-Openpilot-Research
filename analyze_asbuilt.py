"""Extract only non-unique module part identifiers from a local Ford As-Built XML.

The output excludes VINs, serials, manufacturing codes, raw configuration data,
the input filename, and the input-file hash. It never connects to a vehicle.
"""

import argparse
import json
from pathlib import Path
import re
from xml.etree import ElementTree

MODULES = {'706': 'IPMA', '716': 'GWM', '730': 'PSCM'}
LABELS = {
    'F10A': 'ECU Cal-Config Part Number',
    'F110': 'Subsystem Specific Diagnostic Specification Part Number',
    'F111': 'ECU Core Assembly Number',
    'F113': 'ECU Delivery Assembly Number',
    'F120': 'ECU Software #2 Part Number',
    'F124': 'ECU Calibration Data #1 Number',
    'F125': 'ECU Calibration Data #2 Number',
    'F16B': 'ECU Cal-Config #2 Part Number',
    'F16C': 'ECU Cal-Config #3 Part Number',
    'F188': 'Vehicle Manufacturer ECU Software Number',
}
PART_NUMBER = re.compile(r'(?:DS)?[A-Z0-9]{4}-[A-Z0-9]{5,6}-[A-Z0-9]{1,5}')
PROGRAM_FIELDS = {'F188', 'F120'}
DATA_FIELDS = {'F10A', 'F124', 'F125', 'F16B', 'F16C'}


def extract(raw):
    root = ElementTree.fromstring(raw)
    if root.tag != 'AS_BUILT_DATA':
        raise ValueError('Expected a Ford AS_BUILT_DATA XML document')
    records = {}
    for node in root.iter('NODEID'):
        address = (node.text or '').strip().upper()
        if address not in MODULES:
            continue
        if address in records:
            raise ValueError(f'Duplicate target module node: {address}')
        fields = []
        seen = set()
        for child in node:
            if child.tag not in LABELS:
                continue
            if child.tag in seen:
                raise ValueError(f'Duplicate identification field in {address}')
            seen.add(child.tag)
            value = (child.text or '').strip()
            if not PART_NUMBER.fullmatch(value):
                # Fail without printing unexpected input, which might be private.
                raise ValueError(f'Unrecognized part-number format in {address}/{child.tag}')
            fields.append({
                'did': '0x' + child.tag,
                'label': LABELS[child.tag],
                'part_number': value,
                'placeholder': value.startswith('XXXX-'),
            })
        records[address] = {
            'module': MODULES[address], 'node': '0x' + address,
            'identification': fields,
        }
    missing = set(MODULES) - set(records)
    if missing:
        raise ValueError('Missing target modules: ' + ', '.join(sorted(missing)))

    candidates = []
    for address in ('716', '730', '706'):
        for field in records[address]['identification']:
            tag = field['did'][2:]
            if field['placeholder'] or tag not in PROGRAM_FIELDS | DATA_FIELDS:
                continue
            candidates.append({
                'module': MODULES[address], 'source_did': field['did'],
                'part_number': field['part_number'],
                'role': 'software' if tag in PROGRAM_FIELDS else 'calibration/configuration',
                'vbf_filename_candidate': field['part_number'] + '.VBF',
                'download_verified': False,
            })

    return {
        'source_type': 'Owner-supplied Ford As-Built server record',
        'live_vehicle_read': False,
        'module_nodes_in_file': sum(1 for _ in root.iter('NODEID')),
        'configuration_data_rows_in_file': sum(1 for _ in root.iter('DATA')),
        'label_basis': 'Common Ford DID labels cross-checked against public MDX references; original DID values are preserved.',
        'modules': [records[a] for a in ('716', '730', '706')],
        'firmware_search_candidates': candidates,
        'limits': [
            'The record does not prove which software or hardware is currently installed.',
            'As-Built configuration and identification are not executable firmware.',
            'VBF names are search candidates; package availability and filenames are unverified.',
            'The placeholder XXXX-14H525-XXX is excluded from firmware requests.',
        ],
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('input', type=Path)
    parser.add_argument('--output', type=Path, required=True,
                        help='Destination for the sanitized identification JSON')
    args = parser.parse_args()
    if args.input.resolve() == args.output.resolve():
        raise ValueError('The output must not overwrite the source record')
    result = extract(args.input.read_bytes())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps({
        'target_modules': len(result['modules']),
        'firmware_search_candidates': len(result['firmware_search_candidates']),
        'live_vehicle_read': False,
    }, indent=2))


if __name__ == '__main__':
    main()
