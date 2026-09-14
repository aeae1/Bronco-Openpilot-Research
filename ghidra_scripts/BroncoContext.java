import ghidra.app.script.GhidraScript;
import java.math.BigInteger;
public class BroncoContext extends GhidraScript {
 public void run() throws Exception {
  String[] a=getScriptArgs();
  for(int i=0;i<a.length;i+=2){
   currentProgram.getProgramContext().setValue(currentProgram.getRegister(a[i]),toAddr(0x40000),toAddr(0x1fffff),new BigInteger(a[i+1],16));
   println("Context "+a[i]+"="+a[i+1]);
  }
 }
}
