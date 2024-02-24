import java.io.*;
interface Foo extends Serializable
{
	int x = 25;
}
abstract class Bar implements Foo
{
	int x = 25;
}
public class Main extends Bar
{
}

