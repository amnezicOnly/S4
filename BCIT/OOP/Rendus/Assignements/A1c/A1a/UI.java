package A1;

/*
 * NewInterface.java
 *
 * Created on January 15, 2006, 9:06 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author ds
 */
public interface UI
{

    void display(String[] database);

    String readName();

    String readPerson();

    void run(Main main);

    void displayMsg(String msg);

    void displayErrorMsg(String msg);

}
