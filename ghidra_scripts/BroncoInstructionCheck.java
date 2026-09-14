import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import java.nio.file.*;
import java.util.*;

/** Executes two isolated firmware instructions in virtual memory; no hardware access. */
public class BroncoInstructionCheck extends GhidraScript {
  private String hex(byte[] b) {
    StringBuilder s = new StringBuilder();
    for (byte v : b) s.append(String.format("%02x", v & 255));
    return s.toString();
  }
  public void run() throws Exception {
    StringBuilder out = new StringBuilder("instruction\tregister\tvalue\tbefore\tafter\texpected\tpass\n");
    long[] addresses = {0xd0910, 0xd0cac};
    String[] registers = {"r7", "r18"};
    long[] values = {0x12345678L, 0x0004be4cL, 0xfebf62c4L, 0xfebf6388L, 0, 0xffffffffL};
    for (int n = 0; n < addresses.length; n++) {
      for (long value : values) {
        EmulatorHelper emu = new EmulatorHelper(currentProgram);
        try {
          byte[] before = new byte[12];
          Arrays.fill(before, (byte)0xa5);
          byte[] expected = before.clone();
          for (int i = 0; i < 4; i++) expected[4+i] = (byte)(value >>> (8*i));
          emu.writeMemory(toAddr(0xfebee5ccL), before);
          emu.writeRegister("gp", 0xfebffe7cL);
          emu.writeRegister(registers[n], value);
          emu.writeRegister(emu.getPCRegister(), addresses[n]);
          if (!emu.step(monitor)) throw new IllegalStateException(emu.getLastError());
          byte[] after = emu.readMemory(toAddr(0xfebee5ccL), 12);
          out.append(String.format("0x%x\t%s\t0x%08x\t%s\t%s\t%s\t%s\n", addresses[n],
              registers[n], value, hex(before), hex(after), hex(expected), Arrays.equals(after, expected)));
        } finally { emu.dispose(); }
      }
    }
    Files.writeString(Path.of(getScriptArgs()[0]), out);
    println(out.toString());
  }
}
