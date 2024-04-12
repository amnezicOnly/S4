// A01410991
#include <stdio.h>
#include <stdlib.h>

int mainFunction(int shift, long long first, int negative1, long long second, int negative2){
    long long result = first*second;
    long long mask = 0LL;
    if(negative1==negative2){
	for(int i=shift-1; i>=0; i--){
		mask<<=1;
		if((result & 1<<i)==(1<<i))
			mask++;
	}
        if(result!=mask || (result & 1<<(shift-1))==(1<<(shift-1)))
            return 1;
        return 0; 
    }
    else{
	for(int i=shift; i<64; i++){
		mask<<=1;
		mask++;
	}
	for(int i=shift-1; i>=0; i--){
		mask<<=1;
		if((result & 1<<i)==(1<<i))
			mask++;
	}

        if((result & mask)!=mask || ((result & 1<<(shift-1))!=(1<<(shift-1))))
            return -1;
        return 0;
    }
}


int main(int argc, char **argv){
	// argc : number of argument from the command line
	// argv[0] : name of the program
	// argv[>0] : user input
	if(argc!=3)
		perror("Wrong argument count, usage : ./a.out input.txt output.txt\n");
	
	FILE* input = fopen(argv[1],"r");
	if (input==NULL)
		perror("Unable to open input file.\n");
	FILE* output = fopen(argv[2],"w");
	if (output==NULL)
		perror("Unable to open output file.\n");
	
	int shift = 0;
	char temp;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!='-')
			shift = shift*10 + (temp-'0');

    if(temp=='E' || temp==EOF){
        fputs("Input file should contains exactly 1 or 3 values.\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

	if(temp=='-'){
        fputs("The first value has to be strictly greater than 0.\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

    if(shift<4 || shift>64){
        fputs("The first has to be strictly greater than 3 and strictly lower than 65.\n",output);
        fclose(input);
        fclose(output);
        return 0;
    }

    long long upper = 1LL;
	upper<<=(shift-1);
    upper--;
    long long lower = ~upper;

	long long first = 0LL;
	int negative1 = 1;
    	int state = 0;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
        state = 1;
        if(temp=='-')
			negative1 = 0;
		else
			first = first*10 + (temp-'0');
	}
		
	if((temp=='E' || temp==EOF) && state==0){
        	fprintf(output,"min: %lld\t0x%.16llx\n",lower,lower);
        	fprintf(output,"max: %lld\t0x%.16llx\n",upper,upper);
		fclose(input);
		fclose(output);
		return 0;
	}

	if (temp=='E' || temp==EOF){
        	fputs("Input file should contains 1 or 3 values exactly.\n",output);
        	fclose(output);
        	fclose(input);
        	return 0;
    	}

    	if(negative1==0)
        	first = -first;

	long long second = 0LL;
    	int negative2 = 1;
	while((temp=fgetc(input))!='E' && temp!='\n' && temp!=EOF){
        if(temp=='-')
            negative2 = 0;
        else
		    second = second*10 + (temp-'0');
    	}

    	if(negative2==0)
        	second = -second;

    	int enfin = mainFunction(shift,first,negative1,second,negative2);

    	if(enfin==-1)
        	fprintf(output,"%lld\n",lower);
    	if(enfin==0)    
        	fprintf(output,"%lld\n",(first*second));
    	if(enfin==1)
		fprintf(output,"%lld\n",upper);
	fclose(input);
	fclose(output);
	return 0;
}
