
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

/**class MyListener implements ActionListener{
  private boolean change;
  private MyWindow window;
  public MyListener(MyWindow window){
    this.window = window;
  }
  public void actionPerformed(ActionEvent e){
    if (change)
     window.c.setBackground(Color.orange);//change the outclasses background colour
   else
     window.c.setBackground(Color.blue);
   change = !change;//toggle
 }//actionPerformed
}//class MyListener

}**/
public class MyWindow extends JFrame implements ActionListener{
  private JButton button;
  private MyListener listener;
  Container c;//holds content pane where all components are put
  public MyButton() {
    super("Simple Button Test");//put title on window
    c = getContentPane();//get the content pane for future use
    c.setLayout(new FlowLayout());//define how components will be layed down
    button = new JButton("Press Me");//create a button
    button.addActionListener(new MyListener());//add listener to handle button events
    c.add(button);//put button onto window (placed onto content pane)
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
    new MyButton();//create an object of this type
  }//main
  /*
    MyListener is another inner class, however this one has a name.
    Inner classes defined this way allow multiple objects of this type
    to be created. It's sometimes clearer too.

    Inner classes have full access to the outer classes members (including
    private). Think of them as just another (special) member.
    Usually used for Listener type class definitions

    This class deals with action events (button pressed usually)
    When an action event occurs, the outer classes content pane's background
    colour is toggled between orange and blue
  */
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
