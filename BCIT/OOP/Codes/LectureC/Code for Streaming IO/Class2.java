import java.io.Serializable;

public class Class2 implements Serializable{
        String s = "Booo";
        Class1 c;
        boolean b = true;
        public Class2(){
                c = new Class1();
        }
        public String toString(){
                return(s+" "+b+" "+c.toString());
        }
}
