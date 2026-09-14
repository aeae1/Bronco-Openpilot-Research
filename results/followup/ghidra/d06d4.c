void FUN_ram_000d06d4(int param_1,int param_2,uint param_3)

{
  uint uVar1;

  for (uVar1 = 0; uVar1 < (param_3 & 0xffff); uVar1 = uVar1 + 1 & 0xffff) {
    *(undefined4 *)(uVar1 * 4 + param_1) = *(undefined4 *)(uVar1 * 4 + param_2);
  }
  return;
}
