class Dog implements Runnable{
	private Object lock;
	private static int idcount = 0;
	private int id;
	public Dog(Object o){
		lock = o;
		id = idcount++;
	}
	public void run(){
			try{
			synchronized(lock){
				lock.wait();
			}
			}catch(Exception e){
				System.out.println("lock failed"+e);
			}
			System.out.println("dog id="+id+" running");
	}
}
public class Kennel {
	public static void main(String[] args){
		Object l = new Object();
		
		for (int i=0; i<5; i++)
			new Thread(new Dog(l)).start();
		
		System.out.println("dogs at start gate");
		try{
		for (int i=5; i>=0; i--){
			Thread.sleep(500);
			System.out.println(""+i);
		}
		}catch(Exception e){}
		synchronized(l){
			l.notifyAll();
		}
	}
}