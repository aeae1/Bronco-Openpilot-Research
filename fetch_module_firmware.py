"""Retrieve pinned public comparison files. No vehicle or diagnostic interface."""

import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import re
from urllib.request import Request, urlopen

ROOT = Path(__file__).resolve().parent
MANIFEST = ROOT / 'module_firmware_manifest.json'


def verify_bytes(data, entry):
    actual = {
        'bytes': len(data),
        'sha256': hashlib.sha256(data).hexdigest(),
        'git_blob_sha1': hashlib.sha1(
            b'blob ' + str(len(data)).encode() + b'\0' + data
        ).hexdigest(),
    }
    for key, value in actual.items():
        if value != entry[key]:
            raise ValueError(f"{entry['filename']}: {key} mismatch")
    return actual


def retrieve(entry, verify_only=False):
    path = (ROOT / entry['local_path']).resolve()
    if not path.is_relative_to((ROOT / 'sources').resolve()):
        raise ValueError('Comparison downloads must stay under sources/')
    revision = entry['source_revision']
    if not re.fullmatch(r'[0-9a-f]{40}', revision):
        raise ValueError('An immutable source revision is required')
    expected_url = (
        'https://raw.githubusercontent.com/ghostdev137/ford-pscm-re/'
        + revision + '/' + entry['source_path']
    )
    if entry['url'] != expected_url:
        raise ValueError('Unexpected source URL')
    downloaded = False
    if path.exists():
        data = path.read_bytes()
    elif verify_only:
        raise FileNotFoundError(path)
    else:
        req = Request(entry['url'], headers={
            'User-Agent': 'Bronco-Openpilot-Research/offline-file-retrieval'
        })
        with urlopen(req, timeout=30) as response:
            data = response.read(entry['bytes'] + 1)
        verify_bytes(data, entry)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        downloaded = True
    result = verify_bytes(data, entry)
    return {'filename': entry['filename'], 'downloaded': downloaded, **result}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--verify-only', action='store_true',
                        help='Check existing files without network access')
    args = parser.parse_args()
    entries = json.loads(MANIFEST.read_text())['files']
    with ThreadPoolExecutor(max_workers=4) as pool:
        results = list(pool.map(lambda e: retrieve(e, args.verify_only), entries))
    print(json.dumps({'verified_files': len(results), 'files': results}, indent=2))


if __name__ == '__main__':
    main()
