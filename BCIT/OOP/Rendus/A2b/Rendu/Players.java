import java.awt.*;
import java.util.*;

public abstract class Players{
	protected int X;
	protected int Y;
	protected int maxLaps;
	protected Color color;
	
	protected int setX(int x){
		return this.X =x;
	}
	
	protected int setY(int y){
		return this.Y = y;
	}
	
	protected int getX(){
		return this.X;
	}
	
	protected int getY(){
		return this.Y;
	}
	
	protected abstract boolean stillAlive();
	protected abstract boolean couldEat(Players player);
	protected abstract int getTypeNextCell(int numFree, int eatable, int sameClass);
	protected abstract void resetMaxLaps();
} 
