public class Race extends Thread {
	private static int task = 0;
	private final int id = task++;
	private Object lock = new Object();
	private static int jellybeans = 1;
	public synchronized static boolean getJellyBean(){
		if (jellybeans != 0){
			try{
			Thread.sleep(100);
			}catch(Exception e){}
			jellybeans--;
			return true;
		}
		return false;
	}
	public void run(){
		System.out.println("id="+id+" attempting to get jellybean");
		System.out.println("id="+id+"jellybean success="+getJellyBean());
		System.out.println("id="+id+"number of jellybeans left="+jellybeans);
	}
	public static void main(String[] args){
		Race r1 = new Race();
		Race r2 = new Race();
		r1.start();
		r2.start();
	}
}