import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.*;
import javafx.scene.control.Label;
import javafx.stage.Stage;

class FirstStage extends Stage{
	Button openOther = new Button("Open other Stage");
	HBox x = new HBox();

	FirstStage(){
		x.getChildren().add(openOther);
		this.setScene(new Scene(x, 300, 300));
		this.show();

		openOther.setOnAction(new EventHandler<ActionEvent>() {
			public void handle(ActionEvent t) {
				new SecondStage();
			}//end action
		});
	}
}

class SecondStage extends Stage {
	Label x = new Label("Second stage");
	VBox y = new VBox();

	SecondStage(){
		y.getChildren().add(x);
		this.setScene(new Scene(y, 300, 300));
		this.show();
	}    
}

public class TwoStages extends Application{
	public void start(Stage primaryStage){
		new FirstStage();
	}
}