class Alarm {
	public synchronized void beep() throws Exception{
		System.out.println("BEEEEEP!");
		notifyAll();
	}
	public synchronized void tickTock() throws Exception{
		System.out.println("tick tock");
		wait();
	}
}
class Student implements Runnable{
	Alarm clock;
	public Student(Alarm a){
		clock = a;
	}
	public void run(){
		System.out.println("student sleeping");
		try{
			clock.tickTock();
			System.out.println("OK I AM AWAKE!");
		}
		catch(Exception e){	
			System.out.println("sleep interrupted");
		}
	}
}		
public class House {
	public static void main(String[] args){
		Alarm c = new Alarm();
		Student s = new Student(c);
		System.out.println("In bedroom");
		Thread t = new Thread(s);
		t.start();
		try{
			Thread.sleep(2000);
			c.beep();
		}catch(Exception e){}
	}
}
		