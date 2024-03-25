public class Cell{
	Players currentPlayer;
	int I;
	int J;
    	boolean alreadySeen = false;

	public Cell(Players player, int i, int j){
		currentPlayer = player;
		this.I = i;
		this.J = j;
	}
	
	public int getX(){
		return this.I;
	}
	
	public int getY(){
		return this.J;
	}

	public void setPlayer(Players player, boolean ate){
		this.currentPlayer = null;
		this.currentPlayer = player;
		this.currentPlayer.setX(this.I);
		this.currentPlayer.setY(this.J);
		if(ate)
			this.currentPlayer.resetMaxLaps();
		this.alreadySeen = true;
	}

}
