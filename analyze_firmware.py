"""Read-only structural analysis of the public Bronco firmware. Never flashes or patches."""
from pathlib import Path
import binascii, collections, hashlib, json, re, struct

ROOT = Path(__file__).resolve().parent
OUT = ROOT/'results'
OUT.mkdir(exist_ok=True)
BASE = 0x10040000

def git_hash(data):
 return hashlib.sha1(b'blob '+str(len(data)).encode()+b'\x00'+data).hexdigest()

def parse_vbf(path):
 raw=path.read_bytes()
 start=raw.index(b'{',raw.index(b'header'))
 depth=0; quoted=False; escaped=False; comment=False
 end=None
 for i in range(start,len(raw)):
  c=raw[i]
  if comment:
   if c==10: comment=False
   continue
  if quoted:
   if escaped: escaped=False
   elif c==92: escaped=True
   elif c==34: quoted=False
   continue
  if raw[i:i+2]==b'//': comment=True; continue
  if c==34: quoted=True
  elif c==123: depth+=1
  elif c==125:
   depth-=1
   if depth==0: end=i+1; break
 assert end is not None
 header=raw[:end].decode('latin1')
 assert int(re.search(r'data_format_identifier\s*=\s*(0x[0-9a-fA-F]+)',header).group(1),16)==0, 'Only uncompressed VBF supported'
 p=end; blocks=[]
 while p<len(raw):
  assert len(raw)-p>=10
  addr,n=struct.unpack_from('>II',raw,p)
  assert n>0 and p+10+n<=len(raw)
  b=raw[p+8:p+8+n]
  crc=struct.unpack_from('>H',raw,p+8+n)[0]
  actual=binascii.crc_hqx(b,0xffff)
  assert crc==actual, f'Block CRC mismatch in {path.name} at {addr:#x}'
  target=OUT/f'{path.stem}_block{len(blocks)}_0x{addr:08X}.bin'
  target.write_bytes(b)
  blocks.append({'address':hex(addr),'length':n,'crc16_stored':hex(crc),'crc16_computed':hex(actual),'crc16_matches':crc==actual,'sha256':hashlib.sha256(b).hexdigest(),'git_blob_sha1':git_hash(b),'local_file':target.name})
  p+=10+n
 return {'file':str(path.relative_to(ROOT)),'bytes':len(raw),'git_blob_sha1':git_hash(raw),'sha256':hashlib.sha256(raw).hexdigest(),'header':header,'blocks':blocks}

def all_hits(b,needle):
 return [m.start() for m in re.finditer(re.escape(needle),b)]

def main():
 files=[ROOT/'sources/firmware/Bronco_6G/NB3C-14D003-AB.VBF',ROOT/'inputs/NB3C-14D004-AD.VBF',ROOT/'inputs/NB3C-14D007-AAB.VBF']
 manifest=[parse_vbf(p) for p in files]
 b=(OUT/manifest[0]['blocks'][0]['local_file']).read_bytes()
 assert b==(ROOT/'inputs/NB3C-14D003-AB_block0_0x10040000.bin').read_bytes()
 published_tables=[]
 for off in [0x12a8,0x1590]:
  rows=[]
  for j in range(47):
   word,can,mask=struct.unpack_from('<III',b,off+12*j)
   rows.append({'index':j,'address':hex(BASE+off+12*j),'packed_word':hex(word),'can_id':hex(can),'mask':hex(mask),'first_word_bytes':list(b[off+12*j:off+12*j+4])})
  published_tables.append({'address':hex(BASE+off),'records':rows})
 published_diff=[{'index':a['index'],'a':a,'b':bb} for a,bb in zip(published_tables[0]['records'],published_tables[1]['records']) if (a['packed_word'],a['can_id'],a['mask'])!=(bb['packed_word'],bb['can_id'],bb['mask'])]
 tables=[]
 for off in [0x11f8,0x14e0]:
  rows=[]
  for j in range(62):
   pos=off+12*j
   can,mask,meta=struct.unpack_from('<III',b,pos)
   rows.append({'index':j,'vbf_address':hex(BASE+pos),'cpu_address':hex(0x40000+pos),'raw_hex':b[pos:pos+12].hex(' '),'can_id':hex(can),'mask_and_search_flags':hex(mask),'packed_metadata':hex(meta),'upper_layer_pdu_id':b[pos+8],'minimum_length':b[pos+9]&0x7f,'callback_index':b[pos+10],'frame_type_filter':b[pos+11]})
  tables.append({'cpu_address':hex(0x40000+off),'records':rows})
 diff=[{'index':a['index'],'a':a,'b':bb} for a,bb in zip(tables[0]['records'],tables[1]['records']) if a['raw_hex']!=bb['raw_hex']]
 def rd(addr,n):return b[addr-0x40000:addr-0x40000+n]
 lmc2_routes=[]
 for row in tables[0]['records']:
  if row['can_id'] not in ['0x3d6','0x3ca','0x3d7','0x230']:continue
  pdu=row['upper_layer_pdu_id'];route=rd(0x4b2f7+pdu*5,1)[0]
  meta=rd(0x4b088+route*3,3);dest=rd(0x4b170+meta[0]*5,5)
  callback_slot=0x4afa4+dest[2]*0x28 if meta[2]==0 else 0x4afb8+dest[2]*0x28
  callback=struct.unpack('<I',rd(callback_slot,4))[0]
  comcfg_addr=0x44ef8+12*dest[0];comcfg=rd(comcfg_addr,12)
  callout=struct.unpack('<I',rd(0x44e50+4*comcfg[6],4))[0]
  lmc2_routes.append({'can_id':row['can_id'],'canif_pdu_id':pdu,'pdur_route':route,'destination_index':meta[0],'destination_pdu_id':dest[0],'callback':hex(callback),'com_config_address':hex(comcfg_addr),'com_config_raw':comcfg.hex(' '),'callout_enabled':comcfg[5],'callout':hex(callout),'deferred_buffer_offset':struct.unpack_from('<H',comcfg,2)[0],'deferred_copy_length':struct.unpack_from('<H',comcfg,0)[0]-struct.unpack_from('<H',comcfg,2)[0]})
 references={hex(v):[hex(BASE+off) for off in all_hits(b,struct.pack('<I',v))] for v in [0x100412a8,0x10041590,0x0003081e,0x3d6,0x3d3]}
 strings=[{'address':hex(BASE+m.start()),'text':m.group().decode('ascii')} for m in re.finditer(rb'[ -~]{8,}',b)]
 cal=(OUT/manifest[2]['blocks'][0]['local_file']).read_bytes()
 profiles=[]
 for off in [0x13a2,0x22f6,0x324a,0x419e,0x50f2,0x6046]:
  profiles.append({'offset':hex(off),'bytes':list(cal[off:off+32]),'u16le':list(struct.unpack_from('<16H',cal,off)),'u16be':list(struct.unpack_from('>16H',cal,off))})
 small=(OUT/manifest[1]['blocks'][0]['local_file']).read_bytes()
 parameter_root=struct.unpack_from('<I',b,0xbe4c+0x6c)[0]
 assert parameter_root==0x1c0168
 parameter_offsets=[0x1e8,0x1ea,0x1ec,0x1ee,0x1f0,0x1f2]
 parameters=[{'structure_offset':hex(off),'cpu_address':hex(parameter_root+off),'raw_u16':struct.unpack_from('<H',small,parameter_root+off-0x1c0000)[0]} for off in parameter_offsets]
 assert b[0x86:0x8c]==bytes.fromhex('25 06 00 8a 04 00')
 report={'manifest':manifest,'receive_table_layout_evidence':{'lookup_function_cpu':'0x84dcc','dispatch_function_cpu':'0x84d46','layout':'CAN ID at +0, mask/search flags at +4, upper-layer PDU ID at +8, length field at +9, callback index at +10, frame-type filter at +11','startup_tp_cpu_instruction':'0x40086','startup_tp_raw':'25 06 00 8a 04 00','tp':'0x48a00','gp_startup':'0xfebffe7c','note':'CPU/VBF address relationship verified against startup and embedded pointers; static analysis only.'},'receive_tables':tables,'table_slot_differences':diff,'receive_routes':lmc2_routes,'default_parameter_path':{'root_cpu':'0x4be4c','pointer_field_cpu':'0x4beb8','parameter_structure_cpu':hex(parameter_root),'fields':parameters,'limits':'This is the ROM default path. Runtime configuration can select other tables. Physical timer units are not established.'},'published_interpretation_audit':{'status':'Field alignment disproved by receive code; retained for comparison only.','tables':published_tables,'slot_differences':published_diff},'literal_references':references,'calibration_candidate_profiles':profiles,'limits':'Static structural evidence only; these records do not establish successful reception in a vehicle, actuation, activation conditions, or safety limits.'}
 (OUT/'firmware_structure.json').write_text(json.dumps(report,indent=2)+'\n')
 (OUT/'program_strings.json').write_text(json.dumps(strings,indent=2)+'\n')
 print(json.dumps({'files':len(manifest),'blocks':sum(len(m['blocks']) for m in manifest),'all_block_crcs_pass':all(bl['crc16_matches'] for m in manifest for bl in m['blocks']),'receive_table_lengths':[len(t['records']) for t in tables],'receive_routes':lmc2_routes,'differing_table_slots':[d['index'] for d in diff]},indent=2))

if __name__=='__main__': main()
