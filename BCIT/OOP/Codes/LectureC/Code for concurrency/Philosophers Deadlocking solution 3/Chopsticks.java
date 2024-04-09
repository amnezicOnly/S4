import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
import java.util.*;
import java.lang.Math;
public class Chopsticks{
	Chopstick left;
	Chopstick right;
	
	public Chopsticks(Chopstick l, Chopstick r){
		left = l;
		right = r;
	}
	public void take(){
		try{
		boolean eatten = false;
		while(!eatten){
		
			if(right.take()){
				System.out.println("grabbed right");
				if (left.take()){
					System.out.println("grabbed left");
					System.out.println("eatting");
					left.drop();
					right.drop();
				}else{
					right.drop();
				}
			}
			Thread.sleep((int)(Math.random() * 100));
		}
		}catch(Exception e){}
	}
}