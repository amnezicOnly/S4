import javax.swing.*;
import java.awt.*;
public class Main {
	// game object that will be displayed
	static Game game;

	// Number of column and line on the grid
	// arbitrary choose but could be be modified with a method in the future if needed
	static int nbCellsX = 25;
	static int nbCellsY = 25;

	public static Color getColor(Cell cell){
		if((cell.currentPlayer)!=null){
			if(cell.currentPlayer instanceof Plant)
				return Color.GREEN;
			else if(cell.currentPlayer instanceof Herbivore)
				return Color.YELLOW;
		}
		return Color.WHITE;
	}
	
	static JPanel createGrid(int width, int height){
		JPanel gridPanel = new JPanel(new GridLayout(width, height));
		for (int j=0; j < height; j++) {
			for(int i=0; i<width; i++){
				JLabel cell = new JLabel();
            			cell.setOpaque(true);
				cell.setBackground(Color.WHITE);
            			cell.setBorder(BorderFactory.createLineBorder(Color.BLACK)); // Ajout d'une bordure noire
            			gridPanel.add(cell);
			}
        	}
		return gridPanel;
	}


	static void actualGrid(Cell[][] cells, int width, int height, JPanel gridPanel){
		Component[] components = gridPanel.getComponents();
		for (int i=0; i < width; i++) {
			for(int j=0; j<height; j++){
				int index = (i*width)+j;
            			Component cell = components[index];
				cell.setBackground(getColor(cells[i][j]));
            		}
        	}
	}

	static JFrame createFrame(String title){
		// create a new frame
		JFrame frame = new JFrame(title);
		frame.setPreferredSize(new Dimension(400,400));	
        	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                
        	frame.pack(); 
        	frame.setVisible(true);
        	return frame;
	}

	public static void main(String[] args) {
		// Création de la fenêtre et initialisation de la partie et de la grille
		JFrame frame = createFrame("Game of Life");
		JPanel gridPanel = createGrid(nbCellsX, nbCellsY);
		frame.add(gridPanel);
		frame.setPreferredSize(new Dimension(500,500));
		game = new Game(nbCellsX,nbCellsY);
		actualGrid(game.world.cells, nbCellsX, nbCellsY, gridPanel);
		game.newLap();
		actualGrid(game.world.cells, nbCellsX, nbCellsY, gridPanel);
      	}
}
