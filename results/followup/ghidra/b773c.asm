# language=V850:LE:32:v850e3v5
ram:000b773c  8007e110  prepare { r27,r28,r29,lp },0x0
ram:000b7740  06d8  mov r6,r27
ram:000b7742  bafff8e4  jarl 0x00065c3a,lp
ram:000b7746  3e064080ddff  mov 0xffdd8040,ep
ram:000b774c  00e5  sld.w 0x0[ep],r28
ram:000b774e  02ed  sld.w 0x4[ep],r29
ram:000b7750  baffeee4  jarl 0x00065c3e,lp
ram:000b7754  f1e75254  cvtf.uls r28r29,r10r11
ram:000b7758  0042  mov 0x0,r8
ram:000b775a  29060040bf40  mov 0x40bf4000,r9
ram:000b7760  e0d9  cmp r0,r27
ram:000b7762  e8577e84  divf.s r8r9,r10r11,r16r17
ram:000b7766  f18754e4  trncf.dul r16r17,r28r29
ram:000b776a  b205  be 0x000b7770
ram:000b776c  7be70100  st.w r28,0x0[r27]
ram:000b7770  4006ff10  dispose 0x0,{ r27,r28,r29,lp },[lp]
