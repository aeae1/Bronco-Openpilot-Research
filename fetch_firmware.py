"""Retrieve pinned, hash-checked public files for offline analysis only."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import hashlib,json,urllib.request
ROOT=Path(__file__).resolve().parent

def main():
 manifest=json.loads((ROOT/'firmware_download_manifest.json').read_text())
 def fetch(item):
  url=f"https://raw.githubusercontent.com/{manifest['repository']}/{manifest['revision']}/{item['source_path']}"
  target=ROOT/item['local_path'];target.parent.mkdir(parents=True,exist_ok=True)
  data=target.read_bytes() if target.exists() else urllib.request.urlopen(url,timeout=60).read()
  actual=hashlib.sha256(data).hexdigest()
  if actual!=item['sha256']:raise ValueError('SHA-256 mismatch: '+item['local_path'])
  if not target.exists():target.write_bytes(data)
  return {'file':item['local_path'],'url':url,'bytes':len(data),'sha256':actual}
 with ThreadPoolExecutor(max_workers=4) as pool:results=list(pool.map(fetch,manifest['files']))
 (ROOT/'results').mkdir(exist_ok=True)
 (ROOT/'results/firmware_downloads_verified.json').write_text(json.dumps(results,indent=2)+'\n')
 print(f'Verified {len(results)} pinned files. No firmware was modified or sent to a device.')
if __name__=='__main__':main()
