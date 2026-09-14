
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00084d46(uint param_1,uint param_2,undefined4 param_3,ushort param_4)

{
  int iVar1;
  int iVar2;
  undefined4 local_10;
  ushort uStack_c;
  
  uStack_c = param_4 & 0xff;
  if (((((*(char *)((param_1 & 0xff) * 4 + *_DAT_ram_feede884) == '\0') &&
        (DAT_ram_feede909 != '\0')) && (DAT_ram_feede909 == '\x02')) &&
      ((((DAT_ram_feede90a == '\x03' || (DAT_ram_feede90a == '\x01')) ||
        (DAT_ram_feede90a == '\x05')) &&
       ((iVar2 = (param_2 & 0xff) * 0xc + _DAT_ram_feede884[1],
        (*(byte *)(iVar2 + 9) & 0x7f) <= uStack_c && (*(byte *)(iVar2 + 10) < 5)))))) &&
     (iVar1 = (uint)*(byte *)(iVar2 + 10) * 8, (&UNK_ram_00040f64)[iVar1] == '\x01')) {
    if (*(code **)(&UNK_ram_00040f60 + iVar1) != (code *)0x0) {
      local_10 = param_3;
      (**(code **)(&UNK_ram_00040f60 + iVar1))(*(undefined1 *)(iVar2 + 8),&local_10);
    }
  }
  return;
}

