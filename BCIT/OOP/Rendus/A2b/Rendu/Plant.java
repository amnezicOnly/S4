import java.awt.*;
import java.util.ArrayList;

public class Plant extends Players{
	public Plant(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = -1; // Herbs n'a pas de tour compté pour jouer
		this.color = Color.GREEN;
	}


	public boolean stillAlive(){
		return true;
	}
	
	public boolean couldEat(Players player){
		return player==null;
	}

	public ArrayList<Cell> hasEnoughNeighbor(Cell[][] board){
		ArrayList<Cell> res = new ArrayList<>();
		int tempPlants = 0;
		int couldEat = 0;
		int max = board.length;
		// haut
		if((this.Y)+1<max){
			if(couldEat(board[(this.X)][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		
		// haut droite
		if((this.X)+1<max && (this.Y)+1<max){
			if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// droite
		if((this.X)+1<max){
			if(couldEat(board[(this.X)+1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// bas droite
		if((this.X)+1<max && (this.Y)+1<max){
			if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// bas
		if((this.Y)-1>0){
			if(couldEat(board[(this.X)][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)][(this.Y)-1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// bas gauche
		if((this.X)-1>0 && (this.Y)-1>0){
			if(couldEat(board[(this.X)-1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)-1]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// gauche
		if((this.X)-1>0){
			if(couldEat(board[(this.X)-1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// haut gauche
		if((this.X)-1>0 && (this.Y)+1<max){
			if(couldEat(board[(this.X)-1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)+1]);
				couldEat++;
			}
			else if(board[(this.X)-1][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		if(tempPlants>=2 && couldEat>=3)
			return res;
		ArrayList<Cell> res2 = new ArrayList<>();
		return res2;
	}
	
}
