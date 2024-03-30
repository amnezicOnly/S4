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
		RandomGenerator.reset();
		for(int j=0; j<nbCellsY; j++){
			for(int i=0; i<nbCellsX; i++){
				int temp = RandomGenerator.nextNumber(100);
				if(temp>=80){
					world.updateCell(i,j,new Herbivore(i,j));
				}
				else if(temp>=60){
					world.updateCell(i,j,new Plant(i,j));
				}
				else if(temp>=50){
					world.updateCell(i,j,new Carnivore(i,j));
				}
				else if(temp>=45){
					world.updateCell(i,j,new Omnivore(i,j));
				}
				else{
					world.updateCell(i,j,null);
				}
					
			}
		}
	}
	
	public void newLap(){
		world.newLap();
	}
}
