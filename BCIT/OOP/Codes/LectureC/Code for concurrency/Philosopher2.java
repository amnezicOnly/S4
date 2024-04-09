//: concurrency/Philosopher.java
// A dining philosopher
import java.util.concurrent.*;
import java.util.*;
//import static net.mindview.util.System.out.print.*;

public class Philosopher2 implements Runnable {
  private Chopstick left;
  private Chopstick right;
  private final int id;
  private final int ponderFactor;
  private Random rand = new Random(47);
  private Semaphore room;
  
  private void pause() throws InterruptedException {
    if(ponderFactor == 0) return;
    TimeUnit.MILLISECONDS.sleep(
      rand.nextInt(ponderFactor * 250));
  }
  public Philosopher2(Chopstick left, Chopstick right,
    int ident, int ponder, Semaphore r) {
    this.left = left;
    this.right = right;
    id = ident;
	room = r;
    ponderFactor = ponder;
  }
  public void run() {
    try {
      while(!Thread.interrupted()) {
		room.acquire();
        System.out.print(this + " " + "thinking");
        pause();
        // Philosopher becomes hungry
        System.out.print(this + " " + "grabbing right");
        right.take();
        System.out.print(this + " " + "grabbing left");
        left.take();
        System.out.print(this + " " + "eating");
        pause();
        right.drop();
        left.drop();
		room.release();
      }
    } catch(InterruptedException e) {
      System.out.print(this + " " + "exiting via interrupt");
    }
  }
  public String toString() { return "Philosopher " + id; }
} ///:~
