class Cat {
 	Kitten k;
 	public Cat(){
  		System.out.println("cat");
 	}
 	static class Kitten{
  		public Kitten(){
   			System.out.println("kitten");
  		}
 	}
 	public void produce(Kitten kk){
   		k = kk;
 	}
}
public class Lion extends Cat {
 	public Lion(){
  		System.out.println("Lion");
  		produce(new Cat.Kitten());
 	}
 	class Kitten {
  		public Kitten(){
   			System.out.println("young Lion");
  		}
 	}
 	public static void main(String[] args){
  		new Lion();
 	}
}	
