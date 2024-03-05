// import de la classe random
import java.util.Random;



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
					// On récupère la liste des cellules voisines qui peuvent être mangées
					Cell[] eatable = (cells[i][j]).currentPlayer.hasEnoughNeighbor(cells);
					int longueur = eatable.length;
					boolean state = false;
					// si c'est un herbivore et que sa liste est vide et que son maxLaps<0, on le détruit
					if((cells[i][j]).currentPlayer instanceof Herbivore){
						if((cells[i][j]).currentPlayer.maxLaps<0){
							(cells[i][j]).currentPlayer = null;
							state = true;
						}
					}
					// sinon, si eatable n'est pas vide
					if(longueur!=0 && state == false){
						// on calcule la vraie taille de la liste
						int realLength = 0;
						while(eatable[realLength]!=null)
							realLength++;
						// on prend un nombre random compris entre 0 et realLength inclus
						Random random = new Random();
						int randomInt = random.nextInt(realLength);
						int tempX = eatable[randomInt].getX();
						int tempY = eatable[randomInt].getY();
						// en fonction du type de joueur sur la case, on remplace une case par un Plant ou un Herbivore
						if((cells[i][j]).currentPlayer instanceof Plant){
							(cells[tempX][tempY]).currentPlayer = new Plant(tempX,tempY);
							(cells[tempX][tempY]).alreadySeen = true;
							(cells[i][j]).alreadySeen = true;
						}
						if((cells[i][j]).currentPlayer instanceof Herbivore){
							if((cells[tempX][tempY]).currentPlayer!=null && (cells[tempX][tempY]).currentPlayer instanceof Plant)
								(cells[i][j]).currentPlayer.maxLaps = 5;
							(cells[tempX][tempY]).currentPlayer = (cells[i][j]).currentPlayer;
							(cells[tempX][tempY]).currentPlayer.setX(tempX);
							(cells[tempX][tempY]).currentPlayer.setY(tempY);
							(cells[tempX][tempY]).alreadySeen = true;
							(cells[i][j]).alreadySeen = true;
							(cells[i][j]).currentPlayer = null;
							
						}
					}				
				}
			}
		}

        for(int i=0; i<nbCellsX; i++){
            for(int j=0; j<nbCellsY; j++){
                (cells[i][j]).alreadySeen = false;
            }
        }

	}
}
