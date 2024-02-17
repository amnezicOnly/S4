public class Game{
	int nbCellsX;
	int nbCellsY;
	World world;

	public Game(int nbCellsx, int nbCellsy){
		nbCellsX = nbCellsx;
		nbCellsY = nbCellsy;
		world = new World(nbCellsX,nbCellsy);
		firstLap(world);
	}

	public void firstLap(World world){
		for(int j=0; j<nbCellsY; j++){
			for(int i=0; i<nbCellsX; i++){
				int temp = RandomGenerator.nextNumber(100);
				if(temp>=85){
					world.updateCell(world.cells,i,j,new Herbivors());
					System.out.println("1 ");
				}
				else if(temp>=65){
					world.updateCell(world.cells,i,j,new Herbs());
					System.out.println("0 ");
				}
				else{
					world.updateCell(world.cells,i,j,null);
					System.out.println("r ");
				}
					
			}
			System.out.println("\n");
		}
	}
}
