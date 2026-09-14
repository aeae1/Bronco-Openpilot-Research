# language=V850:LE:32:v850e3v5
ram:000d08ec  8007a110  prepare { r27,r28,lp },0x0
ram:000d08f0  a407b593b6fe  ld.bu -0xa4c5[gp],r18
ram:000d08f6  3b06c462bffe  mov 0xfebf62c4,r27
ram:000d08fc  20463000  movea 0x30,r0,r8
ram:000d0900  f236c400  mulhi 0xc4,r18,r6
ram:000d0904  b2e60100  xori 0x1,r18,r28
ram:000d0908  fc3ec400  mulhi 0xc4,r28,r7
ram:000d090c  db31  add r27,r6
ram:000d090e  db39  add r27,r7
ram:000d0910  84074f3dcefd  st.w r7,-0x118ac[gp]
ram:000d0916  bfffbefd  jarl 0x000d06d4,lp
ram:000d091a  a407b58bb6fe  ld.bu -0xa4c5[gp],r17
ram:000d0920  2787c100  ld.w 0xc0[r7],r16
ram:000d0924  8407bde3b6fe  st.b r28,-0xa4c5[gp]
ram:000d092a  f1f6c400  mulhi 0xc4,r17,ep
ram:000d092e  dbf1  add r27,ep
ram:000d0930  6185  sst.w r16,0xc0[ep]
ram:000d0932  a407f5f6b0fe  ld.bu -0xa791[gp],ep
ram:000d0938  c1f2  shl 0x1,ep
ram:000d093a  c4f1  add gp,ep
ram:000d093c  be079576b0fe  ld.bu -0xa797[ep],r14
ram:000d0942  84079d73b6fe  st.b r14,-0xa4c7[gp]
ram:000d0948  4006bf10  dispose 0x0,{ r27,r28,lp },[lp]
