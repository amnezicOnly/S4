import java.util.Scanner;


public class ConsoleUI implements UI
{
	private final Scanner     input;
    	private AddressBook addressBook;

    	public ConsoleUI()
    	{
        	input       = new Scanner(System.in);
    	}

	public int readChoice(){	// returns the choice of the user 
		int choice = input.nextInt();
		return choice;
         }

	public Person readPerson(){	// returns a new Person object
		System.out.printf("Name : ");
		String name = input.next();
		System.out.printf("PhoneNumber : ");
		String phoneNumber = input.next();
		return new Person(name,phoneNumber);
	}

	public String readName(){	// returns Scanner input
		return input.next();
		
	}

	public void display(Person person){	// display someone data
		System.out.printf("%-20s%-15s\n","Name","PhoneNumber");
		System.out.printf("%-20s%-15s\n",person.getName(),person.getPhoneNumber());
	}

	public void displayAll(Person[] people){	// call display for each person in addressBook
		System.out.printf("\n%-20s%-15s\n","Name","PhoneNumber");
		for(Person elt : people)
			System.out.printf("%-20s%-15s\n",elt.getName(),elt.getPhoneNumber());
		System.out.println("\n");
	}

	public void run(AddressBook book){
		int choice=0;
		do {
			displayMenu();
			choice = readChoice();
		switch(choice){
			case 1:
				book.addPerson();
				break;
			case 2:
				book.deletePerson();
				break;
			case 3:
				book.findPerson();
				break;
			case 4:
				book.displayAll();
			default:
			//should not get here
		}
		}while (choice != 5);
	}	


	public void displayMenu(){	// display the different choices	
		System.out.printf("\n1) Add\n");
		System.out.printf("2) Delete\n");
		System.out.printf("3) Search\n");
		System.out.printf("4) Display all\n");
		System.out.printf("5) Exit\n");
		System.out.printf("Your choice ? ");
	}

	public void displayErrorMsg(String msg){	// Display an error message
		System.out.printf("%s\n",msg);
	}

	public void displayMsg(String msg){	// Display a simple message
		System.out.printf("%s\n",msg);
	}
}

