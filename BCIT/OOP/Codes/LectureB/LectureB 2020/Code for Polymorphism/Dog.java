

public class Dog extends Animal{
  public void move(){//override method inherited from Animal
    System.out.println("move like a Dog");
  }
  public void growl(){//new method for Dog
    System.out.println("GRRRRR");
  }
}