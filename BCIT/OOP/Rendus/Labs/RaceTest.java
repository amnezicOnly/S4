// A01410991
// Antoine Leveque

/** In-lab assignment: Threading
1. Create 2 threads to add the data provided in main <1 mark>
2. After the threads have FINISHED, print the resulting linked list (in-order) <1 mark>
3. Exacerbate any existing race conditions <1 mark>

	
********************************************************************************************/

interface DIterator<T> {
	boolean isEmpty();
	boolean hasNext();
	boolean hasPrevious();
	T next();
	T previous();
}
class DLinkedList <T extends Comparable<T>>{
	private DNode head;
	private class DNode {
		T data;
		DNode previous, next;
		DNode(T d){
			data = d;
		}
	}
	public void clear(){
		head = null;
	}
	public boolean insert(T d) {
		try{
		DNode temp = new DNode(d);
		DNode cur = head;
		DNode prev = head;
		//1. empty list case
		if (head == null){//check if list is empty
			head = temp;//if empty, put new item at the start of the list
			return true;
		}
		//2. non-empty list, find position
		while((cur != null) && (cur.data.compareTo(d)<0)){
			prev = cur;
			cur = cur.next;
		}
		//2.1 inserting at end of list
		if (cur == null){
			prev.next = temp;
			temp.previous = prev;
			return true;
		}
		//3. value exists in list already - fail
		if (cur.data.compareTo(d) == 0 )
			return false;
		//4. single node in list
		if (cur == prev){
			//5. single node < new node
			if (cur.data.compareTo(d) < 0){
				cur.next = temp;
				temp.previous = cur;
				return true;
			}
			//6. single node > new node
			temp.next = cur;
			cur.previous = temp;
			head = temp;
			return true;
		}
		//7. multiple nodes in list
		prev.next = temp;
		temp.next = cur;
		//8. check if being added at the start of the list
		// if it is there is no previous node and the head of list
		// needs to change
		if (cur.previous != null)
			cur.previous = temp;
		else
			head = temp;
		temp.previous = prev;
		}catch(Exception e){}
		return true;
	}
	public DIterator<T> iterator(){
		return new DIterator<T>(){
			DNode cur = head;
			public boolean isEmpty(){
				if (cur != null)
					return false;
				return true;
			}
			public boolean hasNext(){
				return cur.next != null;
			}
			public boolean hasPrevious(){
				return cur.previous != null;
			}
			public T next(){
				T d = cur.data;
				cur = cur.next;
				return d;
			}
			public T previous(){
				T d = cur.data;
				cur = cur.previous;
				return d;
			}
		};
	}
}




//CREATE YOUR RUNNABLE CLASS(ES) HERE FOR THREADING
class Race implements Runnable {
	DLinkedList<Integer> linklist;
	public Race(DLinkedList<Integer> list){
		linklist = list;
	}

	public void run() {
		int[] prime = {47,13,23,17};
		for (int i = 0; i < prime.length; i++) {
			linklist.insert(prime[i]);
		}
	}
}

class Race2 implements Runnable {
	DLinkedList<Integer> linklist;
	public Race2(DLinkedList<Integer> list){
		linklist = list;
	}

	public void run() {
		int[] prime = {5,19,37,7};
		for (int i = 0; i < prime.length; i++) {
			linklist.insert(prime[i]);
		}
	}

}

public class RaceTest {
		static DLinkedList<Integer> list = new DLinkedList<Integer>();

	public static void main(String[] args){
		int[] prime1 = {47,13,23,17};//for Thread1
		int[] prime2 = {5,19,37,7};//for Thread2

		Race race = new Race(list);
		Race2 race2 = new Race2(list);

		//make threads and launch them

		Thread Thread1 = new Thread(race);
		Thread Thread2 = new Thread(race2);
		
		Thread1.start();
		Thread2.start();

		try{
			Thread1.join();
			Thread2.join();
		}catch(Exception e){};
		
		
		//make sure you WAIT for Thread1 and Thread2 to complete before attempting to print
		print(list);//result should display missing data, data out of order, different each time
	}
	public static <P extends Comparable<P>> void print(DLinkedList<P> list){
		DIterator<P> i = list.iterator();
		while(!i.isEmpty())
			System.out.print(""+i.next()+" ");
		System.out.println("");
	}
	public static <P extends Comparable<P>> void printR(DLinkedList<P> list){
		DIterator<P> i = list.iterator();
		while(i.hasNext()) i.next();
		while (!i.isEmpty())
			System.out.print(""+i.previous()+" ");
		System.out.println("");
	}
}
		
