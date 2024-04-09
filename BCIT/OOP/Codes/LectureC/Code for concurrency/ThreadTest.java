
class DCT implements Runnable{
	double result[][];
	double data[][];
	int runs = 0;
	public DCT(double[][] d, int r){
		data = new double[d.length][d[0].length];
		runs = r;
		for(int i=0; i< d.length;i++)
			System.arraycopy(d[i],0, data[i],0,data.length);
	}
	public void dct(){
		dct(data);
	}
	public void dct(double[][] in){
		int w = in.length;
		int h = in[0].length;
		int u = 0;
		int v = 0;
		double sum = 0.0;
		result = new double[w][h];
		for (u=0;u<w;u++){
			for (v=0;v<h;v++){
				sum = 0.0;
				for (int x=0; x<w; x++)
					for (int y=0; y<h; y++)
						sum += in[x][y]*Math.cos((2*x+1)*u*Math.PI/(2*w))*Math.cos((2*y+1)*v*Math.PI/(2*h));
				sum *= 2/Math.sqrt(h*w)*c(u)*c(v);
				result[u][v] = sum;
			}
		}
	}
	public void run(){
		for(int i=0; i<runs;i++){
			dct();
			idct();
		}
	}
	public void idct(){
		idct(result);		
	}
	public void idct(double[][] in){
		int w = in.length;
		int h = in[0].length;
		int x = 0;
		int y = 0;
		double sum = 0.0;
		double[][] iresult = new double[w][h];
		for (x=0;x<w;x++){
			for (y=0;y<h;y++){
				sum = 0.0;
				for (int u=0; u<w; u++)
					for (int v=0; v<h; v++)
						sum += in[u][v]*Math.cos((2*x+1)*u*Math.PI/(2*w))*Math.cos((2*y+1)*v*Math.PI/(2*h))*c(u)*c(v);
				sum *= 2/Math.sqrt(h*w);
				iresult[x][y] = sum;
			}
		}
		result = iresult;
	}
	public double c(double value){
		if (value == 0)
			return 1/Math.sqrt(2);
		return 1;
	}
	public void display(double[][] in){
		for (int i = 0; i< in.length;i++){
			for (int j = 0; j< in[0].length;j++)
				System.out.printf("%3.1f  ",in[i][j]);
			System.out.println("");
		}
	}
}
public class ThreadTest {
		public static void createThreads(double[][] data, int iterations, int numThreads){
			try{
				System.out.println("Number of threads="+numThreads);
				DCT[] dct = new DCT[numThreads];
				Thread[] t = new Thread[numThreads];
				for(int i=0;i<numThreads;i++){
					dct[i] = new DCT(data, iterations/numThreads);
					t[i] = new Thread(dct[i]);
				}
				long start = System.currentTimeMillis();
				for(int j=0;j<numThreads;j++)
						t[j].start();
				for(int j=0;j<numThreads;j++)
						t[j].join();
				System.out.println(System.currentTimeMillis() - start);
				}
			catch(Exception e){}
		}
		public static void main(String[] args){
			double[][] test3 = {{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7},{0,1,2,3,4,5,6,7}};
			for(int i=1; i<=6; i++)
				createThreads(test3, 1200, i);
			createThreads(test3, 1200, 10);
		}
}