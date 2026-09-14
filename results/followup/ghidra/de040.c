uint * FUN_ram_000de040(uint *param_1,undefined8 *param_2,uint param_3)

{
  undefined1 uVar1;
  byte *pbVar2;
  uint *puVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  uint uVar7;
  undefined8 uVar8;
  uint uVar9;

  puVar3 = param_1;
  uVar4 = param_3;
  if (((uint)param_1 & 3) == 0) {
    if (((uint)param_2 & 3) == 0) {
      uVar9 = param_3 >> 4;
      if (uVar9 != 0) {
        do {
          uVar6 = *param_2;
          uVar8 = param_2[1];
          param_2 = param_2 + 2;
          *(undefined8 *)puVar3 = uVar6;
          *(undefined8 *)(puVar3 + 2) = uVar8;
          puVar3 = puVar3 + 4;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
        uVar4 = param_3 & 0xf;
        if ((param_3 & 0xf) == 0) {
          return param_1;
        }
      }
    }
    else {
      uVar9 = param_3 >> 2;
      if (uVar9 != 0) {
        do {
          pbVar2 = (byte *)((int)param_2 + 3);
          param_2 = (undefined8 *)((int)param_2 + 4);
          *puVar3 = (uint)*pbVar2;
          puVar3 = puVar3 + 1;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
        uVar4 = param_3 & 3;
        if ((param_3 & 3) == 0) {
          return param_1;
        }
      }
    }
  }
  else {
    uVar7 = -(int)param_2 & 3;
    uVar9 = param_3;
    if (uVar7 != 0) {
      uVar9 = param_3 - uVar7;
      if (param_3 <= uVar7) goto joined_r0x000de118;
      do {
        uVar1 = *(undefined1 *)param_2;
        param_2 = (undefined8 *)((int)param_2 + 1);
        *(undefined1 *)puVar3 = uVar1;
        puVar3 = (uint *)((int)puVar3 + 1);
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
    uVar7 = uVar9 >> 2;
    uVar4 = uVar9;
    if (uVar7 != 0) {
      do {
        uVar5 = *(undefined4 *)param_2;
        param_2 = (undefined8 *)((int)param_2 + 4);
        *(char *)puVar3 = (char)uVar5;
        *(char *)((int)puVar3 + 1) = (char)((uint)uVar5 >> 8);
        *(char *)((int)puVar3 + 2) = (char)((uint)uVar5 >> 0x10);
        *(char *)((int)puVar3 + 3) = (char)((uint)uVar5 >> 0x18);
        puVar3 = puVar3 + 1;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
      uVar4 = uVar9 & 3;
      if (uVar4 == 0) {
        return param_1;
      }
    }
  }
joined_r0x000de118:
  for (; uVar4 != 0; uVar4 = uVar4 - 1) {
    uVar1 = *(undefined1 *)param_2;
    param_2 = (undefined8 *)((int)param_2 + 1);
    *(undefined1 *)puVar3 = uVar1;
    puVar3 = (uint *)((int)puVar3 + 1);
  }
  return param_1;
}
