import java.lang.Math;
import java.util.*;
import java.util.stream.*;
import java.util.Comparator;
import java.util.stream.Collectors;

class Transaction {
	Integer ID;
	public enum TYPE {GROCERY, MISC, APPLIANCE};
	TYPE type;
	Integer value;
	public Integer getValue(){return value;}
	public TYPE getType(){return type;}
	public Integer getId(){return ID;}
	public Transaction(int id, TYPE t, int v){ID=id;type=t;value=v;}
}
class DB{
	List<Transaction> transactions = new LinkedList<>();
	public DB(){
		for(int i=0;i<20;i++){
			int choice = (int)(Math.random()*3);
			if (choice > 2)
				transactions.add(new Transaction((int)(Math.random()*1000),Transaction.TYPE.APPLIANCE,(int)(Math.random()*100)));
			else if(choice>1)
				transactions.add(new Transaction((int)(Math.random()*1000),Transaction.TYPE.MISC,(int)(Math.random()*10)));
			else
				transactions.add(new Transaction((int)(Math.random()*1000),Transaction.TYPE.GROCERY,(int)(Math.random()*5)));
		}
	}
}
public class StreamingCollections{
	static DB db = new DB();
	public static List<Integer> getGrocID(){
	List<Transaction> groceryTransactions = new ArrayList<>();
		for(Transaction t: db.transactions){
			if(t.getType() == Transaction.TYPE.GROCERY)
				groceryTransactions.add(t);
		}
		Collections.sort(groceryTransactions, new Comparator<Transaction>(){
			   public int compare(Transaction t1, Transaction t2){
				return t2.getValue().compareTo(t1.getValue());
			}});
		List<Integer> transactionIds = new ArrayList<>();
		for (Transaction t: groceryTransactions)
			transactionIds.add(t.getId());
		return transactionIds;
	}
	public static <T> void print(List<T> list){
		for(T t : list)
			System.out.println(t);
	}
	public static void main(String[] args){
		List<Integer> list = getGrocID();
		print(list);
		System.out.println("=============================");
	}
}
		