import java.util.concurrent.*;
import java.util.concurrent.locks.*;

public class MyLockExample{
	ReentrantLock lock = new ReentrantLock();
	LThread a = new LThread("A");
	LThread b = new LThread("B");
	public void get(String name){
		try{
			while(!lock.tryLock(1,TimeUnit.SECONDS))
				System.out.println(name+" waiting for lock");
		}catch(InterruptedException i){}
		System.out.println(name+" got lock");
		try{
				Thread.sleep(3000);
		}catch(Exception e){}
		finally{
			System.out.println(name+" released lock");
			lock.unlock();
		}
	}
	class LThread extends Thread{
		String name;
		public LThread(String n){
			name = n;
			start();
		}
		public void run(){
			get(name);
		}
	}
	public static void main(String[] args){
		MyLockExample m = new MyLockExample();
	}
}
		