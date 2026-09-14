/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000f3e34(void)

{
  float fVar1;
  float fVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  float fVar8;
  float in_r16;
  float fVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;

  uRamfef211a2 = func_0x000bce5c();
  uVar4 = func_0x000bd486();
  uRamfef21253 = (undefined1)uVar4;
  uRamfef21255 = cRamfef23886 != '\0' || uVar4 == bRamfef23887;
  if ((bool)uRamfef21255) {
    iVar5 = func_0x000bd516();
    in_r16 = (float)iVar5;
    uRamfef21244 = (undefined2)iVar5;
    fVar9 = in_r16 * 1e-06;
    uVar3 = func_0x000bdf3a();
    uRamfef20811 = FUN_ram_000bd56e();
  }
  else {
    iVar5 = func_0x000bd51e();
    uRamfef21242 = (undefined2)iVar5;
    fVar9 = (float)iVar5 * 2.5e-07;
    uRamfef20811 = func_0x000bd576();
    uVar3 = 0;
  }
  fVar9 = fVar9 - 0.001024;
  uRamfef20810 = uVar3;
  uRamfef211a8 = func_0x000bd596();
  iVar5 = func_0x000bd53e();
  uRamfef21250 = (undefined2)iVar5;
  uVar4 = 0x3fa66666;
  fVar8 = (float)iVar5 * 0.0002 - 6.5;
  uRamfef21190 = (uint)(0x3fa66666 < (int)fVar8) * 0x3fa66666 +
                 (int)in_r16 * (uint)(0x3fa66666 >= (int)fVar8);
  if ((int)fVar8 < 0x3fa66667) {
    uRamfef21190 = (uint)(fVar8 < -1.3) * -0x4059999a | (uint)(fVar8 >= -1.3) * (int)fVar8;
  }
  uRamfef21254 = func_0x000bd4f6();
  uRamfef2123a = func_0x000bd3b0();
  bVar10 = (uRamfef23874 & uRamfef2123a) != uRamfef23874;
  uRamfef2122c = FUN_ram_000bd05c();
  bVar11 = (uRamfef23868 & uRamfef2122c) == uRamfef23868;
  bVar12 = (uRamfef2386c & uRamfef2122c) == uRamfef2386c;
  bVar13 = (uRamfef23870 & uRamfef2122c) == uRamfef23870;
  if ((bVar10) || (uRamfef2119a = uRamfef21254, (uRamfef23860 & uRamfef2122c) != uRamfef23860)) {
    uRamfef2119a = 0;
  }
  uRamfef211a4 = FUN_ram_000bd54e();
  uRamfef2119c = func_0x000bdcd0();
  bVar10 = cRamfef23888 != '\0';
  cRamfef2119d = bVar10 + cRamfef23888 * !bVar10;
  if ((!bVar10) && ((uRamfef23876 & uRamfef2123a) == uRamfef23876)) {
    cRamfef2119d = (uRamfef23876 != 0) + cRamfef2119d * (uRamfef23876 == 0);
  }
  uRamfef211a0 = (uRamfef2387a & uRamfef2123a) == uRamfef2387a;
  uRamfef2119f = (uRamfef23878 & uRamfef2123a) == uRamfef23878;
  uRamfef2119e = (uRamfef2387c & uRamfef2123a) == uRamfef2387c;
  uRamfef211a1 = (uRamfef2387e & uRamfef2123a) == uRamfef2387e;
  uVar6 = func_0x000bcf1e();
  uRamfef21252 = (undefined1)uVar6;
  bRamfef211ac = ((bRamfef2388b <= uVar6 && (float)(int)uVar6 < fRam0017f410) << 2 |
                 (bRamfef2388a <= uVar6 && (float)(int)uVar6 < fRam0017f410) << 1 |
                 (bRamfef23889 <= uVar6 && (float)(int)uVar6 < fRam0017f410)) &
                 (bVar13 << 2 | bVar12 << 1 | bVar11);
  uRamfef21199 = func_0x000bde22();
  uRamfef21198 = func_0x000bde02();
  uRamfef21197 = func_0x000bde0a();
  iVar5 = func_0x000bcf26();
  uRamfef21232 = (undefined2)iVar5;
  bVar10 = fRamfef2385c < (float)iVar5 * 0.0078125;
  fRamfef2114c = (float)((int)fRamfef2385c * (uint)bVar10 +
                        (int)((float)iVar5 * 0.0078125) * (uint)!bVar10);
  if ((!bVar10) && (fRamfef2114c < -fRamfef2385c)) {
    fRamfef2114c = -fRamfef2385c;
  }
  iVar5 = func_0x000bce28();
  uRamfef21234 = (undefined2)iVar5;
  iVar7 = func_0x000bceba();
  uRamfef21236 = (undefined2)iVar7;
  fVar8 = 1000.0;
  fVar1 = (float)iVar7 * 0.03125;
  if ((int)fVar1 < 0x447a0001) {
    fVar8 = (float)((uint)(fVar1 < -1000.0) * -0x3b860000 | (uint)(fVar1 >= -1000.0) * (int)fVar1);
  }
  if (cRamfef23880 == '\0') {
    fVar1 = 0.0;
  }
  else {
    uVar6 = 0xffffffff;
    fVar1 = ((float)(int)cRamfef23881 * 0.0625 + fVar8) * _UNK_ram_0017f3ec;
    if ((0x80000000 < (uint)fVar1) || (uVar6 = (uint)(0 < (int)fVar1), 0x80000000 < (uint)fVar1)) {
      fVar1 = -fVar1;
    }
    fVar2 = fVar1;
    if ((((ABS(_UNK_ram_0017f3e4) != 0.0) &&
         (fVar2 = -((float)(int)(fVar1 / _UNK_ram_0017f3e4) * _UNK_ram_0017f3e4 - fVar1),
         ABS(fVar2) != 0.0)) && (0x80000000 < (uint)fVar1)) &&
       ((uint)_UNK_ram_0017f3e4 < 0x80000001)) {
      fVar2 = fVar2 + _UNK_ram_0017f3e4;
    }
    iVar7 = func_0x000f3dcc(0xb,0xfef2388c,0xfef238a4,(int)(fVar2 * 4096.0) & 0xffff);
    fVar2 = (float)(int)uVar6 * ((float)iVar7 * 6.1035156e-05 - 2.0) *
            (float)(int)cRamfef23882 * 0.03125;
    fVar1 = (float)(int)cRamfef23885 * 0.0078125;
    if (fVar2 <= fVar1) {
      fVar1 = (float)(int)cRamfef23884 * 0.0078125;
      fVar1 = (float)((uint)(fVar2 < fVar1) * (int)fVar1 | (uint)(fVar2 >= fVar1) * (int)fVar2);
    }
    fVar1 = (float)(int)cRamfef23883 * 0.015625 + fVar1;
  }
  fVar1 = (float)iVar5 * 0.0009765625 - fVar1;
  fVar2 = 8.0;
  if ((int)fVar1 < 0x41000001) {
    fVar2 = (float)((uint)(fVar1 < -8.0) * -0x3f000000 | (uint)(fVar1 >= -8.0) * (int)fVar1);
  }
  fRamfef21150 = fVar2;
  iVar5 = func_0x000bce64();
  uRamfef21238 = (undefined2)iVar5;
  fVar1 = (float)iVar5 * 0.25;
  fRamfef2115c = (float)((uint)(0x43fa0000 < (int)fVar1) * 0x43fa0000 +
                        (int)fVar1 * (uint)((int)fVar1 < 0x43fa0001));
  if ((int)fVar1 < 0x43fa0001) {
    fRamfef2115c = (float)((uint)(fRamfef2115c < -500.0) * -0x3c060000 |
                          (uint)(fRamfef2115c >= -500.0) * (int)fRamfef2115c);
  }
  fVar1 = fRamfef23864 * _UNK_ram_0017f3e4 * fRam0017f434 * (fVar2 - fRamfef20830) + fRamfef20830;
  fRamfef20830 = fVar1;
  fRamfef21154 = fVar1;
  fRamfef21158 = fVar8;
  iVar5 = func_0x000bceec();
  uRamfef2124a = (undefined2)iVar5;
  fVar8 = (float)iVar5 * 0.015625;
  uRamfef21188 = (uint)(fVar8 < 255.0) * (int)fVar8 | (uint)(fVar8 >= 255.0) * 0x437f0000;
  uRamfef211aa = func_0x000bd566();
  iVar5 = func_0x000bd4ae();
  uRamfef2123c = (undefined2)iVar5;
  fVar8 = (float)iVar5 * 0.035 - 17.9;
  uRamfef21164 = (uint)(0x418e6666 < (int)fVar8) * 0x418e6666 +
                 (int)fVar1 * (uint)((int)fVar8 < 0x418e6667);
  if ((int)fVar8 < 0x418e6667) {
    uRamfef21164 = (uint)(fVar8 < -17.8) * -0x3e71999a | (uint)(fVar8 >= -17.8) * (int)fVar8;
  }
  uRamfef211a9 = func_0x000bd55e();
  iVar5 = func_0x000bd536();
  uRamfef2123e = (undefined2)iVar5;
  fVar8 = (float)iVar5 * 0.0005 - 0.5;
  uRamfef2116c = (uint)(0.5 < fVar8) * 0x3f000000 | (uint)(0.5 >= fVar8) * (int)fVar8;
  iVar5 = func_0x000bd52e();
  fVar8 = (float)iVar5 * 0.01 - 5.12;
  uRamfef21246 = (undefined2)iVar5;
  uRamfef21174 = (uint)(0.001024 < fVar9) * 0x3a8637bd | (uint)(0.001024 >= fVar9) * (int)fVar9;
  uRamfef21178 = (uint)(5.12 < fVar8) * 0x40a3d70a | (uint)(5.12 >= fVar8) * (int)fVar8;
  iVar5 = func_0x000bd526();
  uRamfef21240 = (undefined2)iVar5;
  fVar9 = (float)iVar5 * 2e-05 - 0.02;
  uRamfef21170 = (uint)(0.02 < fVar9) * 0x3ca3d70a | (uint)(0.02 >= fVar9) * (int)fVar9;
  uRamfef211ad = func_0x000bd5a6();
  uVar6 = func_0x000bd4c6();
  sRamfef2124c = (short)uVar6;
  sRamfef21194 = (ushort)(0x1fe < uVar6) * 0x1ff + sRamfef2124c * (ushort)(0x1fe >= uVar6) + -0x100;
  iVar5 = func_0x000bd4be();
  fVar9 = (float)iVar5;
  uRamfef2124e = (undefined2)iVar5;
  fVar8 = (fVar9 * 0.03663 - 75.0) * _UNK_ram_0017f3ec;
  if ((int)fVar8 < 0x3fa66667) {
    uVar4 = (uint)(fVar8 < -1.3) * -0x4059999a | (uint)(fVar8 >= -1.3) * (int)fVar8;
  }
  uRamfef2118c = uVar4;
  iVar5 = func_0x000bd506();
  fVar8 = (float)iVar5 * 5e-06 - 0.01024;
  uRamfef21230 = (undefined2)iVar5;
  uRamfef21148 = (uint)(0x3c27b0b4 < (int)fVar8) * 0x3c27b0b4 +
                 (int)fVar9 * (uint)(0x3c27b0b4 >= (int)fVar8);
  if ((int)fVar8 < 0x3c27b0b5) {
    uRamfef21148 = (uint)(fVar8 < -0.010235) * -0x43d84f4c | (uint)(fVar8 >= -0.010235) * (int)fVar8
    ;
  }
  iVar5 = func_0x000bd50e();
  uRamfef21248 = (undefined2)iVar5;
  fVar9 = (float)iVar5 * 0.05 - 102.4;
  if ((int)fVar9 < 0x42ccb334) {
    uRamfef21184 = (uint)(fVar9 < -102.35) * -0x3d334ccd | (uint)(fVar9 >= -102.35) * (int)fVar9;
  }
  else {
    uRamfef21184 = 0x42ccb333;
  }
  uRamfef211ab = func_0x000bd556();
  uRamfef211a7 = func_0x000bd58e();
  uRamfef211a5 = func_0x000bd57e();
  uRamfef211a6 = func_0x000bd586();
  uRamfef21196 = func_0x000bd546();
  uRamfef211a3 = func_0x000bd59e();
  return;
}
