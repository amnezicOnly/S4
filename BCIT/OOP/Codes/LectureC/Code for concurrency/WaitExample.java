public class WaitExample {
	private int data = 0;
	Object lock = new Object();
	MThread x = new MThread("One", true);
	MThread y = new MThread("Two", false);
	public   void add(int d){
		synchronized(lock){
			data = d;
			lock.notify();
		}
	}
	public   int remove(){
		int temp = 0;
		synchronized(lock){
		try{
		lock.wait();
		}catch(Exception e){}
		temp = data;
		data = 0;
		}
		return temp;
	}
	public void go(){
		x.start();
		y.start();
	}
	class MThread extends Thread{
		String name;
		boolean add = true;
		public MThread(String n, boolean a){
			name = n;
			add = a;
		}
		public void run(){
			for(int i=0;i<20;i++){
				if (add){
					System.out.println(name+" adding to data "+data);
					add(1);
				}else
					System.out.println(name+" removing from data "+remove());
			}
		}
	}
	public static void main(String[] args){
		WaitExample w = new WaitExample();
		w.go();
	}
}