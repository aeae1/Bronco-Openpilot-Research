
void FUN_ram_00074950(char param_1,char param_2,undefined1 *param_3)

{
  uint uStack_14;
  
  if (DAT_ram_febf5ab0 == '\x01') {
    if (param_2 == '\0') {
      *param_3 = 1;
      DAT_ram_febf5ab0 = 0;
      return;
    }
  }
  else {
    FUN_ram_000b77aa(uRamfebf4b18,&uStack_14);
    if ((param_1 != '\0') || (param_2 != '\0')) {
      if (param_2 == '\x01') {
        FUN_ram_000b77aa(uRamfebf4b10,&uStack_14);
        if (uStack_14 <= (uint)*(ushort *)(*(int *)(iRamfebee5d0 + 0x6c) + 0x1e8) * 10) {
          return;
        }
      }
      else {
        if (param_1 != '\x01') goto LAB_ram_00074a10;
        FUN_ram_000b77aa(uRamfebf4b1c,&uStack_14);
        if (uStack_14 <= (uint)*(ushort *)(*(int *)(iRamfebee5d0 + 0x6c) + 0x1ee) * 10) {
          return;
        }
      }
      *param_3 = 0;
      return;
    }
    if ((uint)*(ushort *)(*(int *)(iRamfebee5d0 + 0x6c) + 0x1ec) * 10 < uStack_14) {
      *param_3 = 1;
      return;
    }
  }
LAB_ram_00074a10:
  *param_3 = DAT_ram_febf5ab1;
  return;
}

