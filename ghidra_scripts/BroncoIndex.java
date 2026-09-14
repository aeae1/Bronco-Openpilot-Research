import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.nio.file.*;
import java.io.*;

public class BroncoIndex extends GhidraScript {
 public void run() throws Exception {
  Path out=Path.of(getScriptArgs()[0],"results","ghidra");
  try(var w=Files.newBufferedWriter(out.resolve("instructions.tsv"))){
   var it=currentProgram.getListing().getInstructions(true);
   while(it.hasNext()){
    Instruction i=it.next();Function f=getFunctionContaining(i.getAddress());
    w.write(i.getAddress()+"\t"+(f==null?"":f.getEntryPoint())+"\t"+i+"\n");
   }
  }
  long start=Long.parseLong(getScriptArgs()[1],16),end=Long.parseLong(getScriptArgs()[2],16);
  DecompInterface di=new DecompInterface();di.openProgram(currentProgram);
  var fs=currentProgram.getFunctionManager().getFunctions(true);int count=0;
  while(fs.hasNext()){
   Function f=fs.next();long a=f.getEntryPoint().getOffset();
   if(a<start||a>=end)continue;
   var d=di.decompileFunction(f,20,monitor);
   if(d.getDecompiledFunction()!=null){
    Files.writeString(out.resolve(Long.toHexString(a)+".c"),d.getDecompiledFunction().getC());count++;
   }
  }
  di.dispose();println("INDEX written; decompiled="+count);
 }
}
