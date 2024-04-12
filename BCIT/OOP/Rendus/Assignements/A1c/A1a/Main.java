package A1a;
import java.util.Scanner;
import javax.swing.*;
import java.awt.event.*;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dialog;
import java.awt.BorderLayout;
import java.awt.*;

public class Main {
  	private String[] database;
	static GUI window;

  	public Main() {
    		database = new String[0];
			window = new GUI();
  	}

	/**
 	* GUI.
 	* 
 	* @Antoine your name here
 	* @version
 	*/
	public class GUI extends JFrame implements UI {

    		private Main currentMain;
    		private int choice;// users choice 1-5

    		/**
     		* Constructor for objects of type GUI. Constructs the GUI and adds a
     		* keyboard listener to capture the user's choices from the menu.
     		*/
    		public GUI() {
        		setSize(400, 400);// fix window size
        		setVisible(true);// make window visible
        		addKeyListener(new KeyBoardInput());// listen to keyboard input
    		}

    		/**
     		* Displays the people records passed in.
     		* 
     		* @param String[]
     		*/
    		public void display(String[] database) {
       			String msg = "";
        		// create a string of all the enteries in the database
        		// no formating of the data - chose to keep it simple
        		for (String data : database) {
						String[] info = data.split(" ");
            			msg += info[0] + "    " + info[1] + "\n";
        		}
        		JOptionPane.showMessageDialog(this, msg, "Address book enteries", JOptionPane.PLAIN_MESSAGE);
    		}

			public void displayOne(String name) {
				JOptionPane.showMessageDialog(this, name, "Address book enteries", JOptionPane.PLAIN_MESSAGE);
		 }

    		/**
     		* Reads a person's name using a dialog box.
     		* 
     		* @return String - name read in
     		*/
    		public String readName() {
        		final String name = JOptionPane.showInputDialog("Enter the persons name");
        		return (name);
		}

		public String readPhone() {	// Reads a person phone number using a dialog box
			final String phone = JOptionPane.showInputDialog("Enter the person phone number");
			return (phone);
		}

    		/**
     		* Reads in a person's data (name/phone) using two dialog boxes in a string
     		* 
     		* @return string - person data record
     		*/
    		public String readPerson() {	// returns the name and phone number of a person using the dialog box
        		final String name = readName();
        		final String phone = readPhone();
        		if (name == null || phone == null)// make sure we have data to create a
                                          // person
            			return null;

        		return (name + " " + phone);
    		}

    		/**
     		* Sets the main to use so the GUI can communicate with it. Note that
     		* since a GUI is event driven unlike the Console this method has limited
     		* use here.
     		* 
     		* @param Main
     		*/
    		public void run(Main main) {
        		currentMain = main;
    		}

    		/**
     		* Invokes the appropriate method on the main. When the user makes
     		* their selection the Keyboard listener stores the selection value in data
     		* member "choice" and then calls this method.
     		*/
    		private void evaluateChoice() {

        		switch (choice) {
        		case 1:
            		currentMain.addPerson();
            		break;
        		case 2:
				currentMain.deletePerson();
           			break;
        		case 3:
				currentMain.findPerson();
            			break;
        		case 4:
				currentMain.displayAll();
            			break;
        		case 5:
            			System.exit(0);
            			break;
        		default:
            			// should not get here
        	}

    	}

    	/**
     	* Clears and draws the main menu on the window.
     	* 
     	* @param g
     	*            Graphics - device context to allow drawing on this window
     	*/
    	private void displayMenu(Graphics g) {
        	Color c = this.getBackground();// colour to clear screen with
        	g.setColor(c);// use that colour
        	// colour in a rectangle the size of the window with that colour
        	g.fillRect(0, 0, this.getWidth(), this.getHeight());
        	g.setColor(Color.black);// set colour to draw with now to black
        	g.drawString("1) Add", 100, 100);
        	g.drawString("2) Delete", 100, 120);
        	g.drawString("3) Search", 100, 140);
        	g.drawString("4) Display All", 100, 160);
        	g.drawString("5) Exit", 100, 180);
    	}

    	/**
     	* Displays the menu when window requires repainting.
     	* 
     	* @param g
     	*            Graphics - device context for the window to draw on
     	*/
    	public void paint(Graphics g) {
        	displayMenu(g);
    	}

    	/**
     	* Displays a message on the title bar of the window.
     	* 
     	* @param msg
     	*            String - non-error message to display
     	*/
    	public void displayMsg(String msg) {
        	setTitle(msg);
    	}

    	/**
     	* Displays an error message in a dialog box.
		* @param msg
     	*            String - error msg to display
     	*/
    	public void displayErrorMsg(String msg) {
        	JOptionPane.showMessageDialog(this, msg, "Error", JOptionPane.ERROR_MESSAGE);
    	}

    	/*
     	* KeyBoardInput.
     	*
     	* A private (no one else needs access to this class) inner class (this
     	* class needs access to the GUI to handle user selections) that listens for
     	* keys pressed.
     	*
     	*/
	    	private class KeyBoardInput extends KeyAdapter {

	       		/**
		 	* Responds when a key is pressed on the keyboard.
		 	* 
		 	* @param e
		 	*            KeyEvent - key pressed and other information
		 	*/
			public void keyTyped(KeyEvent e) {
		    	// set the "choice" data member of the outer class GUI
		    	// to get the integer value, get the character value of the key
		    	// pressed, make it a string and ask the Integer class to parse it
		    		try {
		        		choice = Integer.parseInt("" + e.getKeyChar());
		        		// if it wasn't an integer key pressed then make an invalid
		        		// choice
		    		} catch (Exception except) {
		        		choice = -1;// this will result in nothing happening
		    		}
		    		evaluateChoice(); // GUI method to call the addressBook to perform
		                      // task
			}
	    	}
	}
	
	
	public void add(final String name){	// add name in the database
    		String[] temp = new String[database.length +1];
    		System.arraycopy(database, 0, temp, 0, database.length);
    		temp[database.length] = name;
    		database = temp;
  	}
  
  	public int search(final String name){	// search name (name+phoneNumber) in the database
    		String name2;

    		for (int pos=0; pos<database.length; pos++){
      			name2= database[pos];

      			if (name.compareToIgnoreCase(name2)==0){
        			return pos;
      			}
    		}
    		return -1;
  	}
  	
  	
	public void display(int pos){	// call GUI method to display one person info
		window.displayOne(database[pos]);
	}
	
	/* useless
  	public void displayHeading(){	
    		String heading1 = "Name";
    		String heading2 = "Phone";
    		window.displayMsg(heading1 + "     " + heading2);
  	}
  	*/
  	
  	
  	public void displayAll(){	// display each person data
    		window.display(database);
  	}
  	
  	
  	public boolean remove(final String name){	// remove name of the database
    		int pos = 0;
    		for (int i = pos; i < database.length; i++) {
            		if (database[i].startsWith(name)) {
                		break; // Sortir de la boucle si un élément commence par "name"
            		}
            	}
            	
    		if (pos >= 0 && pos!=database.length){
      			String[] temp = new String[database.length-1];
      			System.arraycopy(database,0,temp, 0, pos);
      			System.arraycopy(database, pos+1, temp, pos, database.length-pos-1);
      			database = temp;
      			return true;
    		}
    		return false;
  	}


	public void addPerson(){	// ask name of a person and add him
    		String info = window.readPerson();
		add(info);
  	}

  	public void deletePerson(){	// ask name of a person and delete him
    		String name="";
      		try{
        		name = window.readName();
      		}catch(Exception e){}
    		if (!remove(name))
      			window.displayErrorMsg("Could not delete "+name);
    		else
			window.displayMsg(name + " was deleted successfully");
  	}
  	
  	
  	public void findPerson(){	
    		String name="";
      		try{
        		name = window.readName();
      		}catch(Exception e){}
    		int pos = search(name);
    		if (pos >=0){
     			display(pos);
    		}
    		else{
      			window.displayErrorMsg("No such person");
    		}
  	}
  	
	
  	public static void main(String[] args) {
			Main main = new Main();
    		window.run(main);;
  	}
}
