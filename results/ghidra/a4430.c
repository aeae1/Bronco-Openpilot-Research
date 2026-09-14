
undefined4 FUN_ram_000a4430(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  param_1 = param_1 & 0xff;
  uVar1 = 1;
  if ((&UNK_ram_0004b08a)[param_1 * 3] == '\0') {
    (**(code **)(&UNK_ram_0004afa4 +
                (uint)(byte)(&UNK_ram_0004b172)[(uint)(byte)(&UNK_ram_0004b088)[param_1 * 3] * 5] *
                0x28))((&UNK_ram_0004b170)[(uint)(byte)(&UNK_ram_0004b088)[param_1 * 3] * 5]);
    uVar1 = 0;
  }
  else if ((&UNK_ram_0004b08a)[param_1 * 3] == '\x01') {
    FUN_ram_000a439c();
    uVar1 = (**(code **)(&UNK_ram_0004afb8 +
                        (uint)(byte)(&UNK_ram_0004b172)
                                    [(uint)(byte)(&UNK_ram_0004b088)[param_1 * 3] * 5] * 0x28))
                      ((&UNK_ram_0004b170)[(uint)(byte)(&UNK_ram_0004b088)[param_1 * 3] * 5],param_2
                      );
    FUN_ram_000a43ac(param_1);
  }
  return uVar1;
}

