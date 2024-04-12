package A1B;

import javafx.event.*;
import javafx.scene.paint.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.*;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import javafx.scene.input.KeyEvent;
import javafx.event.EventHandler;

import javafx.scene.canvas.Canvas;
import javafx.scene.control.Alert;
import javafx.scene.control.TextInputDialog;
import java.util.Optional;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Alert.AlertType;
import javafx.application.Application;
import javafx.stage.Stage;


public final class GUI extends Application implements UI {
 private static AddressBook addressBook;//interface to database
 private int choice;//users choice 1-5
 private Canvas canvas = new Canvas(400,400);
 private Alert mbox;
 private TextInputDialog dialog;
 private static Stage window;
 /**
  * Purpose: construct the GUI and add a keyboard listener to capture
  * the users choices from the menu
  */
  
  
 public void start(Stage stage){
   window = stage;
 
   HBox root = new HBox();
   root.getChildren().add(canvas);
   Scene scene = new Scene(root,400,400);
	stage.setScene(scene);
	scene.addEventFilter(KeyEvent.KEY_PRESSED, new EventHandler<KeyEvent>(){
	   public void handle(final KeyEvent keyevent){
		try{
         choice = Integer.parseInt("" + keyevent.getText());
         //if it wasn't an integer key pressed then make an invalid choice
       }catch(Exception except){
         choice = -1;//this will result in nothing happening
       }
     evaluateChoice(); //GUI method to call the addressBook to perform task
   }});
   displayMenu();
   stage.show();
  }

  /**
   * Purpose: displays the people records passed in
   * @param people Person[] - records of people (from address book)
   */
  public void display(Person ... people){
    String msg = "";
    //create a string of all the enteries in the address book
    //no formating of the data - chose to keep it simple
      for (Person p:people){
        msg+=p.getName()+"    ";
        msg+=p.getPhoneNumber()+"\n";
      }
	  //display info in a dialog box
	  mbox = new Alert(AlertType.INFORMATION);
	  mbox.setTitle("People");
	  mbox.setHeaderText(null);
	  mbox.setContentText(msg);

	  mbox.showAndWait();
 }

 /**
  * Purpose: reads the persons name using a dialog box
  * @return String - name read in
  */
 public String readName(){

	String msg = "Please enter name:";
   
   return (readData(msg));

 }
/**
Purpose: display a message to request data and read in
		the String data uisng a dialog box
		@String msg - message to display in dialog box
		@return String - data read in
*/
private String readData(String msg){
	dialog = new TextInputDialog("");
	dialog.setTitle("Input");
	dialog.setHeaderText(null);
	dialog.setContentText(msg);

	Optional<String> result = dialog.showAndWait();
   
   return (result.get());

}
 /**
  * Purpose: reads in the Person data (name/phone) using two dialog boxes
  * creates a Person object with the data
  * @return Person - person data record
  */
 public Person readPerson(){
   final Person person;
   final String name;
   final String phone;
   name = readName();//since we have a method to read the name already
   phone = readData("Enter the persons phone number");
   if (name == null || phone == null)//make sure we have data to create a person
     return null;
   person = new Person(name, phone);

   return (person);

 }

 /**
  * Purpose: Assigns the AddressBook to use so GUI can communicate with it.
  * Note that since a GUI is event driven unlike the Console this method
  * has limited use here.
  * @param book AddressBook - interface to the database of Person records
  */
 public void run(AddressBook book){
   addressBook = book;
   launch();
 }

 /**
  * Purpose: When the user makes their selection the Keyboard listener stores
  * the selection value in data member "choice" and then calls this method.
  * Based on the users choice we call the appropriate method on the
  * addressBook.
  */
 private void evaluateChoice(){

    switch(choice)
    {
        case 1:
            addressBook.addPerson();
            break;
        case 2:
            addressBook.deletePerson();
            break;
        case 3:
            addressBook.findPerson();
            break;
        case 4:
            addressBook.displayAll();
            break;
        case 5:
          System.exit(0);
          break;

        default:
            //should not get here
    }

 }

 /**
  * Purpose: Clears and draws the main menu on the window
  * 
  */
 private void displayMenu(){
   GraphicsContext g = canvas.getGraphicsContext2D();
   
   g.strokeText("1) Add",100,100);
   g.strokeText("2) Delete",100,120);
   g.strokeText("3) Search",100,140);
   g.strokeText("4) Display All",100,160);
   g.strokeText("5) Exit",100,180);
 }

 /**
  * Purpose: displays a message on the title bar of the window
  * @param msg String - non-error message to display
  */
 public void displayMsg(String msg){
   window.setTitle(msg);
 }

 /**
  * Purpose: displays an error message in a dialog box
  * @param msg String - error msg to display
  */
 public void displayErrorMsg(String msg){
	mbox = new Alert(AlertType.INFORMATION);
	mbox.setTitle("Error");
	mbox.setHeaderText(null);
	mbox.setContentText(msg);

	mbox.showAndWait();
   }
 
}
