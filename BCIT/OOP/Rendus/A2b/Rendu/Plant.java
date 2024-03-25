import java.awt.*;
import java.util.*;

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

	public Cell nextCell(Cell[][] board){
		ArrayList<Cell> res = new ArrayList<>();
		int tempPlants = 0;
		int max = board.length;
		/*we create two lists : 
			- one with the list of the cells which currentPlayer couldEat
			- one with the list of the free cells around currentPlayer
		we check for each neighbor cell (North, North-East, East, South-East, South, South-West, West, North-West)
		-->for each case :
		 	- if the cell is free, we add it to the second list
			- if the cell is eatable by the currentPlayer, we add it to the first list
			- if the cell is the same type of the currentPlayer, we increment by one the neighbors value
		if the condition to eat something are okay, we return a random element of the first list
		otherwise, if the currentPlayer can move, we return the second list
		otherwise, we return null
		*/
		// haut
		if((this.Y)+1<max){
			if(couldEat(board[(this.X)][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
			}
			else if(board[(this.X)][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		
		// haut droite
		if((this.X)+1<max && (this.Y)+1<max){
			if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// droite
		if((this.X)+1<max){
			if(couldEat(board[(this.X)+1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)]);
			}
			else if(board[(this.X)+1][(this.Y)].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// bas droite
		if((this.X)+1<max && (this.Y)+1<max){
			if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// bas
		if((this.Y)-1>=0){
			if(couldEat(board[(this.X)][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)-1]);
			}
			else if(board[(this.X)][(this.Y)-1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// bas gauche
		if((this.X)-1>=0 && (this.Y)-1>=0){
			if(couldEat(board[(this.X)-1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)-1]);
			}
			else if(board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// gauche
		if((this.X)-1>=0){
			if(couldEat(board[(this.X)-1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)]);
			}
			else if(board[(this.X)-1][(this.Y)].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		
		// haut gauche
		if((this.X)-1>=0 && (this.Y)+1<max){
			if(couldEat(board[(this.X)-1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)+1]);
			}
			else if(board[(this.X)-1][(this.Y)+1].currentPlayer instanceof Plant){
				tempPlants++;
			}
		}
		Random random = new Random();
		if(tempPlants>=2 && res.size()>=3)
			return res.get(random.nextInt(res.size()));;
		return null;
	}
	
}
