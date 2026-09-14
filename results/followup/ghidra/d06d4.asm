# language=V850:LE:32:v850e3v5
ram:000d06d4  c800  zxh r8
ram:000d06d6  0092  mov 0x0,r18
ram:000d06d8  b50d  br 0x000d06ee
ram:000d06da  1288  mov r18,r17
ram:000d06dc  c28a  shl 0x2,r17
ram:000d06de  11f0  mov r17,ep
ram:000d06e0  c6f1  add r6,ep
ram:000d06e2  c789  add r7,r17
ram:000d06e4  4192  add 0x1,r18
ram:000d06e6  319f0100  ld.w 0x0[r17],r19
ram:000d06ea  d200  zxh r18
ram:000d06ec  019d  sst.w r19,0x0[ep]
ram:000d06ee  e891  cmp r8,r18
ram:000d06f0  d1f5  bc 0x000d06da
ram:000d06f2  7f00  jmp [lp]
