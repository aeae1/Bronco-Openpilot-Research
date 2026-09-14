void FUN_ram_000ed420(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  bool bVar10;

  uRamfef26414 = func_0x000bd3b0();
  uRamfef26389 = (uRamfef24620 & uRamfef26414) == uRamfef24620;
  uRamfef2638a = func_0x000bd7ee();
  uRamfef2638b = FUN_ram_000bd56e();
  iVar1 = func_0x000bd516();
  uRamfef2641c = (undefined2)iVar1;
  fVar3 = (float)iVar1 * 1e-06 - 0.001024;
  uVar4 = (uint)(0.001024 < fVar3) * 0x3a8637bd | (uint)(0.001024 >= fVar3) * (int)fVar3;
  uRamfef26378 = uVar4;
  iVar1 = func_0x000bd526();
  uRamfef2641a = (undefined2)iVar1;
  fVar3 = (float)iVar1 * 2e-05 - 0.02;
  uVar6 = (uint)(0.02 < fVar3) * 0x3ca3d70a | (uint)(0.02 >= fVar3) * (int)fVar3;
  uRamfef26374 = uVar6;
  iVar1 = func_0x000bd536();
  uRamfef26418 = (undefined2)iVar1;
  fVar3 = (float)iVar1 * 0.0005 - 0.5;
  uVar7 = (uint)(0.5 < fVar3) * 0x3f000000 | (uint)(0.5 >= fVar3) * (int)fVar3;
  uRamfef26370 = uVar7;
  iVar1 = func_0x000bd52e();
  uRamfef2641e = (undefined2)iVar1;
  fVar3 = (float)iVar1 * 0.01 - 5.12;
  uVar5 = (uint)(5.12 < fVar3) * 0x40a3d70a | (uint)(5.12 >= fVar3) * (int)fVar3;
  uRamfef2637c = uVar5;
  uRamfef26408 = FUN_ram_000bd05c();
  bVar9 = (uRamfef2461c & uRamfef26408) == uRamfef2461c;
  uRamfef26425 = bVar9;
  uRamfef26412 = func_0x000bd766();
  bVar10 = (uRamfef24622 & uRamfef26412) != uRamfef24622;
  uRamfef26388 = bVar9 && bVar10;
  iVar2 = func_0x000bceec();
  uRamfef26420 = (undefined2)iVar2;
  iVar1 = 0xff;
  if ((int)((float)iVar2 * 0.015625) < 0x437f0000) {
    iVar1 = (int)(short)(int)((float)iVar2 * 0.015625);
  }
  fRamfef26380 = (float)iVar1;
  iVar2 = func_0x000bce28();
  uVar8 = 0x41000000;
  uRamfef26410 = (undefined2)iVar2;
  fVar3 = (float)iVar2 * 0.0009765625;
  if ((int)fVar3 < 0x41000001) {
    uVar8 = (uint)(fVar3 < -8.0) * -0x3f000000 | (uint)(fVar3 >= -8.0) * (int)fVar3;
  }
  uRamfef26368 = uVar8;
  iVar2 = func_0x000bd7e6();
  uRamfef26404 = uVar5;
  uRamfef26416 = (short)iVar2;
  fVar3 = (float)iVar2 * 0.001953125;
  uRamfef263f8 = uVar7;
  uRamfef26400 = uVar4;
  uRamfef2636c = (uint)(64.0 < fVar3) * 0x42800000 | (uint)(64.0 >= fVar3) * (int)fVar3;
  uRamfef263f0 = uVar8;
  fRamfef2640c = (float)iVar1;
  uRamfef263f4 = uRamfef2636c;
  uRamfef26422 = uRamfef26388;
  uRamfef26423 = uRamfef26389;
  uRamfef26424 = bVar10;
  uRamfef263fc = uVar6;
  return;
}
