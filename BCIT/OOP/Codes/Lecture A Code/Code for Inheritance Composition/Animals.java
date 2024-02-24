class Animal {
	public void draw(){
		System.out.println("animal");
	}
}
class Dog extends Animal {
	public void draw(){
		System.out.println("dog");
	}
}
class Cat extends Animal {}
public class Animals{
	public static void main(String[] args){
		Animal a;
		a = new Cat();
		a.draw();
		a = new Dog();
		a.draw();
	}
}