

interface Car {
  void drive();
}
interface Boat {
  void sail();
}
interface Vehicle {
  void turn();
}
class Hovercraft   implements Car, Boat ,Vehicle{
  public void drive(){
    System.out.println("drive on ground");
  }
  public void sail(){
    System.out.println("sail on water");
  }
  public void turn(){
    System.out.println("Turning vehicle");
  }
}
class Porche extends Vehicle implements Car{
  public void drive(){
    System.out.println("drive very fast - ZOOOM!");
  }
}
public class Transportation {
  public void testDrive(Car c){
    c.drive();
  }
  public void testSail(Boat b){
    b.sail();
  }
  public void testTurn(Vehicle v){
    v.turn();
  }
  public static void main(String []args){
    Transportation t = new Transportation();
    Porche p = new Porche();
    Hovercraft h = new Hovercraft();
    t.testDrive(p);
    t.testDrive(h);
    t.testSail(h);
    t.testTurn(p);
    t.testTurn(h);
  }
}
