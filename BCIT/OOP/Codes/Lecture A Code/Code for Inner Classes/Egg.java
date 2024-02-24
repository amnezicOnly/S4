public class Egg {
	private int x;
	private Yolk yolk = new Yolk();
	class Yolk {
		private int y;
		public void setX(int value){
			x = value;
		}
	}
	public void setY(int value){
		yolk.y = value;
	}
	public static void main(String[] args){
		Egg e = new Egg();
		e.setY(5);
	}
}