
void FUN_ram_000d0b34(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iStack_18;
  
  cVar1 = cRamfebeec62;
  func_0x000c4424((int)&DAT_ram_febf62c4 + (uint)DAT_ram_febf59b7 * 0xc4,0x30,0,1,&iStack_18);
  iVar2 = *(int *)(&DAT_ram_febf6384 + (uint)DAT_ram_febf59b7 * 0xc4);
  if (iStack_18 == iVar2) {
    FUN_ram_000c745e(0x14,0,0);
    iVar3 = func_0x000b9d02();
  }
  else {
    iVar3 = 1;
    FUN_ram_000c745e(0x14,1,1);
    uRamfebf59b6 = 5;
  }
  uVar4 = 0;
  if (DAT_ram_febf56ea == '\x01') {
    do {
      iVar5 = uVar4 * 0xc;
      if (DAT_ram_febf56eb == (&UNK_ram_0004c728)[iVar5]) {
        func_0x000d0b16((&PTR_DAT_ram_feed8004_ram_0004c720)[uVar4 * 3],
                        *(undefined4 *)
                         ((int)&DAT_ram_febf62c4 +
                         (uint)*(ushort *)(&DAT_ram_0004c726 + iVar5) * 4 +
                         (DAT_ram_febf59b7 ^ 1) * 0xc4),*(undefined2 *)(&UNK_ram_0004c724 + iVar5));
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < 9);
    DAT_ram_febf56ea = '\x02';
  }
  if (iStack_18 == iVar2) {
    if ((iVar3 == 0) &&
       ((cRamfebf59b4 != cVar1 ||
        (((&DAT_ram_febf56e5)[(uint)DAT_ram_febf56eb * 2] != cRamfebf59b5 &&
         (DAT_ram_febf56ea == '\x02')))))) {
      iVar2 = func_0x000d06f4(cVar1,0x12,&DAT_ram_0004c690);
      if (iVar2 == 0) {
        FUN_ram_000c745e(0x15,1,1,0);
        uRamfebf59b6 = 5;
      }
      else {
        func_0x000d08ec();
        FUN_ram_000c745e(0x15,0,0,0);
        cRamfebf59b4 = cVar1;
        cRamfebeedc8 = cVar1;
      }
    }
    else {
      uRamfebf59b6 = 1;
      if (cRamfebf59b4 == cVar1) {
        uRamfebf59b6 = (&DAT_ram_febf56e5)[(uint)DAT_ram_febf56eb * 2] != cRamfebf59b5;
      }
    }
  }
  else {
    uRamfebee5d0 = 0xbe4c;
  }
  bRamfebeedc5 = DAT_ram_febf56eb;
  cRamfebeedc9 = DAT_ram_febf56ea;
  uRamfebeedcc = uRamfebf59b6;
  return;
}

