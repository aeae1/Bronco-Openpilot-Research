/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000ed662(void)

{
  int iVar1;
  uint uVar2;

  uRamfef26428 = uRamfef24626;
  uRamfef2642c = uRamfef2462a;
  if (cRamfef24628 != '\0') {
    uRamfef26428 = uRamfef26384;
    uRamfef2642c = uRamfef26387;
  }
  func_0x000be206();
  if ((((sRamfef26054 < 1) || (0 < sRamfef26050)) || (sRamfef26054 == sRamfef26050)) ||
     (cRamfef26057 != '\0')) {
    cRamfef26057 = 0;
    iVar1 = 0;
    if (cRamfef26056 == '\0') {
      iVar1 = (int)sRamfef26426 + (uint)uRamfef26052;
    }
  }
  else {
    cRamfef26057 = 1;
    iVar1 = 0;
  }
  sRamfef26050 = sRamfef26054;
  sRamfef26426 = (short)(int)(1.0 / _UNK_ram_001805f0);
  if (iVar1 < 0xea6) {
    sRamfef26054 = -(ushort)(iVar1 < 1);
    uVar2 = iVar1 * (uint)(0 < iVar1) & 0xffff;
  }
  else {
    uVar2 = 0xea6;
    sRamfef26054 = 1;
  }
  uRamfef26052 = (ushort)uVar2;
  if (cRamfef24628 == '\0') {
    uRamfef2642a = (undefined1)uRamfef24624;
    uRamfef2642b = uRamfef24629;
  }
  else {
    uRamfef2642a = (undefined1)(uint)((ulonglong)((longlong)(int)uVar2 * 0x10624dd3) >> 0x24);
    uRamfef2642b = uRamfef26386;
  }
  func_0x000be0fa();
  cRamfef26056 = 0;
  return;
}
