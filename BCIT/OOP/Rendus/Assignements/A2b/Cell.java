import java.util.*;

public class Cell{
	public Players currentPlayer;
	private int I;
	private int J;
    	public boolean alreadySeen = false;
	public static int number = 0;

	public Cell(Players player, int i, int j){
		currentPlayer = player;
		this.I = i;
		this.J = j;
	}
	
	public void setX(int x){
		this.I = x;
	}
	
	public void setY(int y){
		this.J = y;
	}
	
	public int getX(){
		return this.I;
	}
	
	public int getY(){
		return this.J;
	}
	
	protected Cell nextCell(Cell[][] board, int bound){
		//System.out.println(this.getClass());
		//System.out.println("X: "+this.I+", Y: "+this.J);
		
		/*we create 3 lists : 
			- one with the list of the free cells around currentPlayer
			- one with the list of the cells which currentPlayer this.couldEat
			- one with the list of the cells of the same class as currentPlayer
		we check for each neighbor cell (North, North-East, East, South-East, South, South-West, West, North-West)
		-->for each case :
		 	- if the cell is free, we add it to the first list
			- if the cell is eatable by the currentPlayer, we add it to the second list
			- if the cell is the same type of the currentPlayer, we add it to the third list
		we return the cell where currentPlayer will go on
		*/
		ArrayList<Cell> freeCells = new ArrayList<>();		// neighbors free cells
		int numFree = 0;					// we store the size of the list
		ArrayList<Cell> eatableCells = new ArrayList<>();	// neighbors eatable cells
		int numEatable = 0;					// we store the size of the list
		ArrayList<Cell> sameClassCells = new ArrayList<>();	// neighbors same class cells
		int numSameClassCells = 0;				// we store the size of the list
		
		//System.out.println("Number: "+number++);
		int max = board.length;
		for(int j = -bound; j<=bound; j++){
			if(((this.J)+j)>=0 && ((this.J)+j)<max){
				for(int i = -bound; i<=bound; i++){
					if((this.I)+i>=0 && (this.I)+i<max){
						if(!(i==0 && j==0)){
							//System.out.println("i: "+i+", j: "+j);
							//System.out.println("Rentre dans la boucle");
							if(board[(this.I)+i][(this.J)+j].currentPlayer==null){
								freeCells.add(board[(this.I)+i][(this.J)+j]);
								numFree++;
							}
							else if(this.currentPlayer.couldEat(board[(this.I)+i][(this.J)+j].currentPlayer)){
								eatableCells.add(board[(this.I)+i][(this.J)+j]);
								numEatable++;
							}
							else if(board[(this.I)+i][(this.J)+j].currentPlayer.getClass()==this.currentPlayer.getClass()){
								sameClassCells.add(board[(this.I)+i][(this.J)+j]);
								numSameClassCells++;
							}
						}
						
					}
				}
			}
		}
		
		Random random = new Random();
		// get the type of the cell that will be performed
		// type == 0 : currentPlayer will move to another cell
		// type == 1 : currentPlayer will develop to another cell
		int type = this.currentPlayer.getTypeNextCell(numFree,numEatable,numSameClassCells);
		
		
		// return the cell depending on type
		////System.out.println("Type: "+type);
		if(type==0){
			return freeCells.get(random.nextInt(numFree));
		}
		else if(type==1){
			/*if(this.currentPlayer instanceof Carnivore)
				System.out.println("("+this.I+","+this.J+") a mangé");*/
			return eatableCells.get(random.nextInt(numEatable));
		}
		else
			return null;
	}
}
