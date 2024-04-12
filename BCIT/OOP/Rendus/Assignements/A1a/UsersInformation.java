// to search a String in a String, it could be used .startWith("text")


import java.util.Scanner;

public class UsersInformation {
	private String[] database;
	private Scanner input;

	public UsersInformation() {
		database = new String[0];
		input = new Scanner(System.in);
	}

	public void add(final String name){	// add name in database
	    String[] temp = new String[database.length + 1]; // new database
	    System.arraycopy(database, 0, temp, 0, database.length); // recopy the element of database in temp
	    temp[database.length] = name; // we add name at the end of temp
	    database = temp; // database has the same value as temp;
	}

	public int search(final String name){	// returns the index of name in database if exist, -1 otherwise
		int max = database.length;
		for(int i=0; i<max; i++){	// i the index
			String personne = database[i];
			String[] infos = personne.split(" ");	// separate name and phone number
			if (name.equals(infos[0])){	// if this element is the same as name
				return i;
			}
		}
		return -1;
	}
	
	
	public void displayAll(){	// display each person of database inforamtion (Name and PhoneNumber) on a line
		System.out.printf("%-20s%-15s\n", "Name", "PhoneNumber");
		for (String personne : database){
			String[] infos = personne.split(" ");
			System.out.printf("%-20s",infos[0]);
			System.out.printf("%-15s\n",infos[1]);
		}
	}

	
	public boolean remove(final String name){
		int pos = search(name);
		if (pos >= 0){
			String[] temp = new String[database.length-1];
			System.arraycopy(database,0,temp, 0, pos);
			System.arraycopy(database, pos+1, temp, pos, database.length-pos-1);
			database = temp;
			return true;
		}
		return false;
	}

	
	public void displayMenu(){
		System.out.println("\n\n\n1) Add");
		System.out.println("2) Delete");
		System.out.println("3) Search");
		System.out.println("4) Display All");
		System.out.println("5) Exit\n");
	}

	
	public int getChoice(){
		int choice = 4;//default
		boolean done = false;
		while(!done){
			System.out.print("choice? ");
		try{
			choice = input.nextInt();
		}catch(Exception e){}
		if (choice >0 && choice <= 5)
			done = true;
		else
			System.out.println("\nYour choice is incorrect, please try again");
		}
		return choice;
	}
 
	public void addPerson(){
		String name="";
		String phone="";
		boolean done = false;
		try{
			System.out.print("Enter the persons name ");
			name = input.next();
			System.out.print("\nEnter the persons phone number ");
			phone = input.next();
			System.out.println("");
		}catch(Exception e){}
		add(name +" "+ phone);
	}

	
	public void deletePerson(){
		String name="";
		try{
			System.out.print("Enter the persons name ");
			name = input.next();
			System.out.println("");
		}catch(Exception e){}
		if (!remove(name))
			System.out.println("Could not delete "+name);
		else
			System.out.println(name + " was deleted successfully");
	}

	
	public void findPerson(){	// display person information if exist in database
		String name="";
		try{
			System.out.print("Enter the persons name ");
			name = input.next();
			System.out.println("");
		}catch(Exception e){}
		int pos = search(name);
		if (pos >=0){
			String personne = database[pos];
			String[] infos = personne.split(" ");
			System.out.printf("%-20s %-15s","Name","PhoneNumber");
			System.out.printf("\n%-20s %-15s", infos[0], infos[1]);


		}
		else{
		System.out.println("No such person");
		}
	}

	
	public void run(){
		int choice=0;
		do {
			displayMenu();
			choice = getChoice();
		switch(choice){
			case 1:
				addPerson();
				break;
			case 2:
				deletePerson();
				break;
			case 3:
				findPerson();
				break;
			case 4:
				displayAll();
			default:
			//should not get here
		}
		}while (choice != 5);
	}


	
	public static void main(String[] args) {
		new UsersInformation().run();
	}
}
