import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

//JavaFx application must extend Application 
public class HelloWorld extends Application {

	//JavaFx applications call start (entry point) not the constructor
	//Primary stage is used to hold visual nodes
	public void start(Stage primaryStage) {
		Button btn = new Button();
		btn.setText("Say 'Hello World'");
		btn.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				System.out.println("Hello World!");
			}
		});
		
		//define our top most Node as a StackPane
		StackPane root = new StackPane();
		//add button node to root node
		root.getChildren().add(btn);
		//create a scene and add root node
		Scene scene = new Scene(root, 300, 250);
		primaryStage.setTitle("Hello World!");
		//add scene to stage
		primaryStage.setScene(scene);
		primaryStage.show();
	}
		
	//main() not needed in JavaFX apps but if used must call "launch()" in main()
	public static void main(String[] args) {
		launch(args);
	}
}