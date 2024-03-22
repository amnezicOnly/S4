import java.awt.*;

public class Herbivore extends Players{
	public Herbivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.YELLOW;
	}

	public boolean stillAlive(){
		maxLaps--;
		return this.maxLaps==-1;
	}
	
	public boolean couldEat(Players player){
		return player instanceof Plant;
	}

	public ArrayList<Cell> hasEnoughNeighbor(Cell[][] board){
		ArrayList<Cell> res = new ArrayList<>();
		int couldEat = 0;
		int voidCells = 0;
		int neighbors = 0;
		int max = board.length;
		// haut
		if((this.Y)+1<max){
			if(board[(this.X)][(this.Y)+1].currentPlayer==null){
				res.add(board[(this.X)][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)][(this.Y)+1].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// haut droite
		if((this.Y)+1<max && (this.X)+1<max){
			if(board[(this.X)+1][(this.Y)+1].currentPlayer==null){
				res.add(board[(this.X)+1][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// droite
		if((this.X)+1<max){
			if(board[(this.X)+1][(this.Y)].currentPlayer==null){
				res.add(board[(this.X)][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)+1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// bas droite
		if((this.X)+1<max && (this.Y)-1>0){
			if(board[(this.X)+1][(this.Y)-1].currentPlayer==null){
				res.add(board[(this.X)+1][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)+1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)-1].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// bas
		if((this.Y)-1>0){
			if(board[(this.X)][(this.Y)-1].currentPlayer==null){
				res.add(board[(this.X)][(this.Y)-1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)][(this.Y)-1].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// bas gauche
		if((this.Y)-1>0 && (this.X)-1>0){
			if(board[(this.X)-1][(this.Y)-1].currentPlayer==null){
				res.add(board[(this.X)-1][(this.Y)-1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)-1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// gauche
		if((this.X)-1>0){
			if(board[(this.X)-1][(this.Y)].currentPlayer==null){
				res.add(board[(this.X)-1][(this.Y)]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)-1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		// haut gauche
		if((this.X)-1>0 && (this.Y)+1<max){
			if(board[(this.X)-1][(this.Y)+1].currentPlayer==null){
				res.add(board[(this.X)-1][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)-1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)+1].currentPlayer instanceof Herbivore){
				neighbors++;
			}
		}
		if(neighbors>=1 && voidCells>=2 && couldEat>=2)
			return res;
		ArrayList<Cell> res2 = new ArrayList<>();
		return res2;
	}
}
