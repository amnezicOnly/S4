import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.TimeUnit;
public class MyLock{
	static ReentrantLock lock = new ReentrantLock();
	public static void main(String[] args) throws Exception{
		//Define a new thread type
		/////////////////////////////////////////////////////////////////
		Thread t = new Thread(){
			public void run(){
				try{
				Thread.sleep(1000);
				}catch(Exception ee){}
				boolean g = lock.tryLock();
				try{
					System.out.println("thread 2 got it");
					//Sleep to pretend working
					//////////////////////////
					try{
						Thread.sleep(5000);
					}catch(Exception er){}
					//////////////////////////
					
					System.out.println("slept for awhile");
					}
				catch(Exception e){}
				finally{
					if (g){//release lock if we got it
						System.out.println("unlock");
						lock.unlock();
					}
				}
				}};
		///////////////////////////////////////////////////////////
				t.start();
		
		//Main - sleep to simulate working in Main thread
		/////////////////////////////////////
		try{
			Thread.sleep(2000);
		}catch(Exception eee){}
		/////////////////////////////////////////////
		
		//Attempt to get the lock, if not available wait a period of time for it, if timeout give up
		boolean gotIt = lock.tryLock(6,TimeUnit.SECONDS);
		
		if (gotIt){
			try{
				System.out.println("Main thread got it, doing stuff");
				}
			finally{
				System.out.println("need to unlock");
				if (gotIt)
					lock.unlock();
			}
		}
		else
			System.out.println("Main did not get it");
	}
}