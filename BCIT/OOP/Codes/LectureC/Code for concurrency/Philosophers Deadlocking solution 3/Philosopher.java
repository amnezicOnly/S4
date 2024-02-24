//: concurrency/Philosopher.java
// A dining philosopher
import java.util.concurrent.*;
import java.util.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Lock;
//import static net.mindview.util.System.out.print.*;

public class Philosopher implements Runnable {
  private Chopstick left;
  private Chopstick right;
  private Chopsticks chopsticks;
  private final int id;
  private final int ponderFactor;
  private Random rand = new Random(47);
  private Lock lock1 = new ReentrantLock();
  private Lock lock2 = new ReentrantLock();
  private boolean eatten = false;
  
  private void pause() throws InterruptedException {
    if(ponderFactor == 0) return;
    TimeUnit.MILLISECONDS.sleep(
      rand.nextInt(ponderFactor * 10));
  }
  public Philosopher(Chopstick left, Chopstick right,
    int ident, int ponder) {
    this.left = left;
    this.right = right;
	chopsticks = new Chopsticks(left, right);
    id = ident;
    ponderFactor = ponder;
  }
  public void run() {
    try {
      while(!Thread.interrupted()) {
        System.out.print(this + " " + "thinking");
        pause();
        // Philosopher becomes hungry
        chopsticks.take();
      }
    } catch(InterruptedException e) {
      System.out.print(this + " " + "exiting via interrupt");
    }
  }
  public String toString() { return "Philosopher " + id; }
} ///:~
