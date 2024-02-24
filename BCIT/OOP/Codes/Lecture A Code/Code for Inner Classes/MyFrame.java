
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;


public class MyFrame extends JFrame{
  private JButton button;
  private MyListener listener;
  Container c;//holds content pane where all components are put
  public MyFrame() {
    super("Simple Button Test");//put title on window
    c = getContentPane();//get the content pane for future use
    c.setLayout(new FlowLayout());//define how components will be layed down
    button = new JButton("Press Me");//create a button
    button.addActionListener(new MyListener());
    add(button);//put button onto window (placed onto content pane)
    //to deal with window events, in particular window closing event
    //add a WindowAdapter to listen and handle the window events
    //using an anonymous inner class
    //note that the definition of the adapter is done in the same "line" as the
    //adapter object is being created
    //Limitation: no other objects using that definition can be made
    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e){
        System.exit(0);
      }
    });
    setSize(350, 150);//resize the window to width=350 height=150 pixels
    setVisible(true);//make the window visible
  }//constructor
  public static void main(String []args){
    new MyFrame();//create an object of this type
  }//main
  //INNER CLASS
  private class MyListener implements ActionListener {
    private boolean change;
    public void actionPerformed(ActionEvent e){
      if (change)
        c.setBackground(Color.orange);//change the outclasses background colour
      else
        c.setBackground(Color.blue);
      change = !change;//toggle
    }//actionPerformed
  }//class MyListener
}//class Main
