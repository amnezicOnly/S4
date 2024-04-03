import java.time.*;
import java.util.*;
import java.util.function.*;
class Person {
	 public enum Sex { MALE, FEMALE } 
	public Person(String n, LocalDate d, Sex g, String e){
		name = n;
		birthday = d;
		gender = g;
		emailAddress = e;
	}
	String name; 
	LocalDate birthday; 
	Sex gender; 
	String emailAddress; 
	public String getEmail(){return emailAddress;}
	public Sex getGender(){ return gender;}
	public int getAge() { return Period.between(birthday, LocalDate.now()).getYears();} 
	public void printPerson() { 
		System.out.print(name+" born "+birthday+" sex: "+gender+" age: "+getAge()+" email: "+emailAddress+"\n");
	} 
}
class DB {
	List<Person> list;
	public DB(){
		list = new ArrayList<Person>();
		list.add(new Person(
			"Nomad",
			LocalDate.of(2000,Month.NOVEMBER ,22),
			Person.Sex.MALE,
			"nomie@box.com"
		));
		list.add(new Person(
			"Fiver",
			LocalDate.of(2013,Month.FEBRUARY, 12),
			Person.Sex.FEMALE,
			"five@pretty.com"
		));
		list.add(new Person(
			"Buddha",
			LocalDate.of(2016, Month.SEPTEMBER, 8),
			Person.Sex.MALE,
			"bud@enlighten.com"
		));
		list.add(new Person(
			"Portia",
			LocalDate.of(2000, Month.OCTOBER, 26),
			Person.Sex.FEMALE,
			"portia@pretty.com"
		));
	}
}

public class Lambda {
	static DB db = new DB();
	static void printPersons(List<Person> roster,Predicate<Person> f,Function<Person, String> x, Consumer<String> block) { 
		for (Person p : roster) { 
			if (f.test(p)) {
				String data = x.apply(p);
				block.accept(data);
			} 
		}
	}
	public static void main(String[] args){
		printPersons(db.list,(Person p) -> p.getGender() == Person.Sex.MALE 
					&& p.getAge() >= 18 
					&& p.getAge() <= 25,
					p->p.getEmail(),
					email->System.out.println(email)
					);
	}
}
	