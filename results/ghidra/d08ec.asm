ram:000d08ec  prepare { r27,r28,lp },0x0
ram:000d08f0  ld.bu -0xa4c5[gp],r18
ram:000d08f6  mov 0xfebf62c4,r27
ram:000d08fc  movea 0x30,r0,r8
ram:000d0900  mulhi 0xc4,r18,r6
ram:000d0904  xori 0x1,r18,r28
ram:000d0908  mulhi 0xc4,r28,r7
ram:000d090c  add r27,r6
ram:000d090e  add r27,r7
ram:000d0910  st.w r7,-0x118ac[gp]
ram:000d0916  jarl 0x000d06d4,lp
ram:000d091a  ld.bu -0xa4c5[gp],r17
ram:000d0920  ld.w 0xc0[r7],r16
ram:000d0924  st.b r28,-0xa4c5[gp]
ram:000d092a  mulhi 0xc4,r17,ep
ram:000d092e  add r27,ep
ram:000d0930  sst.w r16,0xc0[ep]
ram:000d0932  ld.bu -0xa791[gp],ep
ram:000d0938  shl 0x1,ep
ram:000d093a  add gp,ep
ram:000d093c  ld.bu -0xa797[ep],r14
ram:000d0942  st.b r14,-0xa4c7[gp]
ram:000d0948  dispose 0x0,{ r27,r28,lp },[lp]
