public abstract class Players{
	String[] lifeForms = {"Plant","Herbivors"};
	int X;
	int Y;
	int maxLaps;
	
	
	public abstract boolean stillAlive();
	public abstract Cell[] hasEnoughNeighbor(Cell[][] board);
}
