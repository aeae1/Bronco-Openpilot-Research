/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_ram_000d06f4(char param_1,uint param_2,int param_3)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  bool bVar10;
  int iStack_2c;

  iVar3 = 0;
  iVar7 = (DAT_ram_febf59b7 ^ 1) * 0xc4;
  iVar8 = (int)&DAT_ram_febf62c4 + iVar7;
  func_0x000c4424(iVar8,0x30,0,1,&iStack_2c);
  if (iStack_2c != *(int *)(&DAT_ram_febf6384 + iVar7)) {
    FUN_ram_000c745e(0x14,2,1,0);
    uRamfebf59b6 = 5;
    return 0;
  }
  uRamfebf59b6 = 2;
  bVar10 = ((&DAT_ram_febf56e5)[(uint)DAT_ram_febf56eb * 2] & 1) != 0;
  bVar1 = false;
  if (DAT_ram_febf56ea == '\x02') {
    if ((&DAT_ram_febf56e5)[(uint)DAT_ram_febf56eb * 2] != bRamfebf59b5) {
      uVar5 = 0;
      uRamfebf59b6 = 4;
      if (bVar10) {
        do {
          if (DAT_ram_febf56eb == (&UNK_ram_0004c728)[uVar5 * 0xc]) {
            uRamfebf59b6 = 3;
            FUN_ram_000d06d4((uint)*(ushort *)(&DAT_ram_0004c726 + uVar5 * 0xc) * 4 + iVar8,
                             &PTR_DAT_ram_feed8004_ram_0004c720 + uVar5 * 3,1);
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < 9);
      }
      else {
        FUN_ram_000d06d4(iVar8,&LAB_ram_0004be4c,0x30);
        do {
          if (DAT_ram_febf56ec == *(char *)(&PTR_DAT_ram_001e0000_ram_0004c66a + uVar5 * 2)) {
            FUN_ram_000d06d4((uint)(ushort)(&DAT_ram_0004c666)[uVar5 * 4] * 4 + iVar8,
                             &LAB_ram_0004be4c + (uint)(ushort)(&DAT_ram_0004c664)[uVar5 * 4] * 4,1)
            ;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < 4);
        if (DAT_ram_febf56ed == UNK_ram_0004c662) {
          FUN_ram_000d06d4((uint)_UNK_ram_0004c65e * 4 + iVar8,
                           &LAB_ram_0004be4c + (uint)_UNK_ram_0004c65c * 4,1);
        }
      }
      if (DAT_ram_febf56ea != '\x02') goto LAB_ram_000d0840;
    }
    bVar1 = bVar10;
  }
LAB_ram_000d0840:
  for (uVar5 = 0; uVar5 < (param_2 & 0xff); uVar5 = uVar5 + 1 & 0xff) {
    puVar4 = (ushort *)(uVar5 * 8 + param_3);
    if ((char)puVar4[3] == param_1) {
      if ((bVar1) && (uVar6 = 0, DAT_ram_febf56ee == (char)puVar4[3])) {
        do {
          if ((DAT_ram_febf56eb == (&UNK_ram_0004c728)[uVar6 * 0xc]) &&
             ((uint)puVar4[1] == (uint)*(ushort *)(&DAT_ram_0004c726 + uVar6 * 0xc))) {
            FUN_ram_000d06d4((uint)*(ushort *)(&DAT_ram_0004c726 + uVar6 * 0xc) * 4 + iVar8,
                             &PTR_DAT_ram_feed8004_ram_0004c720 + uVar6 * 3,1);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < 9);
      }
      else {
        piVar9 = (int *)((uint)*puVar4 * 4 + iVar8);
        piVar2 = (int *)((uint)puVar4[1] * 4 + iVar8);
        if (*piVar2 == *piVar9) {
          piVar9 = (int *)(&LAB_ram_0004be4c + (uint)*puVar4 * 4);
        }
        FUN_ram_000d06d4(piVar2,piVar9,1);
      }
      iVar3 = 1;
    }
  }
  if (iVar3 == 1) {
    func_0x000c4424(iVar8,0x30,0,1,&DAT_ram_febf6384 + iVar7);
  }
  return iVar3;
}
