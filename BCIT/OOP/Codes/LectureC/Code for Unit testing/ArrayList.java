public class ArrayList {
	Object[] array;
	int pos = 0;
	
	public ArrayList() {
		array = new Object[10];
	}
	public ArrayList(int size) {
		array = new Object[size];
	}
	public int size() {return array.length;}
	public boolean add(Object o) {
		if (pos < array.length)
			array[pos++] = o;
			else
				add(o,10);
		return true;
	}
	private boolean add(Object o, int size) {
		Object[] temp = new Object[array.length+size];
		System.arraycopy(array, 0, temp, 0, array.length);
		temp[pos++] = o;
		array = temp;
		return true;
	}
	public Object getAt(int x) {
		if (x < array.length)
			return array[x];
		else
			return null;
	}
	public static void main(String[] args) {
		ArrayList list = new ArrayList();
		list.add(5);
		list.add(1);
		System.out.println(""+list.getAt(0));

	}

}
