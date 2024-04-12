import java.awt.*;
import java.util.*;

public class Plant extends Players{
	public Plant(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = -1; // Herbs n'a pas de tour compté pour jouer
		this.color = Color.GREEN;
	}


	protected boolean stillAlive(){
		return true;
	}
	
	protected boolean couldEat(Players player){
		return false;
	}

	protected int getTypeNextCell(int numFree, int eatable, int sameClass){
		////System.out.println("X: "+X+", Y: "+Y+", numFree: "+numFree+", eatable: "+eatable+", sameClass: "+sameClass);
		if(sameClass>=2 && numFree>=3)
			return 0;
		return -1;
	}
	
	protected void resetMaxLaps(){}
	
}
