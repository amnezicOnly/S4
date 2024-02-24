

public class Jungle {
  static Animal a;
  static Animal []bag;
  static Tiger t;
  static Dog d;
  static Snake s;
  public static void main(String[] args){
    bag = new Animal[10];
    t = new Tiger();
    d = new Dog();
    s = new Snake();
    System.out.println("get tiger to move");
    t.move();
    System.out.println("get snake to move");
    s.move();
    System.out.println("hold onto tiger with Animal reference");
    a = t;
    System.out.println("Use Animal reference to get Tiger to move");
    a.move();
    //Try to get Tiger object to growl - if you do you'll get an error - try it
    //Try to put Tiger object back onto the Tiger reference
    System.out.println("Fill up animal bag");
    fillBag();
    System.out.println("see how each animal moves");
    for(int i=0; i<bag.length; i++)
      bag[i].move();
    //Since Dog and Tiger seem so similar try to stuff a Dog into a Tiger
    //If you do, you'll get an error - try it!
  }
  public static void fillBag(){
    int choice=0;
    for(int i=0; i<bag.length; i++){
      choice = (int)(Math.random()*3+1);
      switch(choice){
        case 1:
          bag[i] = new Dog();
          break;
        case 2:
          bag[i] = new Snake();
          break;
        case 3:
          bag[i] = new Tiger();
      }//switch
    }//for i=0
  }//fillBag()
}