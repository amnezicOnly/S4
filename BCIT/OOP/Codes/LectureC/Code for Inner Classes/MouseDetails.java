
// Demonstrating mouse clicks and
// distinguishing between mouse buttons.
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MouseDetails extends JFrame {
   private String s = "";
   private int xPos, yPos;

   public MouseDetails()
   {
      super( "Mouse clicks and buttons" );

      addMouseListener( new MouseClickHandler() ); 

      setSize( 350, 150 );
      setVisible(true);
   }

   public void paint( Graphics g )
   {
      g.drawString( "Clicked @ [" + xPos + ", " + yPos + "]",
                    xPos, yPos );
   }

   public static void main( String args[] )
   {
      MouseDetails app = new MouseDetails();

      app.addWindowListener(
         new WindowAdapter() {
            public void windowClosing( WindowEvent e )
            {
               System.exit( 0 );
            }
         }
      );
   }

   // inner class to handle mouse events
   private class MouseClickHandler extends MouseAdapter {
      public void mouseClicked( MouseEvent e )
      {
         xPos = e.getX();
         yPos = e.getY();

         String s =
            "Clicked " + e.getClickCount() + " time(s)";
      
         if ( e.isMetaDown() )      // Right mouse button
            s += " with right mouse button";
         else if ( e.isAltDown() )  // Middle mouse button
            s += " with center mouse button";
         else                       // Left mouse button
            s += " with left mouse button";

         setTitle( s );  // set the title bar of the window
         repaint();
      }
   }
}

