"""Correct one Ghidra 12.1.3 analysis definition. Does not open or modify firmware.

Use only on a dedicated analysis installation. Requires its JDK on PATH/JAVA_HOME.
The original source and compiled language are retained beside the patched files.
"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

EXPECTED = '0aa96a8c2e1fc7ba595eb9a67da6299749f81ba5495e549b70a3a8d0bc7e38db'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('ghidra', type=Path)
    parser.add_argument('--report', type=Path, required=True)
    args = parser.parse_args()
    root = args.ghidra.resolve()
    lang = root / 'Ghidra/Processors/V850/data/languages'
    source = lang / 'V850_instructions.sinc'
    compiled = lang / 'V850e3.sla'
    original = source.read_bytes()
    if sha(original) != EXPECTED:
        raise SystemExit('Source hash differs from the audited stock file; refusing to change it.')
    marker = b'# ST.W reg3, disp23[reg1]'
    start = original.index(marker)
    end = original.index(b'\n}', start) + 2
    block = original[start:end]
    old = b'\t*:2 adr = tmp:2;'
    if block.count(old) != 1:
        raise SystemExit('Expected exactly one audited ST.W statement.')
    changed = original[:start] + block.replace(old, b'\t*:4 adr = tmp;') + original[end:]
    old_sla = compiled.read_bytes()
    for file, data in ((source, original), (compiled, old_sla)):
        backup = file.with_name(file.name + '.bronco-original')
        with backup.open('xb') as stream:
            stream.write(data)
    source.write_bytes(changed)
    try:
        subprocess.run([str(root / 'support/sleigh'), str(lang / 'V850e3.slaspec')], check=True)
    except BaseException:
        source.write_bytes(original)
        compiled.write_bytes(old_sla)
        raise
    report = {
        'scope': 'Ghidra analysis language only; no firmware change',
        'source': 'Ghidra/Processors/V850/data/languages/V850_instructions.sinc',
        'source_original_sha256': sha(original),
        'source_corrected_sha256': sha(changed),
        'compiled_original_sha256': sha(old_sla),
        'compiled_corrected_sha256': sha(compiled.read_bytes()),
        'change': 'ST.W reg3, disp23[reg1]: 16-bit store changed to 32-bit store',
        'architecture_reference': 'Renesas R01US0123EJ0140 Rev.1.40, page 314',
    }
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
