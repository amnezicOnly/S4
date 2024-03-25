import java.awt.*;
import java.util.*;

public class Carnivore extends Players{
	public Carnivore(int x, int y){
		this.X = x;
		this.Y = y;
		this.maxLaps = 5;
		this.color = Color.RED;
	}

	public boolean stillAlive(){
		this.maxLaps--;
		return this.maxLaps>=0;
	}
	
	public boolean couldEat(Players player){
		return (player instanceof Herbivore || player instanceof Omnivore);
	}

	public Cell nextCell(ArrayList<Cell>[] result){
		int numEatable = (result[0]).size();
		int numMove = (result[1]).size();
		int numSame = (result[2]).size();
		Random random = new Random();
		if(numSame>=1 && numMove>=3 && numEatable>=2)
			return (result[0]).get(random.nextInt(numEatable));
		if(numMove>0)
			return (result[1]).get(random.nextInt(numMove));
		return null;
	}
	
	public void resetMaxLaps(){
		this.maxLaps = 5;
	}
}
