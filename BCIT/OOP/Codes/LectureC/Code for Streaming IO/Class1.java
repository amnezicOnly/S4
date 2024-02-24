import java.io.Serializable;

public class Class1 implements Serializable{
        double d = 3.14;
        int i = 5;
        String s = "Hi there";
        public String toString(){
                return(""+d+" "+i+" "+s);
        }
}
