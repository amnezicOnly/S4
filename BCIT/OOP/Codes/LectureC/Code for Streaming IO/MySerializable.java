import java.io.*;

public class MySerializable {
    public static void main(String[] args){
        try{
        //write them out
        FileOutputStream f = new FileOutputStream("Class1.ser");
        ObjectOutput out = new ObjectOutputStream(f);

        out.writeObject(new Class1());
        out.flush();
        out.close();

        f = new FileOutputStream("Class2.ser");
        out = new ObjectOutputStream(f);
        out.writeObject(new Class2());
        out.flush();
        out.close();

        //Read them back
        FileInputStream f2 = new FileInputStream("Class1.ser");
        ObjectInputStream in = new ObjectInputStream(f2);
        Class1 cc1 = (Class1) in.readObject();
        in.close();

        f2 = new FileInputStream("Class2.ser");
        in = new ObjectInputStream(f2);
        Class2 cc2 = (Class2) in.readObject();
        in.close();
        System.out.println("cc1="+cc1.toString()+"\n cc2="+cc2.toString());
        }catch(IOException e){
                e.printStackTrace();
        }catch(ClassNotFoundException e){
                e.printStackTrace();
        }
     }
}
