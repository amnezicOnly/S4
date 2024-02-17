public class Cell{
	Players currentPlayer;

	public Cell(Players player){
		currentPlayer = player;
	}

	public void setPlayer(Players player){
		this.currentPlayer = player;
	}

	public int getLifeFormNumber(){
		return currentPlayer.getLifeFormNumber(currentPlayer);
    	}	
}
