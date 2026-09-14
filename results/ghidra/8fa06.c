
void FUN_ram_0008fa06(uint param_1,int *param_2)

{
  int iVar1;
  
  param_1 = param_1 & 0xff;
  if (((((cRamfeede579 != '\0') && (param_1 < 0x2e)) && (param_2 != (int *)0x0)) &&
      ((*param_2 != 0 || ((short)param_2[1] == 0)))) &&
     (((&DAT_ram_feee006c)[param_1] != '\0' &&
      (((&UNK_ram_00044efd)[param_1 * 0xc] == '\0' ||
       (iVar1 = (*(code *)(&PTR_LAB_ram_0006aa52_ram_00044e50)
                          [(byte)(&UNK_ram_00044efe)[param_1 * 0xc]])(param_1,param_2), iVar1 == 1))
      )))) {
    iVar1 = param_1 * 0xc;
    if ((&UNK_ram_00044efc)[iVar1] != '\0') {
      FUN_ram_000e962a();
      if (((&UNK_ram_00044f03)[iVar1] == '\0') && (*param_2 != 0)) {
        FUN_ram_000b41aa(*(ushort *)(&UNK_ram_00044efa + iVar1) + 0xfeedfefc,*param_2,
                         (uint)*(ushort *)(&UNK_ram_00044ef8 + iVar1) -
                         (uint)*(ushort *)(&UNK_ram_00044efa + iVar1) & 0xff);
      }
      *(short *)(param_1 * 2 + -0x111fe74) = (short)param_2[1] + 1;
      FUN_ram_000e9672();
    }
  }
  return;
}

