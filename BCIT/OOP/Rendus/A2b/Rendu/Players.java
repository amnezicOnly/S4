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
	public abstract Cell nextCell(Cell[][] board);
}
