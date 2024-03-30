import java.util.*;

public class World{
	int nbcellsX;
	int nbcellsY;
	int lap = 0;
	Cell[][] cells;

	public World(int x, int y){
		this.nbcellsX = x;
		this.nbcellsY = y;
		this.cells = new Cell[x][y];
	}
	
	public void updateCell(int i, int j, Players player){
		if(i<0 || i>=nbcellsX || j<0 || j>=nbcellsY){
			System.out.println("Erreur de i ou j dans la méthode World.updateCell()\n");
		}
		else{
			this.cells[i][j] = new Cell(player,i,j);
		}
	}

	public void newLap(){
		// for each cell of the board
		//System.out.println("lap "+ lap++);
		for(int j = 0; j<nbcellsY; j++){
			for(int i = 0; i<nbcellsX; i++){
				// If the current cell isn't free and we didn't modify it
				if((this.cells[i][j]).currentPlayer!=null && (this.cells[i][j]).alreadySeen==false){
					/*if((this.cells[i][j]).currentPlayer instanceof Omnivore)
						System.out.println("Traite X: "+i+", Y: "+j);*/
					// Check if the player on the current cell has to be dead
					if((this.cells[i][j]).currentPlayer.stillAlive()==false){
						(this.cells[i][j]).currentPlayer = null;
						(this.cells[i][j]).alreadySeen = true;
					}	

					// If it's still alive
					if((this.cells[i][j]).alreadySeen==false){
						//System.out.println("Rentre bien là dedans");
						// we mark that we deal with it
						(this.cells[i][j]).alreadySeen = true;
						// we catch a cell where the currentPlayer could go
						// the second parameter represent the number of cell distance we have to care about
						Cell newCell = (this.cells[i][j]).nextCell(this.cells,1);
						// if it could go somewhere
						if(newCell!=null){
							////System.out.println("Nouvelle case");
							int tempX = newCell.getX();
							int tempY = newCell.getY();
							boolean food = (this.cells[i][j]).currentPlayer.couldEat((this.cells[tempX][tempY]).currentPlayer);
							// we move the currentPlayer to the new position
							(this.cells[tempX][tempY]).currentPlayer = (this.cells[i][j]).currentPlayer;
							(this.cells[tempX][tempY]).currentPlayer.setX(tempX);
							(this.cells[tempX][tempY]).currentPlayer.setX(tempY);
							if(food){
								(this.cells[tempX][tempY]).currentPlayer.resetMaxLaps();
							}
							if(!((this.cells[i][j]).currentPlayer instanceof Plant)){
								(this.cells[i][j]).currentPlayer = null;
							}
							if((this.cells[i][j]).currentPlayer instanceof Omnivore){
								
							}
							(this.cells[tempX][tempY]).alreadySeen = true;					
						}
					}
				}
			}
		}

		// we change the status of each cell of the board for the next lap
        	for(int j=0; j<nbcellsY; j++){
            		for(int i=0; i<nbcellsX; i++){
                		(this.cells[i][j]).alreadySeen = false;
            		}
        	}
	}
}
