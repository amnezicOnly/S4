
// Demonstrating menus
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class MenuTest extends JFrame {
   private Color colorValues[] = 
      { Color.black, Color.blue, Color.red, Color.green };   
   private JRadioButtonMenuItem colorItems[], fonts[];
   private JCheckBoxMenuItem styleItems[];
   private JLabel display;
   private ButtonGroup fontGroup, colorGroup;
   private int style;

   public MenuTest()
   {
      super( "Using JMenus" );     

      JMenuBar bar = new JMenuBar();  // create menubar
      setJMenuBar( bar );  // set the menubar for the JFrame

      // create File menu and Exit menu item
      JMenu fileMenu = new JMenu( "File" );
      fileMenu.setMnemonic( 'F' );
      JMenuItem aboutItem = new JMenuItem( "About..." );
      aboutItem.setMnemonic( 'A' );
      aboutItem.addActionListener(
         new ActionListener() {
            public void actionPerformed( ActionEvent e )
            {
               JOptionPane.showMessageDialog( MenuTest.this,
                  "This is an example\nof using menus",
                  "About", JOptionPane.PLAIN_MESSAGE );
            }
         }
      );
      fileMenu.add( aboutItem );

      JMenuItem exitItem = new JMenuItem( "Exit" );
      exitItem.setMnemonic( 'x' );
      exitItem.addActionListener(
         new ActionListener() {
            public void actionPerformed( ActionEvent e )
            {
               System.exit( 0 );
            }
         }
      );
      fileMenu.add( exitItem );
      bar.add( fileMenu );    // add File menu

      // create the Format menu, its submenus and menu items
      JMenu formatMenu = new JMenu( "Format" );  
      formatMenu.setMnemonic( 'r' );

      // create Color submenu
      String colors[] = 
         { "Black", "Blue", "Red", "Green" };
      JMenu colorMenu = new JMenu( "Color" );
      colorMenu.setMnemonic( 'C' );
      colorItems = new JRadioButtonMenuItem[ colors.length ];
      colorGroup = new ButtonGroup();
      ItemHandler itemHandler = new ItemHandler();

      for ( int i = 0; i < colors.length; i++ ) {
         colorItems[ i ] = 
            new JRadioButtonMenuItem( colors[ i ] );
         colorMenu.add( colorItems[ i ] );
         colorGroup.add( colorItems[ i ] );
         colorItems[ i ].addActionListener( itemHandler );
      }

      colorItems[ 0 ].setSelected( true );
      formatMenu.add( colorMenu );
      formatMenu.addSeparator();

      // create Font submenu
      String fontNames[] = 
         { "TimesRoman", "Courier", "Helvetica" };
      JMenu fontMenu = new JMenu( "Font" ); 
      fontMenu.setMnemonic( 'n' );
      fonts = new JRadioButtonMenuItem[ fontNames.length ];
      fontGroup = new ButtonGroup();

      for ( int i = 0; i < fonts.length; i++ ) {
         fonts[ i ] =
            new JRadioButtonMenuItem( fontNames[ i ] );
         fontMenu.add( fonts[ i ] );
         fontGroup.add( fonts[ i ] );
         fonts[ i ].addActionListener( itemHandler );
      }

      fonts[ 0 ].setSelected( true );
      fontMenu.addSeparator();

      String styleNames[] = { "Bold", "Italic" };
      styleItems = new JCheckBoxMenuItem[ styleNames.length ];
      StyleHandler styleHandler = new StyleHandler();

      for ( int i = 0; i < styleNames.length; i++ ) {
         styleItems[ i ] =
            new JCheckBoxMenuItem( styleNames[ i ] );
         fontMenu.add( styleItems[ i ] );
         styleItems[ i ].addItemListener( styleHandler );
      }

      formatMenu.add( fontMenu );
      bar.add( formatMenu );  // add Format menu
     
      display = new JLabel(
         "Sample Text", SwingConstants.CENTER );
      display.setForeground( colorValues[ 0 ] );
      display.setFont( 
         new Font( "TimesRoman", Font.PLAIN, 72 ) );
	//to change the background you must use the content
	//pane since it "hides" the actual containers background
      getContentPane().setBackground( Color.cyan );

      add( display, BorderLayout.CENTER );

      setSize( 500, 200 );
      setVisible(true);
   }

   public static void main( String args[] )
   {
      MenuTest app = new MenuTest();

      app.addWindowListener(
         new WindowAdapter() {
            public void windowClosing( WindowEvent e )
            {
               System.exit( 0 );
            }
         }
      );
   }

   class ItemHandler implements ActionListener {
      public void actionPerformed( ActionEvent e )
      {
         for ( int i = 0; i < colorItems.length; i++ )         
            if ( colorItems[ i ].isSelected() ) {
               display.setForeground( colorValues[ i ] );
               break;
            }
 
         for ( int i = 0; i < fonts.length; i++ )
            if ( e.getSource() == fonts[ i ] ) {
               display.setFont( new Font( 
                  fonts[ i ].getText(), style, 72 ) );
               break;
            }

         repaint();   
      }
   }

   class StyleHandler implements ItemListener {
      public void itemStateChanged( ItemEvent e )
      {
         style = 0;

         if ( styleItems[ 0 ].isSelected() )
            style += Font.BOLD;

         if ( styleItems[ 1 ].isSelected() )
            style += Font.ITALIC;

         display.setFont( new Font( 
            display.getFont().getName(), style, 72 ) );

         repaint();
      }
   }
}

