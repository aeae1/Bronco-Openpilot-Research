"""Retrieve pinned, hash-checked public source for an offline comparison."""

from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import urllib.request

ROOT = Path(__file__).resolve().parent


def fetch(item):
    target = ROOT / item['file']
    data = (target.read_bytes() if target.exists()
            else urllib.request.urlopen(item['url'], timeout=45).read())
    if len(data) != item['bytes'] or hashlib.sha256(data).hexdigest() != item['sha256']:
        raise ValueError('Source integrity mismatch: ' + item['file'])
    target.parent.mkdir(parents=True, exist_ok=True)
    if not target.exists():
        target.write_bytes(data)
    return item['file']


def main():
    manifest = json.loads((ROOT / 'results/port_source_manifest.json').read_text())
    with ThreadPoolExecutor(max_workers=6) as pool:
        verified = list(pool.map(fetch, manifest))
    print(f'Verified {len(verified)} pinned source files. The expected-hash manifest was preserved.')


if __name__ == '__main__':
    main()
