
uint FUN_ram_000a44aa(int param_1,undefined4 param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 1;
  bVar1 = (&UNK_ram_0004b2f7)[param_1 * 5];
  for (uVar3 = (uint)bVar1; uVar3 < (bVar1 + 1 & 0xff); uVar3 = uVar3 + 1) {
    uVar2 = FUN_ram_000a4430(uVar3 & 0xff,param_2);
    uVar4 = uVar4 & uVar2;
  }
  return uVar4;
}

