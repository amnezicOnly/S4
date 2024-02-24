class Holder {
	String s;
	public Holder(String string){
		setString(string);
	}
	public final void setString(String string){
		s = string;
	}
	public final String getString(){
		return s;
	}
}
public class Main {
	static Holder g1, g2;
	public static void swapper(Holder a, Holder b){
		String temp = a.getString();
		a.setString(b.getString());
		b.setString(temp);
	}
	public static void swap(Object a, Object b){
		Object temp = a;
		a = b;
		b = temp;
	}
	public static void main(String[] args){
		g1 = new Holder("hello");
		g2 = new Holder("goodbye");
		System.out.println(g1.getString());
		swapper(g1, g2);
		System.out.println(g1.getString());
		g1 = new Holder("hello");
		g2 = new Holder("goodbye");		
		swap(g1, g2);
		System.out.println(g1.getString());

	}
}
