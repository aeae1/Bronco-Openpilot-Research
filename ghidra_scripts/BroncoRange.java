import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.app.util.PseudoDisassembler;
import java.nio.file.*;

/** Lists instructions with bytes; optional linear mode is only an exploratory decode. */
public class BroncoRange extends GhidraScript {
  public void run() throws Exception {
    String[] args = getScriptArgs();
    StringBuilder out = new StringBuilder("address\tfunction\tbytes\tinstruction\n");
    for (String range : args[1].split(",")) {
      String[] ends = range.split(":");
      long start = Long.parseUnsignedLong(ends[0], 16);
      long end = Long.parseUnsignedLong(ends[1], 16);
      if (args.length > 2 && args[2].equals("linear")) {
        PseudoDisassembler pd = new PseudoDisassembler(currentProgram);
        for (long a = start; a < end;) {
          var ins = pd.disassemble(toAddr(a));
          if (ins == null) throw new IllegalStateException("No instruction at " + Long.toHexString(a));
          out.append(ins.getAddress()).append("\tLINEAR_CANDIDATE\t");
          for (byte b : ins.getBytes()) out.append(String.format("%02x", b & 255));
          out.append('\t').append(ins).append('\n');
          a += ins.getLength();
        }
        continue;
      }
      var it = currentProgram.getListing().getInstructions(toAddr(start), true);
      while (it.hasNext()) {
        Instruction ins = it.next();
        if (ins.getAddress().getOffset() >= end) break;
        Function f = getFunctionContaining(ins.getAddress());
        out.append(ins.getAddress()).append('\t').append(f == null ? "" : f.getEntryPoint()).append('\t');
        for (byte b : ins.getBytes()) out.append(String.format("%02x", b & 255));
        out.append('\t').append(ins).append('\n');
      }
    }
    Files.writeString(Path.of(args[0]), out);
  }
}
