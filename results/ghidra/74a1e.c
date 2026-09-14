
void FUN_ram_00074a1e(char param_1,char param_2,undefined1 param_3,undefined1 param_4,
                     undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
                     undefined1 param_9,byte param_10,byte param_11,undefined1 param_12,
                     undefined1 *param_13,undefined1 *param_14,undefined2 *param_15,
                     undefined2 *param_16,undefined1 *param_17,undefined4 param_18,
                     undefined2 *param_19,undefined2 *param_20,undefined1 *param_21,ushort *param_22
                     ,ushort *param_23)

{
  undefined1 uVar1;
  bool bVar2;
  uint uStack_28;
  
  *param_13 = param_3;
  *param_14 = param_4;
  *param_16 = param_5;
  *param_20 = param_6;
  *param_19 = param_7;
  *param_15 = param_8;
  *param_21 = param_9;
  *param_23 = (ushort)param_10;
  *param_17 = param_12;
  bVar2 = DAT_ram_feede874 != cRamfebf58e4;
  func_0x00074904(*param_16,*param_20,*param_19,*param_21,*param_23,*param_15,param_22);
  if (((*param_23 != uRamfebf578c) || (uVar1 = bVar2, !bVar2)) && (uVar1 = 0, !bVar2)) {
    uVar1 = DAT_ram_febf5ab2;
  }
  DAT_ram_febf5ab2 = uVar1;
  func_0x00074950(DAT_ram_febf5ab2,*param_22 != (ushort)param_11,param_18);
  if (param_2 != cRamfebf58df) {
    FUN_ram_000b773c(0xfebf4b24);
  }
  cRamfebf58df = param_2;
  if (param_1 == '\x01') {
    FUN_ram_000b77aa(uRamfebf4b24,&uStack_28);
    if (uStack_28 <= (uint)*(ushort *)(*(int *)(iRamfebee5d0 + 0x6c) + 0x1f2) * 10)
    goto LAB_ram_00074b52;
  }
  else {
    FUN_ram_000b773c(0xfebf4b24);
  }
  FUN_ram_000c745e(0x10c,0,0,0xffff);
LAB_ram_00074b52:
  cRamfebf58e4 = DAT_ram_feede874;
  FUN_ram_000b773c(0xfebf4b20);
  FUN_ram_000b773c(0xfebf4b14);
  return;
}

