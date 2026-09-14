import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.*;

/** Offline excerpts from a local analysis project. Never connects to a vehicle. */
public class BroncoTrace extends GhidraScript {
  public void run() throws Exception {
    String[] args = getScriptArgs();
    Path out = Path.of(args[0]);
    Files.createDirectories(out);
    DecompInterface di = new DecompInterface();
    if (!di.openProgram(currentProgram)) throw new IllegalStateException(di.getLastMessage());
    try {
      StringBuilder refs = new StringBuilder("target\tfrom\ttype\tcontaining_function\n");
      for (String hex : args[1].split(",")) {
        var a = toAddr(Long.parseUnsignedLong(hex, 16));
        Function f = getFunctionAt(a);
        if (f == null) { disassemble(a); f = createFunction(a, null); }
        if (f == null) { println("NO_FUNCTION " + hex); continue; }
        StringBuilder asm = new StringBuilder("# language=" + currentProgram.getLanguageID() + "\n");
        var it = currentProgram.getListing().getInstructions(f.getBody(), true);
        while (it.hasNext()) {
          Instruction ins = it.next();
          asm.append(ins.getAddress()).append("  ");
          for (byte b : ins.getBytes()) asm.append(String.format("%02x", b & 255));
          asm.append("  ").append(ins).append("\n");
        }
        Files.writeString(out.resolve(hex + ".asm"), asm);
        var dec = di.decompileFunction(f, 45, monitor);
        String c = dec.getDecompiledFunction() == null
            ? "FAILED: " + dec.getErrorMessage() : dec.getDecompiledFunction().getC();
        // Normalize presentation whitespace only; assembly retains instruction bytes.
        Files.writeString(out.resolve(hex + ".c"), c.replaceAll("(?m)[ \\t]+$", "").strip() + "\n");
        var ri = currentProgram.getReferenceManager().getReferencesTo(a);
        while (ri.hasNext()) {
          Reference r = ri.next();
          Function caller = getFunctionContaining(r.getFromAddress());
          refs.append(a).append('\t').append(r.getFromAddress()).append('\t')
              .append(r.getReferenceType()).append('\t')
              .append(caller == null ? "" : caller.getEntryPoint()).append('\n');
        }
        println("EXPORTED " + hex + " bytes=" + f.getBody().getNumAddresses()
            + " decompiled=" + dec.decompileCompleted());
      }
      Files.writeString(out.resolve("function_references.tsv"), refs);
    } finally { di.dispose(); }
  }
}
