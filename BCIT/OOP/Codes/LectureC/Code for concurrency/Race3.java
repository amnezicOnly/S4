public class Race3{
	public static boolean winner = false;
	public static int winnerID = -1;
	public static final int END = 5;
	public static  boolean isWinner(int pos, int ID){
		if (!winner)//if no winner yet
			if (pos >= END){//if pos of player past the END
				try{
					Thread.sleep(100);
				}catch(Exception e){}
				winner = true;
				winnerID = ID;
				return true;
			}
		return false;
	}
	static class Runner extends Thread{
		public int ID;
		public Runner(int id){
			ID = id;
		}
		public void jog(){
			for (int i=0;i<99999;i++)
				for(int j=0; j<99999;j++);
		}
		public void run(){
			for (int d = 0; d<=END; d++){
				if (winner) return;
				if (isWinner(d, ID)){
					System.out.println("Runner ID="+ID+" won the race");
					return;
				}
				jog();
			}
		}
	}
	public static void main(String[] args){
		Runner r1 = new Runner(1);
		Runner r2 = new Runner(2);
		System.out.println("start running");
		r1.start();
		r2.start();
		try{
			r1.join();
			r2.join();
		}catch(Exception e){}
		System.out.println("race over");
	}
}
		