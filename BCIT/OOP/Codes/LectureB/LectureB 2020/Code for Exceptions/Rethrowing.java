//: c10:Rethrowing.java
// From 'Thinking in Java, 2nd ed.' by Bruce Eckel
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
// Demonstrating fillInStackTrace()

public class Rethrowing {
  public static void f() throws Exception {
    System.out.println(
      "originating the exception in f()");
    throw new Exception("thrown from f()");
  }
  public static void g() throws Throwable {
    try {
      f();
	  System.out.println("after F");
    } catch(Exception e) {
      System.err.println(
        "Inside g(), e.printStackTrace()");
      e.printStackTrace(System.err);
      throw e; // 17
     //  throw e.fillInStackTrace(); // 18
    }
	System.out.println("End of G");
  }
  public static void
  main(String[] args) throws Throwable {
    try {
      g();
	  System.out.println("after G");
    } catch(Exception e) {
      System.err.println(
        "Caught in main, e.printStackTrace()");
      e.printStackTrace(System.err);
    }
	System.out.println("end of main");
  }
} ///:~