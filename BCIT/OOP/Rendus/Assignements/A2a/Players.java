public abstract class Players{
	String[] lifeForms = {"Plant","Herbivors"};
	int X;
	int Y;
	int maxLaps;
	
	public int setX(int x){
		return this.X =x;
	}
	
	public int setY(int y){
		return this.Y = y;
	}
	
	public int getX(){
		return this.X;
	}
	
	public int getY(){
		return this.Y;
	}
	
	public abstract boolean stillAlive();
	public abstract Cell[] hasEnoughNeighbor(Cell[][] board);
}
