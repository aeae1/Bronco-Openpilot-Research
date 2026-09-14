
void FUN_ram_000a41f0(byte param_1)

{
  if (((char)DAT_ram_feede6f0 != '\0') && (param_1 < 0x2c)) {
    FUN_ram_000a44aa();
    return;
  }
  return;
}

