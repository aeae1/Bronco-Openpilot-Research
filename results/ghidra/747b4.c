
void FUN_ram_000747b4(char param_1,char param_2,char param_3,undefined1 *param_4,undefined1 *param_5
                     ,undefined2 *param_6,undefined2 *param_7,undefined1 *param_8,
                     undefined1 *param_9,undefined2 *param_10,undefined2 *param_11,
                     undefined1 *param_12,undefined2 *param_13,undefined2 *param_14)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uStack_30;
  
  if (param_3 != cRamfebf58df) {
    FUN_ram_000b773c(0xfebf4b20);
  }
  cRamfebf58df = param_3;
  if (param_1 == '\x01') {
    uVar3 = 0x134c;
    if (param_2 == '\0') {
      uVar3 = (uint)*(ushort *)(*(int *)(iRamfebee5d0 + 0x6c) + 0x1f0);
    }
    FUN_ram_000b77aa(uRamfebf4b20,&uStack_30);
    if (uStack_30 <= uVar3 * 10) goto LAB_ram_0007483a;
    uVar2 = 1;
  }
  else {
    FUN_ram_000b773c(0xfebf4b20);
    uVar2 = 0;
  }
  FUN_ram_000c745e(0x10c,0,uVar2,0xffff);
LAB_ram_0007483a:
  FUN_ram_000b77aa(uRamfebf4b14,&uStack_30);
  uVar1 = 0;
  if (uStack_30 <= (uint)*(ushort *)(*(int *)(iRamfebee5d0 + 0x6c) + 0x1ea) * 10) {
    uVar1 = DAT_ram_febf5ab1;
  }
  *param_9 = uVar1;
  *param_4 = uRamfebf58e2;
  *param_5 = uRamfebf58e1;
  *param_7 = uRamfebf5784;
  *param_11 = uRamfebf5788;
  *param_10 = uRamfebf5786;
  *param_6 = uRamfebf5782;
  *param_12 = uRamfebf58e3;
  *param_14 = uRamfebf578c;
  *param_13 = uRamfebf578a;
  *param_8 = uRamfebf58e0;
  FUN_ram_000b773c(0xfebf4b24);
  FUN_ram_000b773c(0xfebf4b18);
  FUN_ram_000b773c(0xfebf4b10);
  FUN_ram_000b773c(0xfebf4b1c);
  return;
}

