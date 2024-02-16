public class GenericTest{
	public void print(String s){
		System.out.println(s);
	}
	public int min(int a, int b, int c){
		int result = a;
		if (result > b)
			result = b;
		if (result > c)
			result = c;
		return result;
	}
	public void copy(Object[] a, Object[] b){
		System.arraycopy(a,0,b,0,a.length);
	}
	public static void main(String[] args){
		GenericTest g = new GenericTest();
		g.print("hi");
		System.out.println(""+g.min(5,3,12));
	}
}
		