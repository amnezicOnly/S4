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
		int tempPlants = 0;
		int couldEat = 0;
		int max = board.length;
		Cell[] eatable = new Cell[8];
		// haut
		if((this.Y)+1<max && board[(this.X)][(this.Y)+1].currentPlayer==null){
			eatable[couldEat] = board[(this.X)][(this.Y)+1];
			couldEat++;
		}
		if((this.Y)+1<max && board[(this.X)][(this.Y)+1].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// haut droite
		if((this.X)+1<max && (this.Y)+1<max && board[(this.X)+1][(this.Y)+1].currentPlayer==null){
			eatable[couldEat] = board[(this.X)+1][(this.Y)+1];
			couldEat++;
		}
		if((this.X)+1<max && (this.Y)+1<max && board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// droite
		if((this.X)+1<max && board[(this.X)+1][(this.Y)].currentPlayer==null){
			eatable[couldEat] = board[(this.X)+1][(this.Y)];
			couldEat++;
		}
		if((this.X)+1<max && board[(this.X)+1][(this.Y)].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// bas droite
		if((this.X)+1<max && (this.Y)-1>=0 && board[(this.X)+1][(this.Y)-1].currentPlayer==null){
			eatable[couldEat] = board[(this.X)+1][(this.Y)-1];
			couldEat++;
		}
		if((this.X)+1<max && (this.Y)-1>=0 && board[(this.X)+1][(this.Y)-1].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// bas
		if((this.Y)-1>=0 && board[(this.X)][(this.Y)-1].currentPlayer==null){
			eatable[couldEat] = board[(this.X)][(this.Y)-1];
			couldEat++;
		}
		if((this.Y)-1>=0 && board[(this.X)][(this.Y)-1].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// bas gauche
		if((this.X)-1>=0 && (this.Y)-1>=0 && board[(this.X)-1][(this.Y)-1].currentPlayer==null){
			eatable[couldEat] = board[(this.X)-1][(this.Y)-1];
			couldEat++;
		}
		if((this.X)-1>=0 && (this.Y)-1>=0 && board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// gauche
		if((this.X)-1>=0 && board[(this.X)-1][(this.Y)].currentPlayer==null){
			eatable[couldEat] = board[(this.X)-1][(this.Y)];
			couldEat++;
		}
		if((this.X)-1>=0 && board[(this.X)-1][(this.Y)].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		// haut gauche
		if((this.X)-1>=0 && (this.Y)+1<max && board[(this.X)-1][(this.Y)+1].currentPlayer==null){
			eatable[couldEat] = board[(this.X)-1][(this.Y)+1];
			couldEat++;
		}
		if((this.X)-1>=0 && (this.Y)+1<max && board[(this.X)-1][(this.Y)+1].currentPlayer instanceof Plant){
			tempPlants++;
		}
		
		if(tempPlants==4 && couldEat>=3)
			return eatable;
		return new Cell[0];
	}
	
}
