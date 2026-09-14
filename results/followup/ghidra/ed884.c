/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000ed884(void)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;

  fVar10 = fRamfef26380;
  iVar6 = func_0x000ed78e(8,0xfef24674);
  fVar9 = _UNK_ram_001805f0;
  uRamfef26498 = (undefined2)iVar6;
  fVar12 = 0.001953125;
  fRamfef26434 = (float)iVar6 * 0.001953125;
  fRamfef26460 = fRamfef26434 * (float)(int)sRamfef2464c * 0.001953125;
  uVar3 = uRamfef24646;
  fRamfef26488 = 0.00048828125;
  if (bRamfef2638b != 0) {
    uVar3 = uRamfef24644;
    fRamfef26488 = 1.5258789e-05;
  }
  fRamfef26488 = (float)uVar3 * fRamfef26488;
  fVar7 = fRamfef26070 + _UNK_ram_001805f0 * fRamfef26488;
  bVar1 = fVar7 < fRamfef26370;
  fRamfef26070 = (float)((int)fVar7 * (uint)bVar1 + (int)fRamfef26070 * (uint)!bVar1);
  if (!bVar1) {
    fRamfef26070 = fRamfef26070 - _UNK_ram_001805f0 * fRamfef26488;
    fRamfef26070 = (float)((uint)(fRamfef26370 < fRamfef26070) * (int)fRamfef26070 |
                          (uint)(fRamfef26370 >= fRamfef26070) * (int)fRamfef26370);
  }
  if (bRamfef2638b == 0) {
    fRamfef26490 = (float)uRamfef24642 * 0.0078125;
  }
  else {
    fRamfef26490 = (float)_DAT_ram_fef24640 * 0.00012207031;
  }
  fVar7 = fRamfef2606c + _UNK_ram_001805f0 * fRamfef26490;
  bVar1 = fVar7 < fRamfef2637c;
  fRamfef2606c = (float)((int)fVar7 * (uint)bVar1 + (int)fRamfef2606c * (uint)!bVar1);
  if (!bVar1) {
    fRamfef2606c = fRamfef2606c - _UNK_ram_001805f0 * fRamfef26490;
    fRamfef2606c = (float)((uint)(fRamfef2637c < fRamfef2606c) * (int)fRamfef2606c |
                          (uint)(fRamfef2637c >= fRamfef2606c) * (int)fRamfef2637c);
  }
  if (bRamfef2638b == 0) {
    fRamfef2648c = (float)uRamfef2463e * 0.0009765625;
  }
  else {
    fRamfef2648c = (float)uRamfef2463a * 1.5258789e-05;
  }
  fRamfef26484 = (float)uRamfef2463c * 0.0009765625 * fRamfef26378 + fRamfef26374;
  fVar7 = fRamfef26068 + _UNK_ram_001805f0 * fRamfef2648c;
  if (fRamfef26484 <= fVar7) {
    fRamfef26068 = fRamfef26068 - _UNK_ram_001805f0 * fRamfef2648c;
    fVar7 = (float)((uint)(fRamfef26484 < fRamfef26068) * (int)fRamfef26068 |
                   (uint)(fRamfef26484 >= fRamfef26068) * (int)fRamfef26484);
  }
  uRamfef2649e = (undefined2)(int)(fRamfef26070 * 16384.0);
  uRamfef264a2 = (undefined2)(int)(fRamfef2606c * 4096.0);
  uRamfef264a0 = (undefined2)(int)(fVar7 * 16384.0);
  fRamfef26480 = fVar10 / _UNK_ram_001805ec;
  fRamfef26480 = fVar7 * fRamfef26480 * fRamfef26480;
  fRamfef2645c = fRamfef26480 * fRamfef26434 * (float)(int)sRamfef24658 * 0.001953125;
  if (fRamfef2645c <= fRamfef26460) {
    fRamfef26460 = -fRamfef26460;
    fRamfef26460 = (float)((uint)(fRamfef2645c < fRamfef26460) * (int)fRamfef26460 |
                          (uint)(fRamfef2645c >= fRamfef26460) * (int)fRamfef2645c);
  }
  fRamfef26470 = fRamfef26434 * (float)(int)sRamfef24650 * 0.001953125;
  fRamfef2646c = fRamfef2606c * fRamfef26434 * (float)(int)sRamfef2465a * 0.001953125;
  if (fRamfef2646c <= fRamfef26470) {
    fRamfef26470 = -fRamfef26470;
    fRamfef26470 = (float)((uint)(fRamfef2646c < fRamfef26470) * (int)fRamfef26470 |
                          (uint)(fRamfef2646c >= fRamfef26470) * (int)fRamfef2646c);
  }
  fRamfef2643c = fRamfef26434 * (float)(int)sRamfef2462e * 0.001953125;
  fRamfef26438 = fRamfef26070 * fRamfef26434 * (float)(int)sRamfef24656 * 0.001953125;
  if (fRamfef26438 <= fRamfef2643c) {
    fRamfef2643c = -fRamfef2643c;
    fRamfef2643c = (float)((uint)(fRamfef26438 < fRamfef2643c) * (int)fRamfef2643c |
                          (uint)(fRamfef26438 >= fRamfef2643c) * (int)fRamfef26438);
  }
  fVar5 = (float)bRamfef2638b;
  fRamfef26440 = fRamfef26460 + fRamfef26470 + fRamfef2643c;
  fVar5 = (float)((uint)(1.0 < fVar5) * 0x3f800000 | (uint)(1.0 >= fVar5) * (int)fVar5);
  fVar8 = _UNK_ram_001805f0 * (float)(int)cRamfef24662 * 0.03125 + fRamfef26074;
  if (fVar5 <= fVar8) {
    fRamfef26074 = _UNK_ram_001805f0 * (float)(int)cRamfef24663 * 0.03125 + fRamfef26074;
    fVar8 = (float)((uint)(fVar5 < fRamfef26074) * (int)fRamfef26074 |
                   (uint)(fVar5 >= fRamfef26074) * (int)fVar5);
  }
  fRamfef26444 = fRamfef26440 * fVar8;
  fVar5 = (float)uRamfef24630 * 0.00048828125 * _UNK_ram_001805f0;
  uRamfef264a4 = false;
  fVar11 = fRamfef26434 * (float)uRamfef2465e * 3.0517578e-05;
  if (((float)(int)sRamfef2462c <= fVar10) &&
     (uRamfef264a4 = bRamfef2638b == bRamfef24661, !(bool)uRamfef264a4)) {
    uRamfef264a4 = bRamfef2638b == bRamfef24660;
  }
  fRamfef26454 = 0.0;
  if (!(bool)uRamfef264a4) {
    fRamfef26454 = (float)uRamfef24654 * 0.00048828125;
  }
  fVar10 = fRamfef26368;
  if (0x80000000 < (uint)fRamfef26368) {
    fVar10 = -fRamfef26368;
  }
  if (cRamfef2607c == '\0') {
    fRamfef26078 = fRamfef26430 * 0.004 + fRamfef26078;
  }
  else {
    fRamfef26078 = 0.0;
  }
  fVar4 = (float)uRamfef24634;
  bVar1 = (float)uRamfef24636 * 0.00048828125 <= fRamfef26078;
  fRamfef26430 = fVar4 * 0.00048828125 * fVar10 - (float)uRamfef24632 * 0.00048828125;
  fVar13 = (float)((int)((float)uRamfef24636 * 0.00048828125) * (uint)bVar1 +
                  (int)fRamfef26078 * (uint)!bVar1);
  fVar10 = fVar13;
  if ((!bVar1) && (fVar10 = fRamfef26078, (int)fVar13 < 1)) {
    fVar13 = 0.0;
    fVar10 = fVar13;
  }
  fRamfef26078 = fVar10;
  fRamfef2644c = fVar11 + fRamfef26454 + fVar13;
  fVar10 = fRamfef26080 + fVar5;
  if (fRamfef2644c <= fVar10) {
    fRamfef26080 = fRamfef26080 - fVar5;
    fVar10 = (float)((uint)(fRamfef2644c < fRamfef26080) * (int)fRamfef26080 |
                    (uint)(fRamfef2644c >= fRamfef26080) * (int)fRamfef2644c);
  }
  fRamfef26464 = fRamfef26444 - fVar10;
  fRamfef26478 = fRamfef26444 + fVar10;
  bVar1 = fRamfef2636c < fRamfef26464;
  fRamfef26494 = fRamfef26478;
  if (fRamfef2636c <= fRamfef26478) {
    fRamfef26494 = (float)((int)fRamfef2636c * (uint)!bVar1 + (int)fRamfef26464 * (uint)bVar1);
  }
  bVar2 = fRamfef2636c > fRamfef26478;
  uRamfef2604e = bVar2 || bVar1;
  fRamfef26068 = fVar7;
  fRamfef26074 = fVar8;
  fRamfef26080 = fVar10;
  if ((bRamfef26058 & 4) == 0) {
    fVar10 = fRamfef26084;
    if (0x80000000 < (uint)fRamfef26084) {
      fVar10 = -fRamfef26084;
    }
    if ((bRamfef26058 & 0x40) == 0) {
      if ((bRamfef26058 & 2) == 0) {
        bRamfef26058 = bRamfef26058 | 4;
        func_0x000ed834();
      }
      else if (fVar10 < (float)uRamfef24652 * 3.0517578e-05) {
        bRamfef26058 = bRamfef26058 & 0xfd | 4;
        if (cRamfef26388 == '\0') goto LAB_ram_000ee048;
        if (bRamfef2638b == 0) {
          func_0x000ed816();
        }
        else {
          func_0x000ed834();
        }
      }
      goto LAB_ram_000ee07a;
    }
    uVar3 = uRamfef24634;
    if ((cRamfef26388 == '\0') ||
       ((fVar4 = (float)uRamfef24638, fVar4 * 0.0009765625 < fVar10 &&
        ((uVar3 = uRamfef24638, cRamfef2638a == '\0' || (cRamfef2638a == '\x04')))))) {
      uRamfef2605c = 3;
      func_0x000ed850(uVar3,fVar4);
      bRamfef26058 = bRamfef26058 | 2;
      cRamfef2605d = '\x03';
    }
    else {
      if (bRamfef2638b != 3) {
        if (((float)uRamfef24652 * 3.0517578e-05 <= fVar10) || (cRamfef2638a != '\0')) {
          cRamfef2605d = cRamfef2638a;
          if ((bRamfef26058 & 0x80) == 0) {
            if ((bRamfef26059 & 1) == 0) {
              if ((bRamfef26059 & 2) == 0) {
                if ((bRamfef26058 & 1) != 0) {
                  if (dRamfef26060 <=
                      (double)(((float)uRamfef24648 * 3.0517578e-05) / _UNK_ram_001805f0)) {
                    if ((bool)uRamfef2604e) goto LAB_ram_000ee012;
                    uRamfef2605c = 2;
                    dRamfef26060 = 0.0;
                    bRamfef26058 = bRamfef26058 & 0xfe | 0x80;
                  }
                  else {
                    uRamfef2605c = 1;
                    bRamfef26058 = bRamfef26058 & 0xfe;
                    bRamfef26059 = bRamfef26059 | 2;
                    dRamfef26060 = 0.0;
                  }
                }
              }
              else if (!bVar2 && !bVar1) {
                bRamfef26059 = bRamfef26059 & 0xfd | 1;
              }
            }
            else if (dRamfef26060 <=
                     (double)(((float)uRamfef2464a * 3.0517578e-05) / _UNK_ram_001805f0)) {
              if (bVar2 || bVar1) {
                uRamfef2605c = 1;
                bRamfef26059 = bRamfef26059 & 0xfe | 2;
                dRamfef26060 = 0.0;
              }
              else {
LAB_ram_000ee012:
                dRamfef26060 = dRamfef26060 + 1.0;
              }
            }
            else {
              bRamfef26058 = bRamfef26058 | 0x80;
              uRamfef2605c = 2;
              bRamfef26059 = bRamfef26059 & 0xfe;
              dRamfef26060 = 0.0;
            }
          }
          else if ((bool)uRamfef2604e) {
            bRamfef26058 = bRamfef26058 & 0x7f | 1;
          }
        }
        else {
          func_0x000ed850(uRamfef24638,fVar4);
          bRamfef26058 = bRamfef26058 | 4;
          func_0x000ed816();
        }
        goto LAB_ram_000ee07a;
      }
      uRamfef2605c = 0;
      func_0x000ed850(uRamfef24638,fVar4);
      bRamfef26058 = bRamfef26058 | 2;
      cRamfef2605d = '\x03';
    }
LAB_ram_000edebc:
    cRamfef2605e = '\x01';
  }
  else {
    if (cRamfef26388 == '\0') {
      if ((bRamfef26058 & 8) == 0) {
        if ((bRamfef26058 & 0x10) != 0) {
          bRamfef26058 = bRamfef26058 & 0xef;
        }
      }
      else {
        bRamfef26058 = bRamfef26058 & 0xf7;
      }
LAB_ram_000ee048:
      uRamfef2605c = 3;
      bRamfef26058 = bRamfef26058 | 0x20;
      cRamfef2605d = cRamfef2638a;
      goto LAB_ram_000edebc;
    }
    if ((bRamfef26058 & 8) == 0) {
      if ((bRamfef26058 & 0x10) == 0) {
        if ((bRamfef26058 & 0x20) != 0) {
          bRamfef26058 = bRamfef26058 & 0xdf;
          func_0x000ed834();
        }
      }
      else {
        if (bRamfef2638b != 0) {
          uRamfef2605c = 2;
          cRamfef2605d = cRamfef2638a;
          dRamfef26060 = 0.0;
          cRamfef2605e = '\0';
          bRamfef26058 = bRamfef26058 & 0xeb | 0xc0;
          uVar3 = uRamfef2464e;
          fVar10 = fRamfef26494;
          goto LAB_ram_000ee08e;
        }
        cRamfef2605d = cRamfef2638a;
      }
    }
    else if (bRamfef2638b == 0) {
      bRamfef26058 = bRamfef26058 & 0xf7;
      func_0x000ed816();
    }
LAB_ram_000ee07a:
    uVar3 = uRamfef2464e;
    fVar10 = fRamfef26494;
    if (cRamfef2605e == '\0') goto LAB_ram_000ee08e;
  }
  fVar12 = 0.00048828125;
  uVar3 = uRamfef2465c;
  fVar10 = 0.0;
LAB_ram_000ee08e:
  fVar10 = fVar10 - fRamfef26084;
  fVar9 = (float)uVar3 * fVar12 * fVar9;
  if (fVar10 <= fVar9) {
    fVar9 = -fVar9;
    fVar9 = (float)((uint)(fVar10 < fVar9) * (int)fVar9 | (uint)(fVar10 >= fVar9) * (int)fVar10);
  }
  fRamfef26084 = fRamfef26084 + fVar9;
  fVar9 = fRamfef2636c;
  if (cRamfef26389 != '\0') {
    fVar9 = fRamfef26084;
  }
  uRamfef26384 = (short)(int)(fVar9 * 512.0);
  cRamfef26387 = cRamfef2638a;
  if (cRamfef26389 != '\0') {
    cRamfef26387 = cRamfef2605d;
  }
  uRamfef26386 = 1;
  if (cRamfef26389 != '\0') {
    uRamfef26386 = uRamfef2605c;
  }
  fRamfef26468 = fRamfef26464;
  fRamfef2647c = fRamfef26478;
  fRamfef26474 = (float)dRamfef26060;
  fRamfef26450 = fRamfef2644c;
  cRamfef26088 = cRamfef2605e;
  uRamfef2649c = (short)(int)(fVar13 * 2048.0);
  fRamfef26458 = fRamfef26454;
  cRamfef2607c = 0;
  fRamfef26448 = fRamfef26444;
  uRamfef2649a = (short)(int)(fVar11 * 512.0);
  return;
}
