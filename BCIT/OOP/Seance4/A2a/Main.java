import javax.swing.*;
import java.awt.*;

public class Main {
	static Game game;
	
	static JPanel actualGrid(Cell[][] cells, int width, int height){
		JPanel gridPanel = new JPanel(new GridLayout(width, height)); // Utilisation de GridLayout pour la grille
        	int nbCells = width*height;
        	// Boucle pour créer 100 cellules dans la grille
        	for (int i = 0; i < nbCells; i++) {
            		JLabel cell = new JLabel();
            		cell.setBorder(BorderFactory.createLineBorder(Color.BLACK)); // Ajout d'une bordure noire
            		gridPanel.add(cell);
        	}
		return gridPanel;
	}

	static void createFrame(JFrame frame, Cell[][] cells, int width, int height){
		frame.setPreferredSize(new Dimension(400,400));	
        	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
       		JPanel gridPanel = actualGrid(cells,width,height);
        
        	frame.add(gridPanel); // Ajout de la grille à la fenêtre
        	frame.pack(); // Ajuster la taille de la fenêtre pour s'adapter à la grille
        	frame.setVisible(true);

	}

	public static void main(String[] args) {
		// Initialisation de la fenêtre
		JFrame frame = new JFrame("Game of Life");
		int nbCellsX = 10;
		int nbCellsY = 10;
		game = new Game(nbCellsX,nbCellsY);
		createFrame(frame, game.world.cells, nbCellsX, nbCellsY);

		// Initialisation du monde	
      	}
}
