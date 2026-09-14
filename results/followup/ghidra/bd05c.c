uint FUN_ram_000bd05c(void)

{
  uint uVar1;

  uVar1 = (uint)(cRamfebeed62 != '\0');
  if (cRamfebeec89 != '\0') {
    uVar1 = uVar1 | 2;
  }
  if (cRamfebeec8a != '\0') {
    uVar1 = uVar1 | 4;
  }
  if (cRamfebeecc4 != '\0') {
    uVar1 = uVar1 | 8;
  }
  if (cRamfebeecd0 != '\0') {
    uVar1 = uVar1 | 0x10;
  }
  if (cRamfebeecc7 != '\0') {
    uVar1 = uVar1 | 0x20;
  }
  if (cRamfebeecd1 != '\0') {
    uVar1 = uVar1 | 0x40;
  }
  if (cRamfebeece7 != '\0') {
    uVar1 = uVar1 | 0x80;
  }
  if (cRamfebeec84 != '\0') {
    uVar1 = uVar1 | 0x100;
  }
  if (cRamfebeecf9 != '\0') {
    uVar1 = uVar1 | 0x200;
  }
  if (cRamfebeec61 != '\0') {
    uVar1 = uVar1 | 0x400;
  }
  if (cRamfebeeca9 != '\0') {
    uVar1 = uVar1 | 0x800;
  }
  if (cRamfebeecb1 != '\0') {
    uVar1 = uVar1 | 0x1000;
  }
  if (cRamfebeecca != '\0') {
    uVar1 = uVar1 | 0x2000;
  }
  if (cRamfebeecd2 != '\0') {
    uVar1 = uVar1 | 0x4000;
  }
  if (cRamfebeeccd != '\0') {
    uVar1 = uVar1 | 0x8000;
  }
  if (cRamfebeecd3 != '\0') {
    uVar1 = uVar1 | 0x10000;
  }
  if (cRamfebeed05 != '\0') {
    uVar1 = uVar1 | 0x20000;
  }
  if (cRamfebeec9f != '\0') {
    uVar1 = uVar1 | 0x40000;
  }
  if (cRamfebeedd0 != '\0') {
    uVar1 = uVar1 | 0x80000;
  }
  if (cRamfebeec87 != '\0') {
    uVar1 = uVar1 | 0x100000;
  }
  if (cRamfebeeca1 != '\0') {
    uVar1 = uVar1 | 0x200000;
  }
  if (cRamfebeed4b != '\0') {
    uVar1 = uVar1 | 0x400000;
  }
  if (cRamfebeec85 != '\0') {
    uVar1 = uVar1 | 0x800000;
  }
  if (cRamfebeecbe != '\0') {
    uVar1 = uVar1 | 0x1000000;
  }
  if (cRamfebeecd7 != '\0') {
    uVar1 = uVar1 | 0x2000000;
  }
  if (cRamfebeed01 != '\0') {
    uVar1 = uVar1 | 0x4000000;
  }
  if (cRamfebeec86 != '\0') {
    uVar1 = uVar1 | 0x8000000;
  }
  if (cRamfebeec75 != '\0') {
    uVar1 = uVar1 | 0x10000000;
  }
  if (cRamfebeec78 != '\0') {
    uVar1 = uVar1 | 0x20000000;
  }
  if (cRamfebeec7b != '\0') {
    uVar1 = uVar1 | 0x40000000;
  }
  if (cRamfebeec7a != '\0') {
    return uVar1 | 0x80000000;
  }
  return uVar1;
}
