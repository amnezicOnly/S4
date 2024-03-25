import java.awt.*;
import java.util.*;

public class Omnivore extends Players{
	public Omnivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.BLUE;
	}

	public boolean stillAlive(){
		this.maxLaps--;
		return this.maxLaps>=0;
	}
	
	public boolean couldEat(Players player){
		return (player instanceof Herbivore || player instanceof Omnivore || player instanceof Plant);
	}

	public Cell nextCell(Cell[][] board){
		ArrayList<Cell> res = new ArrayList<>();
		ArrayList<Cell> res2 = new ArrayList<>();	
		int neighbors = 0;
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
			if(board[(this.X)][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)][(this.Y)+1]);
			}
			else if(couldEat(board[(this.X)][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
			}
			else if(board[(this.X)][(this.Y)+1].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// haut droite
		if((this.Y)+1<max && (this.X)+1<max){
			if(board[(this.X)+1][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)+1]);
			}
			else if(couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// droite
		if((this.X)+1<max){
			if(board[(this.X)+1][(this.Y)].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)]);
			}
			else if(couldEat(board[(this.X)+1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)]);
			}
			else if(board[(this.X)+1][(this.Y)].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// bas droite
		if((this.X)+1<max && (this.Y)-1>=0){
			if(board[(this.X)+1][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)-1]);
			}
			else if(couldEat(board[(this.X)+1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)-1]);
			}
			else if(board[(this.X)+1][(this.Y)-1].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// bas
		if((this.Y)-1>=0){
			if(board[(this.X)][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)][(this.Y)-1]);
			}
			else if(couldEat(board[(this.X)][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)-1]);
			}
			else if(board[(this.X)][(this.Y)-1].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// bas gauche
		if((this.Y)-1>=0 && (this.X)-1>=0){
			if(board[(this.X)-1][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)-1]);
			}
			else if(couldEat(board[(this.X)-1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)-1]);
			}
			else if(board[(this.X)-1][(this.Y)-1].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// gauche
		if((this.X)-1>=0){
			if(board[(this.X)-1][(this.Y)].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)]);
			}
			else if(couldEat(board[(this.X)-1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)]);
			}
			else if(board[(this.X)-1][(this.Y)].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		// haut gauche
		if((this.X)-1>=0 && (this.Y)+1<max){
			if(board[(this.X)-1][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)+1]);
			}
			else if(couldEat(board[(this.X)-1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)+1]);
			}
			else if(board[(this.X)-1][(this.Y)+1].currentPlayer instanceof Omnivore){
				neighbors++;
			}
		}
		Random random = new Random();
		if(neighbors>=1 && res.size()>=3 && res.size()==1)
			return res.get(res.size());
		if(res2.size()>0)
			return res2.get(random.nextInt(res2.size()));
		return null;
	}
}
