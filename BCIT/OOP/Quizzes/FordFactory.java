// ID
// Nom

import java.lang.Thread;

interface Car {
	
  	boolean drive();
  	void turn();

  	class Construct {
      		public void constructCar() {
          		System.out.println("Constructing car components");
          		buildEngine();
          		buildBody();
      		}

      		void buildEngine() {}
      		void buildBody() {}
  	}
}

interface CarFactory {
  	Car getCar();
}

class ModelA implements Car{
	private int maxDistance = 3;
	private int distance = 0;
	
	private ModelA(){
      		new ConstructA().constructCar();
	}
	
	class ConstructA extends Car.Construct{
		void buildEngine() {
      			System.out.println("basic engine");
      		}

      		void buildBody() {
      			System.out.println("modelA body");
      		}
      	}
      	
	
	public boolean drive() {
      		System.out.println("ModelA drove " + distance++);
      		return (distance<maxDistance);
  	}
  	
  	public void turn(){
  		System.out.println("ModelA turning");
  		distance = 0;
  	}
  	
  	public static CarFactory factory = new CarFactory(){
  		public Car getCar(){return new ModelA();}
  	};
}

class ModelT implements Car{
	
	private int maxDistance = 5;
	private int distance = 0;
	
	private ModelT(){
      		new ConstructT().constructCar();
	}
	
	class ConstructT extends Car.Construct{
		void buildEngine() {
      			System.out.println("improved engine");
      		}

      		void buildBody() {
      			System.out.println("modelT body");
      		}
      	}
      	
	
	public boolean drive() {
      		System.out.println("ModelT drove " + distance++);
      		return (distance<maxDistance);
  	}
  	
  	public void turn(){
  		System.out.println("ModelT turning");
  		distance = 0;
  	}
  	
  	public static CarFactory factory = new CarFactory(){
  		public Car getCar(){return new ModelT();}
  	};	
}


public class FordFactory {
	public static void produce(CarFactory factory) {
		int turn = 0;
		Car c = factory.getCar();
		while(c.drive()){
			try{
				Thread.sleep(300);
			}catch(Exception e){}
			turn = (int)(Math.random()*4);
			if ( turn > 2)
				c.turn();
     		}
  	}
  
  	public static void main(String[] args) {
    		produce(ModelA.factory);
    		produce(ModelT.factory);
  	}
} 
