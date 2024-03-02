public class Herbivore extends Players{
	public Herbivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
	}

	public boolean stillAlive(){
		return this.maxLaps==0;
	}

	public Cell[] hasEnoughNeighbor(Cell[][] board){
		maxLaps--;
		if(maxLaps==0)
			return new Cell[0];
		if(this.X==0 || this.X==board.length-1 || this.Y==0 || this.X==((board[0]).length)-1)
			return new Cell[0];
		int couldEat = 0;
		Cell[] eatable = new Cell[8];
		for(int i=(this.X)-1; i<(this.X)+1; i++){
			for(int j=(this.Y)-1; j<(this.Y)+1; j++){
				if((board[i][j]).currentPlayer instanceof Plant){
					eatable[couldEat] = board[i][j];
					couldEat++;
				}
			}
		}
		if(couldEat!=0)
			return eatable;
		return new Cell[0];
	}
}
