
// Demonstrating FlowLayout alignments.
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FlowLayoutDemo extends JFrame {
   private JButton left, center, right;
   private Container c;
   private FlowLayout layout;
   
   public FlowLayoutDemo()
   {
      super( "FlowLayout Demo" );

      layout = new FlowLayout();

      c = getContentPane();
      c.setLayout( layout );

      left = new JButton( "Left" );
      left.addActionListener(
         new ActionListener() {
            public void actionPerformed( ActionEvent e )
            {
               layout.setAlignment( FlowLayout.LEFT );

               // re-align attached components
               layout.layoutContainer( c );
            }
         }
      );
      add( left );

      center = new JButton( "Center" );
      center.addActionListener(
         new ActionListener() {
            public void actionPerformed( ActionEvent e )
            {
               layout.setAlignment( FlowLayout.CENTER );

               // re-align attached components
               layout.layoutContainer( c );  
            }
         }
      );
      add( center );

      right = new JButton( "Right" );
      right.addActionListener(
         new ActionListener() {
            public void actionPerformed( ActionEvent e )
            {
               layout.setAlignment( FlowLayout.RIGHT );

               // re-align attached components
               layout.layoutContainer( c );  
            }
         }
      );
      add( right );

      setSize( 300, 75 );
      setVisible(true);
   }

   public static void main( String args[] )
   { 
      FlowLayoutDemo app = new FlowLayoutDemo();

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
