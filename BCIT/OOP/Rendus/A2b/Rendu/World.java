import java.util.*;

public class World{
	int nbCellsX;
	int nbCellsY;
	int lap = 0;
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
					//System.out.println("i: "+i+", j: "+j);
					// Check if the player on the current cell has to be dead
					if((cells[i][j]).currentPlayer.stillAlive()==false){
						(cells[i][j]).currentPlayer = null;
						(cells[i][j]).alreadySeen = true;
					}	

					// If it's still alive
					if((cells[i][j]).alreadySeen==false){
						//System.out.println("Rentre bien là dedans");
						// we mark that we deal with it
						(cells[i][j]).alreadySeen = true;
						// we catch a cell where the currentPlayer could go	
						Cell newCell = (cells[i][j]).currentPlayer.nextCells(cells);
						// if it could go somewhere
						if(newCell!=null){
							// we move the currentPlayer to the new position
							newCell.setPlayer((cells[i][j]).currentPlayer,newCell.currentPlayer!=null);
							// if currentPlayer isn't a Plant, we completely move the currentPlayer
							if(!(cells[i][j].currentPlayer instanceof Plant))
								cells[i][j].currentPlayer = null;
							// we mark that we deal with the new cell
							//System.out.println(" mange tempX= "+newCell.getX()+", tempY= "+newCell.getY());			
						}
					}
				}
			}
		}
		System.out.println("lap "+ lap++);

		// we change the status of each cell of the board for the next lap
        	for(int j=0; j<nbCellsY; j++){
            		for(int i=0; i<nbCellsX; i++){
                		(cells[i][j]).alreadySeen = false;
            		}
        	}
	}
}
