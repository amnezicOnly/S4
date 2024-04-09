pulic class MyArray{
public static void main(String[] args){
        int[][] a = {{1,2},{3,4}};
        int [][] b = new int[2][2];
        //System.arraycopy(a,0,b,0,a.length);
        System.arraycopy(a[0],0,b[0],0,a[0].length);
        System.arraycopy(a[1],0,b[1],0,a[1].length);
        for(int i=0;i<b.length;i++)
        {
        for(int j=0;j<b[i].length;j++)
        System.out.print(b[i][j]);
        System.out.println("");
        }
        }
        }
