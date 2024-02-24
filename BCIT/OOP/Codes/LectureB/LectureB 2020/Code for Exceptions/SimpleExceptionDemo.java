//: c10:SimpleExceptionDemo.java
// From 'Thinking in Java, 2nd ed.' by Bruce Eckel
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
// Inheriting your own exceptions.
class SimpleException extends Exception {} 
class MyOtherException extends Exception
{
}
class ExceptDemo
{
	  public void f() throws Exception {
    System.out.println(
      "Throwing SimpleException from f()");
    throw new SimpleException ();
  }

}
public class SimpleExceptionDemo extends ExceptDemo{
  public void f() throws SimpleException, MyOtherException {
    System.out.println(
      "Throwing SimpleException from f()");
    throw new SimpleException ();
  }
  public static void main(String[] args) {
    SimpleExceptionDemo sed = 
      new SimpleExceptionDemo();
    try {
      sed.f();
    } catch(Exception e) {
      System.err.println("Caught it!");
    }
  }
} ///:~