import java.awt.*;
import java.util.*;

public class Carnivore extends Players{
	public Carnivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.RED;
	}

	protected boolean stillAlive(){
		this.maxLaps--;
		return this.maxLaps>=0;
	}
	
	protected boolean couldEat(Players player){
		return (player instanceof Herbivore || player instanceof Omnivore);
	}

	protected int getTypeNextCell(int numFree, int eatable, int sameClass){
		if(sameClass>=1 && numFree>=3 && eatable>=2)
			return 1;
		if(numFree>0)
			return 0;
		return -1;
	}
	
	protected void resetMaxLaps(){
		this.maxLaps = 5;
	}
}
