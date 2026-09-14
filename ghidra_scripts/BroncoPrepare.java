import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.lang.Register;
import java.io.*;
import java.math.BigInteger;
import java.nio.file.*;

public class BroncoPrepare extends GhidraScript {
 public void run() throws Exception {
  String root=getScriptArgs()[0];
  MemoryBlock rom=currentProgram.getMemory().getBlock(toAddr(0x40000));
  rom.setWrite(false);rom.setExecute(true);
  for(String[] spec:new String[][]{{"cal_small","1c0000","NB3C-14D004-AD_block0_0x101C0000.bin"},{"cal_main","1d0000","NB3C-14D007-AAB_block0_0x101D0000.bin"}}){
   try(InputStream in=new FileInputStream(root+"/results/"+spec[2])){
    long size=Files.size(Path.of(root,"results",spec[2]));
    MemoryBlock block=currentProgram.getMemory().createInitializedBlock(spec[0],toAddr(Long.parseLong(spec[1],16)),in,size,monitor,false);
    block.setRead(true);block.setWrite(false);block.setExecute(false);
   }
  }
  MemoryBlock ram=currentProgram.getMemory().createUninitializedBlock("ram",toAddr(0xfeb00000L),0x00500000,false);
  ram.setRead(true);ram.setWrite(true);ram.setExecute(false);
  for(String[] spec:new String[][]{{"gp","febffe7c"},{"tp","48a00"}}){
   Register reg=currentProgram.getRegister(spec[0]);
   if(reg!=null){currentProgram.getProgramContext().setValue(reg,toAddr(0x40000),toAddr(0x1fffff),new BigInteger(spec[1],16));}
  }
  println("STATIC STARTUP EVIDENCE: CPU ROM base 0x40000; gp=0xfebffe7c; tp=0x48a00. Hardware/vehicle match remains unverified.");
  var opts=currentProgram.getOptions("Analysis");
  for(String opt:opts.getOptionNames())if(opt.equals("Decompiler Parameter ID")||opt.equals("Call Convention ID")||opt.equals("Function Start Search"))opts.setBoolean(opt,false);
  int n=0;
  for(String line:Files.readAllLines(Path.of(root,"results","seed_addresses.txt"))){
   Address a=toAddr(Long.parseLong(line.trim(),16));
   disassemble(a);
   if(getFunctionAt(a)==null)createFunction(a,null);
   n++;
  }
  println("BroncoPrepare seed attempts="+n);
 }
}
