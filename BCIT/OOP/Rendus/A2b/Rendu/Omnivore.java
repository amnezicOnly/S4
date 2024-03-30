import java.awt.*;
import java.util.*;

public class Omnivore extends Players{
	public Omnivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.BLUE;
	}

	protected boolean stillAlive(){
		this.maxLaps--;
		return this.maxLaps>=0;
	}
	
	protected boolean couldEat(Players player){
		return (player instanceof Plant || player instanceof Herbivore || player instanceof Carnivore);
	}

	protected int getTypeNextCell(int numFree, int eatable, int sameClass){
		//System.out.println("X: "+this.X+", Y: "+this.Y+", numFree: "+numFree+", eatable: "+eatable+", sameClass: "+sameClass);
		if(sameClass>=1 && numFree>=3 && eatable>=1){
			//System.out.println("A mangé");
			return 1;
		}
		if(numFree>0)
			return 0;
		return -1;
	}
	
	protected void resetMaxLaps(){
		this.maxLaps = 5;
	}
}
