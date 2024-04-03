public class SimpleThreadExample extends Thread implements Runnable{
	private static int task = 0;
	private final int id = task++;
	public static int store = 1;
	public void run(){
		int timewaste = 99999;
		for(int count = 0; count<10; count++){
			for(int i=0;i<timewaste;i++);
			System.out.println("id="+id+" count="+count);
		}

		if(decStore()){
			System.out.println("id = "+id+" yay deleted store "+store);
		}
		else{
			System.out.println("id = "+id+" boo deleted store "+store);
		}
	
	}

	public synchronized boolean decStore(){
		if(store>0){
			try{
				Thread.sleep(10);
			} catch (Exception e) {}
			store--;
			return true;
		}
		else{
			return false;
		}
	}


	public static void main(String[] args){
			SimpleThreadExample s1= new SimpleThreadExample();
			SimpleThreadExample s2 = new SimpleThreadExample();
			s1.start();
			s2.start();
			try{
				s1.join();
				s2.join();
			}catch(Exception e){}
			
			System.out.println("end of program");
	
	}
}
