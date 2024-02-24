
// Using a JPanel to help lay out components.
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class PanelDemo extends JFrame {
   private JPanel buttonPanel;
   private JButton buttons[];

   public PanelDemo()
   {
      super( "Panel Demo" );

      Container c = getContentPane();
      buttonPanel = new JPanel();
      buttons = new JButton[ 5 ];

      buttonPanel.setLayout(
         new GridLayout( 1, buttons.length ) );

      for ( int i = 0; i < buttons.length; i++ ) {
         buttons[ i ] = new JButton( "Button " + (i + 1) );
         buttonPanel.add( buttons[ i ] );
      }

      add( buttonPanel, BorderLayout.SOUTH );

      setSize( 425, 150 );
      setVisible(true);
   }

   public static void main( String args[] )
   {
      PanelDemo app = new PanelDemo();

      app.addWindowListener(
         new WindowAdapter() {
            public void windowClosing( WindowEvent e )
            {
               System.exit( 0 );
            }
         }
      );
   }
}
