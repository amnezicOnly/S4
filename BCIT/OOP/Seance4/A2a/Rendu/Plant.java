public class Plant extends Players{
	public Plant(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = -1; // Herbs n'a pas de tour compté pour jouer
	}


	public boolean couldEat(Cell cell){	// herbs can't eat anything
		return false;
	}

	public boolean stillAlive(){
		return true;
	}

	public void newLap(){

	}
}
