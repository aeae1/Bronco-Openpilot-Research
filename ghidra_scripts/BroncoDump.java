import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.io.*;
import java.util.*;

public class BroncoDump extends GhidraScript {
 public void run() throws Exception {
  Path out=Path.of(getScriptArgs()[0],"results","ghidra");Files.createDirectories(out);
  String[] addresses=getScriptArgs().length>1?getScriptArgs()[1].split(","):new String[]{"8549e","85532","85bc4","87138","872fc","85c2a","87198","87380","85c44","830ac","5f306","5f3f8","82ef0"};
  DecompInterface di=new DecompInterface();
  boolean opened=di.openProgram(currentProgram);println("DECOMPILER_OPEN="+opened+" "+di.getLastMessage());
  for(String hex:addresses){
   var a=toAddr(Long.parseLong(hex,16));Function f=getFunctionAt(a);
   if(f==null){disassemble(a);f=createFunction(a,null);}
   if(f==null){println("No function "+hex);continue;}
   var d=di.decompileFunction(f,40,monitor);
   String text=d.getDecompiledFunction()!=null?d.getDecompiledFunction().getC():"FAILED: "+d.getErrorMessage();
   Files.writeString(out.resolve(hex+".c"),text);
   StringBuilder asm=new StringBuilder();var ins=currentProgram.getListing().getInstructions(f.getBody(),true);
   while(ins.hasNext()){Instruction i=ins.next();asm.append(i.getAddress()).append("  ").append(i).append("\n");}
   Files.writeString(out.resolve(hex+".asm"),asm.toString());
   println("DUMP "+hex+" bytes="+f.getBody().getNumAddresses()+" decompile="+d.decompileCompleted()+" error="+d.getErrorMessage()+" last="+di.getLastMessage());
  }
  di.dispose();
  try(var w=Files.newBufferedWriter(out.resolve("functions.tsv"))){
   var it=currentProgram.getFunctionManager().getFunctions(true);
   while(it.hasNext()){Function f=it.next();w.write(f.getEntryPoint()+"\t"+f.getName()+"\t"+f.getBody().getNumAddresses()+"\n");}
  }
  println("FUNCTION_COUNT="+currentProgram.getFunctionManager().getFunctionCount());
 }
}
