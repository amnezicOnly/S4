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


	static JPanel actualGrid(Cell[][] cells, int width, int height){
		JPanel gridPanel = new JPanel(new GridLayout(width, height)); // Utilisation de GridLayout pour la grille
        	// fill each cell of the grid with the correct color
		for (int j=0; j < height; j++) {
			for(int i=0; i<width; i++){
            			JLabel cell = new JLabel();
            			cell.setOpaque(true);
				cell.setBackground(getColor(cells[i][j]));
            			cell.setBorder(BorderFactory.createLineBorder(Color.BLACK)); // Ajout d'une bordure noire
            			gridPanel.add(cell);
			}
        	}
		return gridPanel;
	}

	static void createFrame(JFrame frame, Cell[][] cells, int width, int height){
		// create a new frame
		frame.setPreferredSize(new Dimension(400,400));	
        	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
       		JPanel gridPanel = actualGrid(cells,width,height);
        
        	frame.add(gridPanel);
        	frame.pack(); 
        	frame.setVisible(true);

	}

	public static void main(String[] args) {
		JFrame frame = new JFrame("Game of Life");
		game = new Game(nbCellsX,nbCellsY);
		createFrame(frame, game.world.cells, nbCellsX, nbCellsY);
		game.newLap();
		createFrame(frame, game.world.cells, nbCellsX, nbCellsY);
		System.out.println("Actualisation");

      	}
}
