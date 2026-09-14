"""Offline comparison: firmware routine 0x74904 versus pinned openpilot code.

No vehicle interface, CAN transmission, or firmware mutation. The small interpreter
executes the straight-line instruction listing exported by Ghidra. Instruction
semantics used here are basic V850 integer, load, and store operations.
"""
from pathlib import Path
import ast,hashlib,json,random,re,struct
ROOT=Path(__file__).resolve().parent

def upstream_function():
 source=(ROOT/'sources/upstream/opendbc/car/ford/fordcan.py').read_text()
 fn=next(n for n in ast.parse(source).body if isinstance(n,ast.FunctionDef) and n.name=='calculate_lat_ctl2_checksum')
 ns={};exec(compile(ast.Module(body=[fn],type_ignores=[]),'pinned_checksum','exec'),ns)
 return ns[fn.name]

def firmware_function(curvature,rate,offset,mode,counter,angle):
 regs={f'r{i}':0 for i in range(32)}
 aliases={'sp':'r3','gp':'r4','tp':'r5','ep':'r30','lp':'r31'}
 def name(r):return aliases.get(r,r)
 def get(r):return regs[name(r)] if name(r) in regs else int(r,0)
 def put(r,v):
  if name(r)!='r0':regs[name(r)]=v&0xffffffff
 regs.update(r3=0x1000,r6=curvature,r7=rate,r8=offset,r9=mode)
 mem=bytearray(0x3000)
 struct.pack_into('<III',mem,0x1000,counter,angle,0x2000)
 for line in (ROOT/'results/ghidra/74904.asm').read_text().splitlines():
  _,text=line.split('  ',1);op,args=text.split(' ',1);args=[v.strip() for v in args.split(',')]
  if op=='jmp':break
  if op=='mov':put(args[1],get(args[0]))
  elif op=='shr':put(args[1],get(args[1])>>get(args[0]))
  elif op=='add':put(args[1],get(args[1])+get(args[0]))
  elif op=='andi':put(args[2],get(args[0])&get(args[1]))
  elif op=='not':put(args[1],~get(args[0]))
  elif op=='zxb':put(args[0],get(args[0])&255)
  elif op in ['sld.hu','sld.w']:
   m=re.fullmatch(r'(0x[0-9a-f]+)\[(\w+)\]',args[0]);a=int(m[1],16)+get(m[2])
   put(args[1],struct.unpack_from('<H' if op=='sld.hu' else '<I',mem,a)[0])
  elif op=='sst.h':
   m=re.fullmatch(r'(0x[0-9a-f]+)\[(\w+)\]',args[1]);a=int(m[1],16)+get(m[2]);struct.pack_into('<H',mem,a,get(args[0])&65535)
  else:raise ValueError('Unimplemented instruction '+text)
 return struct.unpack_from('<H',mem,0x2000)[0]

def bytes_for_fields(c,r,o,m,n,a):
 # Synthetic payload solely for comparing the checksum's input extraction.
 return bytearray([m<<4,0,c>>3,((c&7)<<5)|(a>>6),((a&63)<<2)|(o>>8),o&255,r>>3,((r&7)<<5)|(n<<1)])

def main():
 fn=upstream_function();rng=random.Random(20260914)
 edges=[(c,r,o,m,n,a) for m in range(8) for n in range(16)
        for c,r,o,a in [(0,0,0,0),(2047,2047,1023,2047),(0,2047,0,2047),(2047,0,1023,0),(1000,1024,512,1000)]]
 cases=edges+[(rng.randrange(2048),rng.randrange(2048),rng.randrange(1024),rng.randrange(8),rng.randrange(16),rng.randrange(2048)) for _ in range(10000)]
 for fields in cases:
  c,r,o,m,n,a=fields
  expected=fn(m,n,bytes_for_fields(*fields));actual=firmware_function(*fields)
  assert expected==actual,(fields,expected,actual)
 result={'firmware_function_cpu':'0x74904','instruction_listing_sha256':hashlib.sha256((ROOT/'results/ghidra/74904.asm').read_bytes()).hexdigest(),'upstream_revision':'057aee25b5eee7530f0b95b5b508c8c3247b0cd7','cases':len(cases),'edge_cases':len(edges),'seed':20260914,'mismatches':0,'scope':'Integer checksum arithmetic and input-field extraction only. Does not emulate the vehicle, timing, steering application, or safety limits.'}
 (ROOT/'results/checksum_comparison.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))
if __name__=='__main__':main()
