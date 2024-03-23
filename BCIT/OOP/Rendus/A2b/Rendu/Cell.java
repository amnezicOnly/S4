public class Cell{
	Players currentPlayer;
	int X;
	int Y;
    	boolean alreadySeen = false;

	public Cell(Players player, int i, int j){
		currentPlayer = player;
		this.X = i;
		this.Y = j;
	}
	
	public int getX(){
		return this.X;
	}
	
	public int getY(){
		return this.Y;
	}

	public void setPlayer(Players player){
		this.currentPlayer = player;
	}

}
