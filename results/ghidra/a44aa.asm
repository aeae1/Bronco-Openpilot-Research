ram:000a44aa  prepare { r26,r27,r28,r29,lp },0x0
ram:000a44ae  mov r7,r26
ram:000a44b0  mov 0x1,r29
ram:000a44b2  mulhi 0x5,r6,ep
ram:000a44b6  add tp,ep
ram:000a44b8  ld.bu 0x28f7[ep],r27
ram:000a44bc  mov r27,r28
ram:000a44be  br 0x000a44ce
ram:000a44c0  andi 0xff,r28,r6
ram:000a44c4  mov r26,r7
ram:000a44c6  jarl 0x000a4430,lp
ram:000a44ca  and r10,r29
ram:000a44cc  add 0x1,r28
ram:000a44ce  addi 0x1,r27,r9
ram:000a44d2  zxb r9
ram:000a44d4  cmp r9,r28
ram:000a44d6  bc 0x000a44c0
ram:000a44d8  mov r29,r10
ram:000a44da  dispose 0x0,{ r26,r27,r28,r29,lp },[lp]
