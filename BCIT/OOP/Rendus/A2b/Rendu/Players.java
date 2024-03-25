import java.awt.*;
import java.util.*;

public abstract class Players{
	int X;
	int Y;
	int maxLaps;
	Color color;
	
	public int setX(int x){
		return this.X =x;
	}
	
	public int setY(int y){
		return this.Y = y;
	}
	
	public int getX(){
		return this.X;
	}
	
	public int getY(){
		return this.Y;
	}
	
	public abstract boolean couldEat(Players player);
	public abstract boolean stillAlive();
	public abstract Cell nextCell(ArrayList<Cell>[] result);
	public abstract void resetMaxLaps();
	
	public Cell nextCells(Cell[][] board){
		//System.out.println("X: "+this.X+", Y: "+this.Y);
		ArrayList<Cell> res = new ArrayList<>();
		ArrayList<Cell> res2 = new ArrayList<>();
		ArrayList<Cell> res3 = new ArrayList<>();
		int max = board.length;
		/*we create 3 lists : 
			- one with the list of the cells which currentPlayer this.couldEat
			- one with the list of the free cells around currentPlayer
			- one with the list of the cells of the same class as currentPlayer
		we check for each neighbor cell (North, North-East, East, South-East, South, South-West, West, North-West)
		-->for each case :
		 	- if the cell is free, we add it to the second list
			- if the cell is eatable by the currentPlayer, we add it to the first list
			- if the cell is the same type of the currentPlayer, we add it to the third list
		we return the cell where currentPlayer will go on
		*/
		// haut
		if((this.Y)+1<max){
			if(board[(this.X)][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)][(this.Y)+1]);
			}
			else if(this.couldEat(board[(this.X)][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)+1]);
			}
			else if(board[(this.X)][(this.Y)+1].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)][(this.Y)+1]);
			}
		}
		// haut droite
		if((this.Y)+1<max && (this.X)+1<max){
			if(board[(this.X)+1][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)+1]);
			}
			else if(this.couldEat(board[(this.X)+1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)+1]);
			}
			else if(board[(this.X)+1][(this.Y)+1].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)+1][(this.Y)+1]);
			}
		}
		// droite
		if((this.X)+1<max){
			if(board[(this.X)+1][(this.Y)].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)]);
			}
			else if(this.couldEat(board[(this.X)+1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)]);
			}
			else if(board[(this.X)+1][(this.Y)].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)+1][(this.Y)]);
			}
		}
		// bas droite
		if((this.X)+1<max && (this.Y)-1>=0){
			if(board[(this.X)+1][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)+1][(this.Y)-1]);
			}
			else if(this.couldEat(board[(this.X)+1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)+1][(this.Y)-1]);
			}
			else if(board[(this.X)+1][(this.Y)-1].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)+1][(this.Y)-1]);
			}
		}
		// bas
		if((this.Y)-1>=0){
			if(board[(this.X)][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)][(this.Y)-1]);
			}
			else if(this.couldEat(board[(this.X)][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)][(this.Y)-1]);
			}
			else if(board[(this.X)][(this.Y)-1].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)][(this.Y)-1]);
			}
		}
		// bas gauche
		if((this.Y)-1>=0 && (this.X)-1>=0){
			if(board[(this.X)-1][(this.Y)-1].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)-1]);
			}
			else if(this.couldEat(board[(this.X)-1][(this.Y)-1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)-1]);
			}
			else if(board[(this.X)-1][(this.Y)-1].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)-1][(this.Y)-1]);
			}
		}
		// gauche
		if((this.X)-1>=0){
			if(board[(this.X)-1][(this.Y)].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)]);
			}
			else if(this.couldEat(board[(this.X)-1][(this.Y)].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)]);
			}
			else if(board[(this.X)-1][(this.Y)].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)-1][(this.Y)]);
			}
		}
		// haut gauche
		if((this.X)-1>=0 && (this.Y)+1<max){
			if(board[(this.X)-1][(this.Y)+1].currentPlayer==null){
				res2.add(board[(this.X)-1][(this.Y)+1]);
			}
			else if(this.couldEat(board[(this.X)-1][(this.Y)+1].currentPlayer)){
				res.add(board[(this.X)-1][(this.Y)+1]);
			}
			else if(board[(this.X)-1][(this.Y)+1].currentPlayer.getClass()==this.getClass()){
				res3.add(board[(this.X)-1][(this.Y)+1]);
			}
		}
		ArrayList<Cell>[] result = (ArrayList<Cell>[]) new ArrayList[3];
		result[0] = res;
		result[1] = res2;
		result[2] = res3;
		return this.nextCell(result);
	}
}
