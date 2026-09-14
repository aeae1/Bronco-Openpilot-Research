# language=V850:LE:32:v850e3v5
ram:000b77aa  8207e100  prepare { r28,r29,lp },0x1
ram:000b77ae  06e0  mov r6,r28
ram:000b77b0  07e8  mov r7,r29
ram:000b77b2  0330  mov sp,r6
ram:000b77b4  bfff88ff  jarl 0x000b773c,lp
ram:000b77b8  e0e9  cmp r0,r29
ram:000b77ba  e205  be 0x000b77c6
ram:000b77bc  23970100  ld.w 0x0[sp],r18
ram:000b77c0  bc91  sub r28,r18
ram:000b77c2  7d970100  st.w r18,0x0[r29]
ram:000b77c6  4206ff00  dispose 0x1,{ r28,r29,lp },[lp]
