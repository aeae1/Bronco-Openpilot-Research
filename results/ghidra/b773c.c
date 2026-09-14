
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000b773c(undefined4 *param_1)

{
  longlong lVar1;
  
  thunk_EXT_FUN_ram_00000030();
  lVar1 = CONCAT44(_DAT_ram_ffdd8044,_DAT_ram_ffdd8040);
  thunk_EXT_FUN_ram_00000030();
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = (int)(longlong)((double)lVar1 / 8000.0);
  }
  return;
}

