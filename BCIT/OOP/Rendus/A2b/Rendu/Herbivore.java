import java.awt.*;
import java.util.*;

public class Herbivore extends Players{
	public Herbivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.YELLOW;
	}

	public boolean stillAlive(){
		this.maxLaps--;
		return this.maxLaps>=0;
	}
	
	public boolean couldEat(Players player){
		return player instanceof Plant;
	}

	public Cell nextCell(ArrayList<Cell>[] result){
		int numEatable = (result[0]).size();
		int numMove = (result[1]).size();
		int numSame = (result[2]).size();
		Random random = new Random();
		if(numSame>=1 && numMove>=2 && numEatable>=2)
			return (result[0]).get(random.nextInt(numEatable));
		if(numMove>0)
			return (result[1]).get(random.nextInt(numMove));
		return null;
	}
	
	public void resetMaxLaps(){
		this.maxLaps = 5;
	}
}
