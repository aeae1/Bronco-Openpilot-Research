
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00084dcc(uint param_1,uint param_2,byte param_3,int param_4)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  bool bVar9;
  
  param_1 = param_1 & 0xff;
  bVar9 = (param_2 & 0x40000000) == 0;
  iVar2 = (uint)bVar9 * 2 + (uint)!bVar9;
  param_2 = param_2 & 0xbfffffff;
  if (DAT_ram_feede880 == '\0') {
    return;
  }
  if (param_4 == 0) {
    return;
  }
  if (0x40 < param_3) {
    return;
  }
  if (*(byte *)(_DAT_ram_feede884 + 4) <= param_1) {
    return;
  }
  iVar7 = param_1 * 4 + *_DAT_ram_feede884;
  uVar6 = (uint)*(byte *)(iVar7 + 2);
  if (uVar6 == 0xff) {
    return;
  }
  cVar1 = *(char *)(iVar7 + 3);
  if (cVar1 == '\x01') {
    iVar7 = (int)*(char *)(uVar6 * 0xc + _DAT_ram_feede884[1] + 0xb);
    uVar3 = uVar6;
    if ((iVar7 != 0) && (iVar7 != iVar2)) {
      return;
    }
    goto LAB_ram_00084f22;
  }
  uVar3 = 0xff;
  if (cVar1 != '\0') {
    return;
  }
  iVar7 = _DAT_ram_feede884[1];
  if ((*(byte *)(uVar6 * 0xc + iVar7 + 7) & 0x20) == 0) {
    while( true ) {
      puVar8 = (uint *)(uVar6 * 0xc + iVar7);
      if ((puVar8[1] & 0x20000000) != 0) break;
      if (*puVar8 == param_2) {
        bVar9 = *(char *)((int)puVar8 + 0xb) == 0;
        uVar3 = uVar6 * bVar9 + uVar3 * !bVar9;
        if (bVar9) goto LAB_ram_00084f1c;
        bVar9 = *(char *)((int)puVar8 + 0xb) == iVar2;
        uVar3 = uVar6 * bVar9 + uVar3 * !bVar9;
        if (bVar9) goto LAB_ram_00084f1c;
      }
      if ((puVar8[1] & 0x40000000) != 0) goto LAB_ram_00084f1c;
      uVar6 = uVar6 - 1 & 0xff;
    }
  }
  while( true ) {
    puVar8 = (uint *)(uVar6 * 0xc + iVar7);
    uVar5 = puVar8[1];
    if ((uVar5 & 0x60000000) != 0x20000000) break;
    uVar4 = *puVar8;
    if ((uVar4 & 0x20000000) == 0) {
      if ((uVar4 <= param_2) && (param_2 <= (uVar5 & 0x9fffffff))) goto LAB_ram_00084eba;
    }
    else if (uVar4 == (uVar5 & param_2 | 0x20000000)) {
LAB_ram_00084eba:
      bVar9 = *(char *)((int)puVar8 + 0xb) == 0;
      uVar3 = uVar6 * bVar9 + uVar3 * !bVar9;
      if (bVar9) break;
      bVar9 = *(char *)((int)puVar8 + 0xb) == iVar2;
      uVar3 = uVar6 * bVar9 + uVar3 * !bVar9;
      if (bVar9) break;
    }
    uVar6 = uVar6 - 1 & 0xff;
  }
  if ((uVar5 & 0x60000000) == 0x60000000) {
    uVar4 = *puVar8;
    if ((uVar4 & 0x20000000) == 0) {
      if ((uVar4 <= param_2) && (param_2 <= (uVar5 & 0x9fffffff))) goto LAB_ram_00084f0c;
    }
    else if (uVar4 == (uVar5 & param_2 | 0x20000000)) {
LAB_ram_00084f0c:
      iVar7 = (int)*(char *)((int)puVar8 + 0xb);
      bVar9 = iVar7 == 0;
      uVar3 = uVar6 * bVar9 + uVar3 * !bVar9;
      if (!bVar9) {
        uVar3 = uVar6 * (iVar7 == iVar2) + uVar3 * (iVar7 != iVar2);
      }
    }
  }
LAB_ram_00084f1c:
  if (uVar3 == 0xff) {
    return;
  }
LAB_ram_00084f22:
  FUN_ram_00084d46(param_1,uVar3,param_4,param_3);
  return;
}

