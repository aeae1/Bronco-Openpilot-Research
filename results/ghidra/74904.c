
void FUN_ram_00074904(undefined4 param_1,undefined4 param_2,undefined4 param_3,ushort param_4,
                     ushort param_5,ushort param_6,ushort *param_7)

{
  *param_7 = ~((param_5 & 0xf) +
              (param_4 & 7) +
              (param_6 >> 8 & 7) + param_6 +
              ((ushort)((uint)param_3 >> 8) & 3) + (short)param_3 +
              ((ushort)((uint)param_2 >> 8) & 7) + (short)param_2 +
              ((ushort)((uint)param_1 >> 8) & 7) + (short)param_1) & 0xff;
  return;
}

