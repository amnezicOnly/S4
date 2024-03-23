import java.awt.*;
import java.util.ArrayList;

public class Carnivore extends Players{
	public Carnivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.RED;
	}

	public boolean stillAlive(){
		this.maxLaps--;
		return this.maxLaps>=0;
	}
	
	public boolean couldEat(Players player){
		return (player instanceof Herbivore || player instanceof Omnivore);
	}

	public ArrayList<Cell> hasEnoughNeighbor(Cell[][] board){
		ArrayList<Cell> res = new ArrayList<>();
		ArrayList<Cell> res2 = new ArrayList<>();	
		int couldEat = 0;
		int voidCells = 0;
		int neighbors = 0;
		int max = board.length;
		// haut
		if((this.Y)+1<max){
			if(board[(this.X)][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)][(this.Y)+1].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// haut droite
		if((this.Y)+1<max && (this.X)+1<max){
			if(board[(this.X)+1][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// droite
		if((this.X)+1<max){
			if(board[(this.X)+1][(this.Y)].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)+1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// bas droite
		if((this.X)+1<max && (this.Y)-1>0){
			if(board[(this.X)+1][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)-1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)+1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)-1].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// bas
		if((this.Y)-1>0){
			if(board[(this.X)][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)][(this.Y)-1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)][(this.Y)-1].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// bas gauche
		if((this.Y)-1>0 && (this.X)-1>0){
			if(board[(this.X)-1][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)-1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)-1][(this.Y)-1].currentPlayer)){
				res2.add(board[(this.X)-1][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// gauche
		if((this.X)-1>0){
			if(board[(this.X)-1][(this.Y)].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)-1][(this.Y)].currentPlayer)){
				res2.add(board[(this.X)-1][(this.Y)]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		// haut gauche
		if((this.X)-1>0 && (this.Y)+1<max){
			if(board[(this.X)-1][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)+1]);
				voidCells++;
			}
			else if(couldEat(board[(this.X)-1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)+1].currentPlayer instanceof Carnivore){
				neighbors++;
			}
		}
		if(neighbors>=1 && voidCells>=3 && couldEat==2)
			return res;
		return res2;
	}
}
