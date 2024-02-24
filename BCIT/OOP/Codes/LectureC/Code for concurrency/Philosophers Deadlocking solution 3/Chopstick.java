//: concurrency/Chopstick.java
// Chopsticks for dining philosophers.
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
public class Chopstick {
  private boolean taken = false;
  private Lock lock = new ReentrantLock();
  public  boolean take() throws InterruptedException {
	  if(lock.tryLock()){
		while(taken)
			wait();
		taken = true;
		return true;
	  }else
		  return false;
  }
  public  void drop() {
	  lock.unlock();
    taken = false;
    notifyAll();
  }
} ///:~
