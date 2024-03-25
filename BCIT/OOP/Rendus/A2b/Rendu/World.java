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
						// we mark that we deal with it
						 (cells[i][j]).alreadySeen = true;
						// we catch a cell where the currentPlayer could go	
						Cell newCell = (cells[i][j]).currentPlayer.nextCell(cells);
						// if it could go somewhere
						if(newCell!=null){
							// we catch the coordinates
							int tempX = newCell.getX();
							int tempY = newCell.getY();
							// if the currentPlayer finally eat something, we reset the maxLaps counter to 5
							if(cells[tempX][tempY].currentPlayer!=null)
								// the next line is the only way to make the Omnivore objects follow the maxLaps rule, but I don't actually know why yet
								if(cells[i][j].currentPlayer instanceof Omnivore){}
								cells[i][j].currentPlayer.maxLaps = 5;
							// we delete the old currentPlayer on the new cell
							cells[tempX][tempY].currentPlayer = null;
							// we put the currentPlayer on the new cell
							cells[tempX][tempY].currentPlayer = cells[i][j].currentPlayer;
							// if currentPlayer ins't a Plant, we completely move the currentPlayer
							if(!(cells[i][j].currentPlayer instanceof Plant))
								cells[i][j].currentPlayer = null;
							// we mark that we deal with the new cell
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
