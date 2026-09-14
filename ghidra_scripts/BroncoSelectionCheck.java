import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import java.nio.file.*;
import java.util.*;

/** Virtual-memory checks of selected startup copies and a command-source branch. */
public class BroncoSelectionCheck extends GhidraScript {
  private long u32(long address) throws Exception {
    return Integer.toUnsignedLong(currentProgram.getMemory().getInt(toAddr(address)));
  }
  private void until(EmulatorHelper emu, long... stops) throws Exception {
    for (int n = 0; n < 30000; n++) {
      long pc = emu.getExecutionAddress().getOffset();
      for (long stop : stops) if (pc == stop) return;
      if (!emu.step(monitor)) throw new IllegalStateException(emu.getLastError());
    }
    throw new IllegalStateException("Instruction budget exceeded");
  }
  public void run() throws Exception {
    StringBuilder out = new StringBuilder();
    EmulatorHelper emu = new EmulatorHelper(currentProgram);
    try {
      emu.writeRegister("gp", 0xfebffe7cL);
      emu.writeRegister("tp", 0x48a00L);
      out.append("copy_record\tdestination\tsource\tlength\texact_copy\tguards_intact\n");
      for (long record : new long[]{0x11c068, 0x11cbb4, 0x11cbc0}) {
        long dest = u32(record), src = u32(record + 4);
        int len = Short.toUnsignedInt(currentProgram.getMemory().getShort(toAddr(record + 8)));
        byte[] expected = new byte[len];
        currentProgram.getMemory().getBytes(toAddr(src), expected);
        byte[] fill = new byte[len + 8]; Arrays.fill(fill, (byte)0xa5);
        emu.writeMemory(toAddr(dest - 4), fill);
        emu.writeRegister("r6", dest); emu.writeRegister("r7", src); emu.writeRegister("r8", len);
        emu.writeRegister("lp", 0x40000);
        emu.writeRegister(emu.getPCRegister(), 0xde040);
        until(emu, 0x40000);
        boolean equal = Arrays.equals(expected, emu.readMemory(toAddr(dest), len));
        byte[] guards = {(byte)0xa5,(byte)0xa5,(byte)0xa5,(byte)0xa5};
        boolean intact = Arrays.equals(guards, emu.readMemory(toAddr(dest - 4), 4))
            && Arrays.equals(guards, emu.readMemory(toAddr(dest + len), 4));
        out.append(String.format("0x%x\t0x%x\t0x%x\t%d\t%s\t%s\n",record,dest,src,len,equal,intact));
        if (!equal || !intact) throw new IllegalStateException("Copy check failed");
      }
      int flag = emu.readMemoryByte(toAddr(0xfef23886L)) & 255;
      int expectedCode = emu.readMemoryByte(toAddr(0xfef23887L)) & 255;
      int actualCode = emu.readMemoryByte(toAddr(0xfebf6b0eL)) & 255;
      if (flag != 0 || expectedCode != 1 || actualCode != 1)
        throw new IllegalStateException("Unexpected initialized selector bytes");
      out.append("\ncase\tflag\texpected_code\tinput_code\tbranch\tpass\n");
      int[][] cases = {{flag,expectedCode,actualCode,1},{0,1,0,0},{1,1,0,1},{0,1,2,0}};
      String[] labels = {"sample_startup_defaults", "virtual_mismatch_zero", "virtual_nonzero_flag", "virtual_mismatch_two"};
      for (int i = 0; i < cases.length; i++) {
        int[] c = cases[i];
        emu.writeMemoryValue(toAddr(0xfef23886L), 1, c[0]);
        emu.writeMemoryValue(toAddr(0xfef23887L), 1, c[1]);
        emu.writeMemoryValue(toAddr(0xfebf6b0eL), 1, c[2]);
        // Start at the selector getter call; stop before either command-data getter.
        emu.writeRegister(emu.getPCRegister(), 0xf3e44);
        until(emu, 0xf3ea0, 0xf3e80);
        boolean lmc2 = emu.getExecutionAddress().getOffset() == 0xf3ea0;
        boolean pass = lmc2 == (c[3] == 1);
        out.append(String.format("%s\t%d\t%d\t%d\t%s\t%s\n",labels[i],c[0],c[1],c[2],lmc2?"LMC2":"alternate",pass));
        if (!pass) throw new IllegalStateException("Selection check failed");
      }
      Files.writeString(Path.of(getScriptArgs()[0]), out);
      println(out.toString());
    } finally { emu.dispose(); }
  }
}
