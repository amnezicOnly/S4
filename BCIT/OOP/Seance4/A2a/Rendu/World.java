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
		System.out.println("Rentre bien dans la fonction World.newLap()");
		for(int i = 0; i<nbCellsX; i++){
			for(int j = 0; j<nbCellsY; j++){	// pour chaque cellule du plateau
				if((cells[i][j]).currentPlayer!=null){	// si la case n'est pas vide
					// On récupère la liste des cellules voisines qui peuvent être mangées
					Cell[] eatable = (cells[i][j]).currentPlayer.hasEnoughNeighbor(cells);
					int longueur = eatable.length;
					boolean state = false;
					// si c'est un herbivore et que sa liste est vide et que son maxLaps==0, on le détruit
					if((cells[i][j]).currentPlayer instanceof Herbivore && longueur==0){
						(cells[i][j]).currentPlayer.maxLaps--;
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
						// en fonction du type de joueur sur la case, on remplace une case par un Plant ou un Herbivore
						if((cells[i][j]).currentPlayer instanceof Plant)
							cells[(eatable[randomInt]).getX()][(eatable[randomInt]).getY()].currentPlayer = new Plant((eatable[randomInt]).getX(),(eatable[randomInt]).getY());
						else if((cells[i][j]).currentPlayer instanceof Herbivore)
							cells[(eatable[randomInt]).getX()][(eatable[randomInt]).getY()].currentPlayer = new Herbivore((eatable[randomInt]).getX(),(eatable[randomInt]).getY());
					}				
				}
			}
		}
	}
}
