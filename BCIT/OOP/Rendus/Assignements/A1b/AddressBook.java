/*
 * AddressBook.java

 */


public class AddressBook
{
    private final Database database;
    private final UI       ui;

    public AddressBook(final UI u)
    {
        ui       = u;
        database = new Database();
    }
	
    public void addPerson(){	// add someone in database
	    database.add(ui.readPerson());
    }

    public void deletePerson(){	// remove someone of the database
        System.out.printf("Enter the person name ");
	    String name = ui.readName();
	    boolean state = this.remove(name);
	    if (!state)
		    ui.displayErrorMsg("No such person.\n");
	    else{
		    System.out.printf("%s",name);
		    ui.displayMsg(" was deleted successfully.\n");
	    }
    }

    public void findPerson(){	// display person data if he exist, "No such person" otherwise
        System.out.printf("Enter the persons name ");
	    String qqch = ui.readName();
	    if (database.findByName(qqch)==null)
		    ui.displayErrorMsg("No such person.\n");
        else{
            Person qqn = search(qqch);
            System.out.println();
            display(qqn);
        }
    }

    private boolean remove(final String name)
    {
        return (database.removeByName(name) != null);
    }

    private Person search(final String name)	// return the Person object which the Name name if exist
    {
        return (database.findByName(name));
    }

    public void displayAll()	// Show everybody data
    {
	    ui.displayAll(database.getAll());
    }

    private void display(final Person person)	// use getters to display data
    {
	    System.out.printf("%-20s%-15s\n","Name","PhoneNumber");
	    System.out.printf("%-20s%-15s\n",person.getName(),person.getPhoneNumber());
    }
}
