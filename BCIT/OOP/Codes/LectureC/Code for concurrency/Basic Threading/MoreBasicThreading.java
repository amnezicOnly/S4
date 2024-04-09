

public class MoreBasicThreading {
	public static int MAX = 10;
	static class Dog implements Runnable{
		public void run(){
			for (int d = 0; d<MAX; d++){
				timewaster();
				System.out.println(" dog has run"+d);
			}
		}
	}
	static class Cat implements Runnable{
		public void run(){
			for (int d = 0; d<MAX; d++){
				timewaster();
				timewaster();
				System.out.println(" cat has run"+d);
			}
		}
	}
	private static void timewaster(){
		for(int i=0;i<9999;i++)
			for(int j=0; j<9999; j++);
	}
	public static void main(String[] args){
		Dog dog = new Dog();
		Cat cat = new Cat();
		Thread d = new Thread(dog);
		Thread c = new Thread(cat);
		d.start();
		c.start();
		System.out.println("race over");
	}
}
		
