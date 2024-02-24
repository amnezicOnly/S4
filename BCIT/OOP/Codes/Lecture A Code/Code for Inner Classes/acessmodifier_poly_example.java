class A{
	private void foo(){
		System.out.println("hello");
	}
}
class B extends A{
	public void foo(){
		System.out.println("goodbye");
	}
	public void bar(){}
}
class Test {
	public static void main(String[]args){
		A a = new B();
		a.foo();
		a.bar();//NO
	}
}