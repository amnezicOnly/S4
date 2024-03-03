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
		
		int couldEat = 0;
		Cell[] eatable = new Cell[8];
		int max = board.length;
		// haut
		if((this.Y)+1<max && (board[(this.X)][(this.Y)+1].currentPlayer==null || board[(this.X)][(this.Y)+1].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)][(this.Y)+1];
			couldEat++;
		}
		// haut droite
		if((this.X)+1<max && (this.Y)+1<max && (board[(this.X)+1][(this.Y)+1].currentPlayer==null || board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)+1][(this.Y)+1];
			couldEat++;
		}
		// droite
		if((this.X)+1<max && (board[(this.X)+1][(this.Y)].currentPlayer==null || board[(this.X)+1][(this.Y)].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)+1][this.Y];
			couldEat++;
		}
		// bas droite
		if((this.X)+1<max && (this.Y)-1>=0 && (board[(this.X)+1][(this.Y)-1].currentPlayer==null || board[(this.X)+1][(this.Y)-1].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)+1][(this.Y)-1];
			couldEat++;
		}
		// bas
		if((this.Y)-1>=0 && (board[(this.X)][(this.Y)-1].currentPlayer==null || board[(this.X)][(this.Y)-1].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)][(this.Y)-1];
			couldEat++;
		}
		// bas gauche
		if((this.X)-1>=0 && (this.Y)-1>=0 && (board[(this.X)-1][(this.Y)-1].currentPlayer==null || board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)-1][(this.Y)-1];
			couldEat++;
		}
		// gauche
		if((this.X)-1>=0 && (board[(this.X)-1][(this.Y)].currentPlayer==null || board[(this.X)-1][(this.Y)].currentPlayer instanceof Plant)){
			eatable[couldEat] = board[(this.X)-1][(this.Y)];
			couldEat++;
		}
		if(couldEat!=0)
			return eatable;
		return new Cell[0];
	}
}
