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

	public Cell nextCell(ArrayList<Cell>[] result){
		int numEatable = (result[0]).size();
		int numMove = (result[1]).size();
		int numSame = (result[2]).size();
		Random random = new Random();
		if(numSame>=2 && numMove>=3)
			return (result[1]).get(random.nextInt(numMove));
		return null;
	}
	
	public void resetMaxLaps(){}
	
}
