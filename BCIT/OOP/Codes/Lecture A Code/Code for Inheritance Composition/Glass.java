abstract class Drink {
	public abstract void pour();
	public void drink(){
		System.out.println("burb");
	}
}
class Beer extends Drink {
	public void pour(){
		System.out.println("foam");
	}
}
class Juice extends Drink {
	public void pour(){
		System.out.println("slosh");
	}
	public void drink(){
		System.out.println("smack");
	}
}
class FruitBeer extends Beer {
	public void drink(){
		super.drink();
		System.out.println("blah");
	}
}
public class Glass {
	public static void main(String[] args){
		Drink d = new Juice();
		d.pour();
		d.drink();
		d = new Beer();
		d.pour();
		d.drink();
		d = new FruitBeer();
		d.pour();
		d.drink();
	}
}
