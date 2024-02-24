import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.TestInstance.Lifecycle;
@TestInstance(Lifecycle.PER_CLASS)
class ArrayListTest {
	 ArrayList list;
	
	@BeforeAll
	void startup() {
		list = new ArrayList();
	}
	@Test
	void testArrayList() {
		fail("Not yet implemented");
	}

	@Test
	void testArrayListInt() {
		fail("Not yet implemented");
	}

	@Test
	void testAdd() {
	//	ArrayList list = new ArrayList();
		assertNotEquals(null, list);
		assertEquals(10,list.size());
		for (int i=0;i<5;i++)
			list.add(i);
		assertTrue(list.add(11),"Unable to add beyond default size");
	}


	@Test
	void testGetAt() {
		assertEquals(2,list.getAt(2));
		assertEquals(1,list.getAt(1));
		assertEquals(0,list.getAt(0));
	}
	
}
