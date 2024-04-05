//: innerclasses/BigEgg2.java
// Proper inheritance of an inner class.
//import static net.mindview.util.Print.*;

class Egg2 {
	public static void print(String x){
		System.out.println(x);
	}
  
  	protected class Yolk {
    		public Yolk() {
    			print("Egg2.Yolk()");
    		}
    
    		public void f() {
    			print("Egg2.Yolk.f()");
    		}
  	}
  
  	private Yolk y = new Yolk();
 	
 	public Egg2() { // --> pas d'autres appels, pourquoi l'instruction ligne 20 est exécutée avant ?
 		print("New Egg2()");
 	}
  	
  	public void insertYolk(Yolk yy) {
  		y = yy;
  	}
  	
  	public void g() {
  		y.f();
  	}
}	

public class BigEgg2 extends Egg2 {
	public class Yolk extends Egg2.Yolk {
		public Yolk() {
			print("BigEgg2.Yolk()");
		}
	
		public void f() {
			print("BigEgg2.Yolk.f()");
		}
  	}
  
	public BigEgg2() { // --> constructeur de Egg2
		insertYolk(new Yolk());
	}
	
	public static void main(String[] args) {
		Egg2 e2 = new BigEgg2(); // --> constructeur de BigEgg2
		e2.g();
	}
}
// POURQUOI ?
/* Output:
Egg2.Yolk()
New Egg2()
Egg2.Yolk()
BigEgg2.Yolk()
BigEgg2.Yolk.f()
*///:~
