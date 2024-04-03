public class Race extends Thread /*implements Runnable*/ {
	private static int task = 0;
	private final int id = task++;
	private static int jellybeans = 1;
	public static boolean getJellyBean(){
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
		System.out.println("id="+id+" jellybean success="+getJellyBean());
		System.out.println("id="+id+" number of jellybeans left="+jellybeans);
	}
	public static void main(String[] args){
		Race r1 = new Race();
		Race r2 = new Race();
		r1.start();
		r2.start();
		/*r1.start();
		try{
			r1.join();
		} catch (Exception e){}
		r2.start();
		try{
			r2.join();
		} catch (Exception e){}*/
	}
}

// id=1 attempting to get jellybean
// id=1 jellybean success=true
// id=1 number of jellybeans left=0

// id=1 attempting to get jellybean
// id=1 jellybean success=false
// id=1 number of jellybeans left=0
