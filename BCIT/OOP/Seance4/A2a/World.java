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
			cells[i][j] = new Cell(player);
		}
	}

	public void printMatrix(){
		int temp;
		for(int j=0; j<nbCellsY; j++){
			for(int i=0; i<nbCellsX; i++){
				temp = (cells[i][j]).getLifeFormNumber();
				if(temp!=-2)
					System.out.println(temp+" ");
				else
					System.out.println("r ");	
			}
			System.out.println("\n");
		}
	}	
}
