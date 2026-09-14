
void FUN_ram_000d08ec(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = DAT_ram_febf59b7 ^ 1;
  iVar1 = (int)&DAT_ram_febf62c4 + uVar3 * 0xc4;
  uRamfebee5d0 = (undefined2)iVar1;
  func_0x000d06d4((int)&DAT_ram_febf62c4 + (uint)DAT_ram_febf59b7 * 0xc4,iVar1,0x30);
  uVar2 = (uint)DAT_ram_febf59b7;
  DAT_ram_febf59b7 = (byte)uVar3;
  *(undefined4 *)(&DAT_ram_febf6384 + uVar2 * 0xc4) = *(undefined4 *)(iVar1 + 0xc0);
  uRamfebf59b5 = (&DAT_ram_febf56e5)[(uint)DAT_ram_febf56eb * 2];
  return;
}

