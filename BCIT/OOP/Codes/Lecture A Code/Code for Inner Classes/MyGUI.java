import javafx.scene.*;
import javafx.stage.*;
import javafx.application.*;
import javafx.scene.canvas.*;
import javafx.event.*;
import javafx.scene.paint.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;

public class MyGUI extends Application{
Boolean blue = true;
Canvas canvas = new Canvas(100,100);
	public void start(Stage stage){
		GraphicsContext gc = canvas.getGraphicsContext2D();
		gc.setFill(Color.BLUE);
		gc.fillRect(0,0,100,100);
		Button pressMe = new Button("Press Me");
		pressMe.setOnAction(new OuterButtonEvent(this));
	//	pressMe.setOnAction(new ButtonEvent());
	/*	pressMe.setOnAction(new EventHandler<ActionEvent>(){
			GraphicsContext gc = canvas.getGraphicsContext2D();
			{
			gc.setFill(Color.BLUE);
			gc.fillRect(0,0,100,100);
			}
			public void handle(ActionEvent e){
				if (blue){
					blue = false;
					gc.setFill(Color.GREEN);
				}else{
					blue = true;
					gc.setFill(Color.BLUE);
				}
				gc.fillRect(0,0,100,100);
			}});
			*/
		VBox root = new VBox();
		root.getChildren().addAll(pressMe, canvas);
		root.setMinSize(350,250);
		Scene scene = new Scene(root);
		stage.setScene(scene);
		stage.setTitle("My GUI");
		stage.show();
	}

class ButtonEvent implements EventHandler<ActionEvent> {
	GraphicsContext gc = canvas.getGraphicsContext2D();
	public ButtonEvent(){
			gc.setFill(Color.BLUE);
			gc.fillRect(0,0,100,100);
			}
	public void handle(ActionEvent e){
		if (blue){
			blue = false;
			gc.setFill(Color.GREEN);
		}else{
			blue = true;
			gc.setFill(Color.BLUE);
		}
		gc.fillRect(0,0,100,100);
	}
}
}
class OuterButtonEvent implements EventHandler<ActionEvent>{
		MyGUI outer;
		GraphicsContext gc;
		Boolean blue = false;
		public OuterButtonEvent(MyGUI my){
			outer = my;
			gc = my.canvas.getGraphicsContext2D();
			gc.setFill(Color.BLUE);
			gc.fillRect(0,0,100,100);
		}
		public void handle(ActionEvent e){
		if (blue){
			blue = false;
			gc.setFill(Color.GREEN);
		}else{
			blue = true;
			gc.setFill(Color.BLUE);
		}
		gc.fillRect(0,0,100,100);
	}
}
		