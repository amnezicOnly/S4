public class Ex{
	public void bar() throws Exception { throw new Exception();}
	public void foo() throws Exception{
		try{
			System.out.println("foo");
			bar();
		}
			
			finally{
				System.out.println("finally");
		}
			System.out.println("done foo");
	}
	public static void main(String[] args) throws Exception{
		Ex ee = new Ex();
		ee.foo();
	}
}