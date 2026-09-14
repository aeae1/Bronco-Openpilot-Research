void FUN_ram_000b77aa(int param_1,int *param_2)

{
  int local_10;

  FUN_ram_000b773c(&local_10);
  if (param_2 != (int *)0x0) {
    *param_2 = local_10 - param_1;
  }
  return;
}
