public class Herbivore extends Players{
	public Herbivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
	}

	public boolean couldEat(Cell cell){
		return ((cell.currentPlayer) instanceof Plant);
	}

	public boolean stillAlive(){
		return this.maxLaps==0;
	}

	public void newLap(){
		this.maxLaps--;
	}
}
