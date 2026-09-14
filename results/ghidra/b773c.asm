ram:000b773c  prepare { r27,r28,r29,lp },0x0
ram:000b7740  mov r6,r27
ram:000b7742  jarl 0x00065c3a,lp
ram:000b7746  mov 0xffdd8040,ep
ram:000b774c  sld.w 0x0[ep],r28
ram:000b774e  sld.w 0x4[ep],r29
ram:000b7750  jarl 0x00065c3e,lp
ram:000b7754  cvtf.uls r28r29,r10r11
ram:000b7758  mov 0x0,r8
ram:000b775a  mov 0x40bf4000,r9
ram:000b7760  cmp r0,r27
ram:000b7762  divf.s r8r9,r10r11,r16r17
ram:000b7766  trncf.dul r16r17,r28r29
ram:000b776a  be 0x000b7770
ram:000b776c  st.w r28,0x0[r27]
ram:000b7770  dispose 0x0,{ r27,r28,r29,lp },[lp]
