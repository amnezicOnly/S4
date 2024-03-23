import java.util.*;

public class World{
	int nbCellsX;
	int nbCellsY;
	static Cell[][] cells;

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
		for(int j = 0; j<nbCellsY; j++){
			for(int i = 0; i<nbCellsX; i++){	// pour chaque cellule du plateau
				if((cells[i][j]).currentPlayer!=null && (cells[i][j]).alreadySeen==false){	// si la case n'est pas vide
					// On vérifie qu'elle est toujours vivante
					if((cells[i][j]).currentPlayer.stillAlive()==false){
						(cells[i][j]).currentPlayer = null;
						(cells[i][j]).alreadySeen = true;
					}	

					// Si toujours vivante
					if((cells[i][j]).alreadySeen==false){
						// On regarde là où le joueur peut aller
						ArrayList<Cell> eatable = (cells[i][j]).currentPlayer.hasEnoughNeighbor(cells);
						int longueur = eatable.size();
						// S'il peut aller quelque part
						if(longueur>0){
							// On prend une cell random dans sa liste de choix possibles
							Random random = new Random();
							int randomInt = random.nextInt(longueur);
							int tempX = eatable.get(randomInt).getX();
							int tempY = eatable.get(randomInt).getY();
							(cells[i][j]).alreadySeen = true;
							// Si c'est une Plant, on crée un nouveau joueur
							if((cells[i][j]).currentPlayer instanceof Plant){
								(cells[tempX][tempY]).currentPlayer = new Plant(tempX,tempY);
							}
							else{	// Sinon c'est qu'il doit juste se déplacer
								(cells[i][j]).currentPlayer.maxLaps--;
								// Si le joueur mange quelquechose
								if((cells[tempX][tempY]).currentPlayer!=null)
									(cells[i][j]).currentPlayer.maxLaps = 5;
								// On place le joueur sur la nouvelle case et on l'efface de l'ancienne
								(cells[tempX][tempY]).currentPlayer = (cells[i][j]).currentPlayer;
								(cells[i][j]).currentPlayer = null;		
							}
							// la nouvelle case est déjà vue
							(cells[tempX][tempY]).alreadySeen = true;
						}				
					}
				}
			}
		}

        	for(int j=0; j<nbCellsY; j++){
            		for(int i=0; i<nbCellsX; i++){
                		(cells[i][j]).alreadySeen = false;
            		}
        	}
	}
}
