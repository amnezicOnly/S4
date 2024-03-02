public class Plant extends Players{
	public Plant(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = -1; // Herbs n'a pas de tour compté pour jouer
	}


	public boolean stillAlive(){
		return true;
	}

	public Cell[] hasEnoughNeighbor(Cell[][] board){
		if(this.X==0 || this.X==board.length-1 || this.Y==0 || this.X==((board[0]).length)-1)
			return new Cell[0];
		int tempPlants = -1;
		int couldEat = 0;
		Cell[] eatable = new Cell[8];
		for(int i=(this.X)-1; i<(this.X)+1; i++){
			for(int j=(this.Y)-1; j<(this.Y)+1; j++){
				if(board[i][j].currentPlayer==null){
					eatable[couldEat] = board[i][j];
					couldEat++;
				}
				if((board[i][j]).currentPlayer instanceof Plant){
					tempPlants++;
				}
			}
		}
		if(tempPlants>=4 && couldEat>=3)
			return eatable;
		return new Cell[0];
	}
	
}
