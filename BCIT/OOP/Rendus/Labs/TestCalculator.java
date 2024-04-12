// Antoine Leveque
// A01410991

import java.util.*;
import java.util.function.*;

/**Lab: A Look at Lambda functions
Use the class and interface provided to explore Lambda functions.

.forEach()
myArray.forEach(<what you want to do>) - the .forEach() method was added to arrays to allow
easy access to elements in an array and works similar to for (t:myArray){}
You can put an expression to work with the each element during the loop. For example
myArray.forEach(t->System.out.print(t++)) will increment each element found in the array by 1 and display it.
*******************

1(OK). Using the method ".forEach()" on the data1 list, apply a Lambda function to add 5 to each
element and store in data2 list. Then using ".forEach()" again on data2 list, display the results <2 marks>
2(OK). Using the processElements() method provided from lecture, call this method
with the data1 list, test for even numbers using a Lambda function, double the value using
a Lambda function, finally display the results using "print") <2 marks>
3(OK). Using the Calc interface, create a method called "calculate()" that takes in as params:
Iterable source, a List dest, and a Calc op. The method should loop thru the source, apply the
method in the Calc storing the results in the dest. Once created, test it using data1 as
source, data2 as dest, and a Lambda expression for multiplying the value in source to itself (not "squared" although
that is the same thing in this case). Print the results in data2 using .forEach()<3 marks>
4. Make a new method called "calculate2" that has the same params as found in #3 however
replace the Calc param type with a BiFunction type (read this online). Test it as above
but the Lambda expression should be to add it to itself (again don't just *2). Print
results as above. <3 marks>
**/

interface Calc<T>{
	T op(T a, T b);
}
public class TestCalculator {
	static List<Double> data1 = new ArrayList<>();
	static List<Double> data2 = new ArrayList<>();
	public static <X, Y> void processElements(
		Iterable<X> source,
		Predicate<X> tester,
		Function <X, Y> mapper,
		Consumer<Y> block) {
			for (X p : source) {
				if (tester.test(p)) {
					Y data = mapper.apply(p);
					block.accept(data);
				}
			}
	}
	//Using Generics and Interfaces complete the parameters and code
	public static <X> void calculate(Iterable<X> source, List<X> dest, Calc<X> op){
		for(X elt : source){
			dest.add(op.op(elt,elt));
		}
	}
	//Using Generics and Interfaces complete the parameters and code
	public static <X> void calculate2(Iterable<X> source, List<X> dest, BiFunction<X, X, X> op){
		for(X elt : source){
			dest.add(op.apply(elt,elt));
		}
	}
	public static void main(String[] args){
		for(int i=10;i<20;i++) data1.add((double)i);
		//Add 5 to each element in data1 using .forEach() storing in data2
		data1.forEach(d -> data2.add(d + 5));
		//display each value in data2 using .forEach()
		data2.forEach(d -> System.out.println(d));
		
		//use processElements method
		System.out.println("processing elements");
		processElements(data1, n -> n%2==0 , n -> n*=2, n -> System.out.println(n));
		
		//use your method calculate() with Lambda expressions
		calculate(data1,data2, (a,b) -> a*a);
		//display result via .forEach() on data2 
		data2.forEach(n -> System.out.println(n));
		
		//repeat using your calculate2() method with Lambda expressions
		calculate2(data1,data2, (a,b) -> a+a);
		data2.forEach(n -> System.out.println(n));
	}
}
