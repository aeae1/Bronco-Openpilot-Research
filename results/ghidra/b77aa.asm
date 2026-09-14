ram:000b77aa  prepare { r28,r29,lp },0x1
ram:000b77ae  mov r6,r28
ram:000b77b0  mov r7,r29
ram:000b77b2  mov sp,r6
ram:000b77b4  jarl 0x000b773c,lp
ram:000b77b8  cmp r0,r29
ram:000b77ba  be 0x000b77c6
ram:000b77bc  ld.w 0x0[sp],r18
ram:000b77c0  sub r28,r18
ram:000b77c2  st.w r18,0x0[r29]
ram:000b77c6  dispose 0x1,{ r28,r29,lp },[lp]
