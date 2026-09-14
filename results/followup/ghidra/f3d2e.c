void FUN_ram_000f3d2e(void)

{
  char cVar1;

  cVar1 = bRamfef20820 * (bRamfef20820 < bRam0017f438);
  bRamfef20820 = cVar1 + 1;
  uRamfef21224 = (bRamfef20820 & 1) == 0;
  cRamfef21226 = '\x01';
  cRamfef21225 = (cVar1 + 2U & 1) == 0;
  cRamfef21227 = cRamfef21225;
  cRamfef21228 = uRamfef21224;
  if ((bool)uRamfef21224) {
    func_0x001187e2();
  }
  if (cRamfef21225 != '\0') {
    func_0x00119358();
  }
  if (cRamfef21226 != '\0') {
    func_0x0011aa5c();
  }
  if (cRamfef21227 != '\0') {
    func_0x0011b0c0();
  }
  if (cRamfef21228 != '\0') {
    func_0x000f6796();
  }
  return;
}
