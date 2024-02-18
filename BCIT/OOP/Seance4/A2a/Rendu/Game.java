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
	
	// initialize the first lap with RandomGenerator
	public void firstLap(World world){
		for(int j=0; j<nbCellsY; j++){
			for(int i=0; i<nbCellsX; i++){
				int temp = RandomGenerator.nextNumber(100);
				if(temp>=85){
					world.updateCell(world.cells,i,j,new Herbivore(i,j));
				}
				else if(temp>=65){
					world.updateCell(world.cells,i,j,new Plant(i,j));
				}
				else{
					world.updateCell(world.cells,i,j,null);
				}
					
			}
		}
	}
}
