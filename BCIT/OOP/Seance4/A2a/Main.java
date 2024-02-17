import javax.swing.*;
import java.awt.*;

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Game of Life");
	frame.setPreferredSize(new Dimension(400, 300));	
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel gridPanel = new JPanel(new GridLayout(10, 10)); // Utilisation de GridLayout pour la grille
        
        // Boucle pour créer 100 cellules dans la grille
        for (int i = 0; i < 100; i++) {
            JLabel cell = new JLabel();
            cell.setBorder(BorderFactory.createLineBorder(Color.BLACK)); // Ajout d'une bordure noire
            gridPanel.add(cell);
        }
        
        frame.add(gridPanel); // Ajout de la grille à la fenêtre
        frame.pack(); // Ajuster la taille de la fenêtre pour s'adapter à la grille
        frame.setVisible(true);
    }
}
