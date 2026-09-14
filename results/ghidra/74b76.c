
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00074b76(void)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  undefined1 uVar10;
  bool bVar11;
  undefined1 uStack_43;
  char cStack_42;
  undefined1 uStack_41;
  byte bStack_40;
  byte bStack_3f;
  byte bStack_3e;
  undefined1 uStack_3d;
  undefined1 uStack_3c;
  undefined1 uStack_3b;
  ushort uStack_3a;
  ushort uStack_38;
  ushort uStack_36;
  ushort uStack_34;
  ushort uStack_32;
  ushort uStack_30;
  undefined2 uStack_2e;
  
  uVar10 = DAT_ram_feede81c;
  cVar9 = cRamfeede7e9;
  cVar8 = cRamfeede7e5;
  cVar7 = cRamfeede7dc;
  uVar6 = _DAT_ram_feede784;
  uVar5 = _DAT_ram_feede782;
  uVar4 = _DAT_ram_feede780;
  uVar3 = uRamfebeec3c;
  cVar2 = cRamfebeec3a;
  uVar1 = uRamfebeec29;
  uStack_41 = 0;
  uStack_2e = _DAT_ram_feede786;
  uStack_3d = DAT_ram_feede81d;
  uStack_3c = DAT_ram_feede81e;
  uStack_3b = DAT_ram_feede81f;
  func_0x0005ce50(&uStack_43);
  if (cVar2 == '\0') {
    if ((cVar8 == '\x01') || (cVar7 == '\x01')) {
      bVar11 = true;
    }
    else {
      bVar11 = cVar9 == '\x01';
    }
  }
  else {
    bVar11 = false;
  }
  if (cRamfeede85f == '\x01') {
    func_0x000747b4(bVar11,uVar3,uVar1,&bStack_3f,&bStack_3e,&bStack_40,uVar6,&uStack_38,&cStack_42,
                    &uStack_41,&uStack_36,&uStack_34,&bStack_3e,&uStack_32);
  }
  else {
    func_0x00074a1e(bVar11,uVar1,uStack_43,uStack_3b,uVar10,uVar5,uStack_2e,uVar6,uVar4,
                    DAT_ram_feede821,uStack_3d,uStack_3c,uVar10,&bStack_3f,&bStack_40,uVar6,
                    &uStack_38,&cStack_42,&uStack_41,&uStack_36,&uStack_34,&bStack_3e,&uStack_32);
  }
  cRamfebf58e2 = (2 < bStack_3f) * '\x03' + bStack_3f * (bStack_3f != 0) * (2 >= bStack_3f);
  cRamfebf58e1 = (2 < bStack_40) * '\x03' + bStack_40 * (bStack_40 != 0) * (2 >= bStack_40);
  sRamfebf5784 = (ushort)(0x7fe < uStack_38) * 0x7ff +
                 uStack_38 * (uStack_38 != 0) * (ushort)(0x7fe >= uStack_38);
  sRamfebf5788 = (ushort)(0x7fe < uStack_34) * 0x7ff +
                 uStack_34 * (uStack_34 != 0) * (ushort)(0x7fe >= uStack_34);
  sRamfebf5786 = (ushort)(0x3fe < uStack_36) * 0x3ff +
                 uStack_36 * (uStack_36 != 0) * (ushort)(0x3fe >= uStack_36);
  sRamfebf5782 = (ushort)(0x7fe < uStack_3a) * 0x7ff +
                 uStack_3a * (uStack_3a != 0) * (ushort)(0x7fe >= uStack_3a);
  cRamfebf58e3 = (6 < bStack_3e) * '\a' + bStack_3e * (bStack_3e != 0) * (6 >= bStack_3e);
  sRamfebf578c = (ushort)(0xe < uStack_30) * 0xf +
                 uStack_30 * (uStack_30 != 0) * (ushort)(0xe >= uStack_30);
  sRamfebf578a = (ushort)(0xfe < uStack_32) * 0xff +
                 uStack_32 * (uStack_32 != 0) * (ushort)(0xfe >= uStack_32);
  DAT_ram_febf5ab1 = uStack_41;
  uRamfebf58e0 = cStack_42 != '\0';
  sRamfebeeba2 = sRamfebf5782;
  sRamfebeeba4 = sRamfebf5784;
  uRamfebeecf8 = cStack_42 != '\0';
  uRamfebeecf9 = uStack_41;
  sRamfebeeba6 = sRamfebf5786;
  sRamfebeeba8 = sRamfebf5788;
  cRamfebeecfa = cRamfebf58e1;
  cRamfebeecfb = cRamfebf58e2;
  cRamfebeecfc = cRamfebf58e3;
  sRamfebeebaa = sRamfebf578a;
  sRamfebeebac = sRamfebf578c;
  return;
}

