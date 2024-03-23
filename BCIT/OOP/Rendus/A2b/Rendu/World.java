import java.util.*;

public class World{
	int nbCellsX;
	int nbCellsY;
	Cell[][] cells;

	public World(int x, int y){
		this.nbCellsX = x;
		this.nbCellsY = y;
		this.cells = new Cell[x][y];
	}
	
	public void updateCell(Cell[][] cells, int i, int j, Players player){
		if(i<0 || i>=nbCellsX || j<0 || j>=nbCellsY){
			System.out.println("Erreur de i ou j dans la méthode World.updateCell()\n");
		}
		else{
			cells[i][j] = new Cell(player,i,j);
		}
	}

	public void newLap(){
		// for each cell of the board
		for(int j = 0; j<nbCellsY; j++){
			for(int i = 0; i<nbCellsX; i++){
				// If the current cell isn't free and we didn't modify it
				if((cells[i][j]).currentPlayer!=null && (cells[i][j]).alreadySeen==false){
					// Check if the player on the current cell has to be dead
					if((cells[i][j]).currentPlayer.stillAlive()==false){
						(cells[i][j]).currentPlayer = null;
						(cells[i][j]).alreadySeen = true;
					}	

					// If it's still alive
					if((cells[i][j]).alreadySeen==false){
						// We get the list of the cells where the current player could go
						ArrayList<Cell> eatable = (cells[i][j]).currentPlayer.hasEnoughNeighbor(cells);
						int longueur = eatable.size();
						// if the list isn't empty
						if(longueur>0){
							// we took one cell randomly
							Random random = new Random();
							int randomInt = random.nextInt(longueur);
							int tempX = eatable.get(randomInt).getX();
							int tempY = eatable.get(randomInt).getY();
							(cells[i][j]).alreadySeen = true;
							// if the current player is a Plant, we create a new Plant
							if((cells[i][j]).currentPlayer instanceof Plant){
								(cells[tempX][tempY]).currentPlayer = new Plant(tempX,tempY);
							}
							// otherwise, we just move the current player to another available cell
							else{
								// if the current player eat something, we put the lap counter to five
								if((cells[tempX][tempY]).currentPlayer!=null)
									(cells[i][j]).currentPlayer.maxLaps = 5;
								// We move the current player to the new cell and remove him from the old one
								(cells[tempX][tempY]).currentPlayer = (cells[i][j]).currentPlayer;
								(cells[i][j]).currentPlayer = null;		
							}
							// we mark that this cell has already been seen
							(cells[tempX][tempY]).alreadySeen = true;
						}				
					}
				}
			}
		}

		// we change the status of each cell of the board for the next lap
        for(int j=0; j<nbCellsY; j++){
            for(int i=0; i<nbCellsX; i++){
                	(cells[i][j]).alreadySeen = false;
            	}
        }
	}
}
