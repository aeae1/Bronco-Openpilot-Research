void FUN_ram_000b8672(void)

{
  undefined *puVar1;
  uint uVar2;
  uint uVar3;
  undefined *puVar4;

  uVar2 = 0;
  do {
    puVar1 = (&PTR_DAT_ram_febee384_ram_0004af1c)[uVar2 * 2];
    puVar4 = (&PTR_DAT_ram_febf7e8c_ram_0004af20)[uVar2 * 2];
    for (uVar3 = 0; uVar3 < (uint)((int)puVar4 - (int)puVar1) >> 2; uVar3 = uVar3 + 1) {
      *(undefined4 *)(puVar1 + uVar3 * 4) = 0;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 2);
  for (uVar2 = 0; uVar2 < 0xcb4; uVar2 = uVar2 + 0xc & 0xffff) {
    func_0x000de040(*(undefined4 *)(&UNK_ram_0011bf30 + uVar2),
                    *(undefined4 *)(&UNK_ram_0011bf34 + uVar2),
                    *(undefined2 *)(&UNK_ram_0011bf38 + uVar2));
  }
  func_0x0006a410();
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}
