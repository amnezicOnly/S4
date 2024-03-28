#include<stdio.h>
// À PEUT ÊTRE ENLEVER
#include<stdlib.h>

typedef struct Employee{
	int ID;
	char* name;
	float salary;
} Employee;

int line = 1;

void listEmployees(FILE* output, Employee* employees, size_t size){
	for(size_t i=0; i<size; i++)
		fprintf(output,"%d,%s,%.2f\n",employees[i].ID,employees[i].name,employees[i].salary);
}

void freeEmployees(Employee* employees, size_t size){
	for(size_t i = 0; i<size; i++)
		free(employees[i].name);
	free(employees);
}

int checkName(char* name, size_t size){
	int state = 0;
	for(size_t i=0; i<size ; i++){
		if(name[i]==' '){
			if(state==0)
				state++;
			else
				return -1;
		}
		else if(!((name[i]>='a' && name[i]<='z')||(name[i]>='A' && name[i]<='Z'))){
			return -1;
		}
	}
	return 0;
}

int getNumber(char* id, size_t size){
	int res = 0;
	for(size_t i=0; i<size; i++){
		if((id[i]<'0' || id[i]>'9') || ())
			return -1;
		res*=10;
		res+=(id[i]-'0');
	}
	return res;
}

int sortNames(char* name1, char* name2){
	size_t i = 0;
	while(name1[i]!='\0' && name2[i]!='\0' && name1[i]==name2[i])
		i++;
	
	if(name1[i]=='\0' && name2[i]=='\0')
		return 0;
	if(name1[i]=='\0' && name2[i]!='\0')
		return 1;
	if(name1[i]!='\0' && name2[i]=='\0')
		return -1;
	
	else{
		if(name1[i]<name2[i])
			return 1;
		return -1;
	}
}

float getSalary(FILE* input){
	char temp;
	float res = 0;
	while((temp=fgetc(input))!='.'){
		if(temp<'0' || temp>'9')
			return -1;
		res*=10;
		res+=(temp-'0');
	}
	while((temp=fgetc(input))!='\n'){
		if(temp<'0' || temp>'9')
			return -1;
		res*=10;
		res+=(temp-'0');
	}
	return res/100;
}

int addToList(Employee** employees, size_t* size, int id, char* Name, float Salary){
	for(size_t i=0; i<(*size); i++){
		if((*employees)[i].ID==id)
			return -1;
	}
	
	if((*size)==0){
		*employees = (Employee*)malloc(sizeof(Employee));
		if(employees==NULL)
			return -1;
	}
	else{
		Employee* temp = (Employee*)realloc(*employees, (*size + 1) * sizeof(Employee));
		if(temp==NULL)
			return -1;
		*employees = temp;
	}
		
		
	Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
	if(newEmployee==NULL)
		return -1;
	
	newEmployee->ID = id;
    	newEmployee->name = Name;
    	newEmployee->salary = Salary;
    	
    	(*employees)[*size] = *newEmployee;
    	(*size)++;
    	
    	
    	size_t i = (*size)-1;
    	while(i>0 && sortNames(((*employees)[i]).name, ((*employees)[i-1]).name)>=0){
		Employee temp = (*employees)[i];
		(*employees)[i] = (*employees)[i-1];
	    	(*employees)[i-1] = temp;
	    	i--;
	}
	while(i>0 && sortNames(((*employees)[i]).name, ((*employees)[i-1]).name)==0 && ((*employees)[i-1]).ID>((*employees)[i]).ID){
		Employee temp = (*employees)[i];
		(*employees)[i] = (*employees)[i-1];
	    	(*employees)[i-1] = temp;
	    	i--;
	}
    	free(newEmployee);    	
    	
    	 return 1;
}

int catchData(FILE* input, Student** students, size_t* size, int filter){
	char temp0[50];
    	char temp1[50];
    	char temp2[50];
    	char line[100];
    	//int i = 2;

    	while (fgets(line, sizeof(line), input)){
    		if(strcmp(line, "E\n") == 0)
    			return 0;
    		sscanf(line, "%s,%s,%s", temp0, temp1, temp2);
    		
    		//name
    		int sizeName = strlen(temp0)+1;
    		if(sizeName==0){
    			return -1;
    		}
    		char* name = malloc(sizeName);
    		if(name==NULL){
    			return -1;
    		}
    		strcpy(name, temp0);
    		int nameStatus = verifyName(name, sizeName-1, 0);
    		if(nameStatus!=0){
    			return -1;
    		}
    		
    		// ID
    		int sizeID = strlen(temp2)+1;
    		if(sizeID!=9){
    			return -1;
    		}
    		char* ID = malloc(sizeID);
    		if(ID==NULL){
    			return -1;
    		}
    		if(temp2[0]!='A'){
    			return -1;
    		}
    		strcpy(ID, temp2);
    		nameStatus = verifyName(ID, sizeID-1, 1);
    		if(nameStatus!=0){
    			return -1;
    		}
    		
    		// midterm
    		int sizeMidterm = strlen(temp3);
    		if(!(sizeMidterm==1 || sizeMidterm==2 || sizeMidterm==3)){
    			return -1;
    		}
    		int midterm = getGrade(temp3, sizeMidterm);
    		if(midterm<0 || midterm>100){
    			return -1;
    		}
    			
    		// final
    		int sizeFinal= strlen(temp4);
    		if(!(sizeFinal==1 || sizeFinal==2 || sizeFinal==3)){
    			return -1;
    		}
    		int final = getGrade(temp4, sizeFinal);
    		if(final<0 || final>100){
    			return -1;
    		}
    			
    		int average = (midterm+final)/2;
    		
		if(filter==1 && average>=90){
			int addStatus = addToList(students, size, firstName, lastName, ID, midterm, final);
			if(addStatus==-1){
				return -1;
			}
		}
		else if(filter==2 && (average>=80 && average<90)){
			int addStatus = addToList(students, size, firstName, lastName, ID, midterm, final);
			if(addStatus==-1){
				return -1;
			}
		}
		else if(filter==3 && (average>=70 && average<80)){
			int addStatus = addToList(students, size, firstName, lastName, ID, midterm, final);
			if(addStatus==-1){
				return -1;
			}
		}else if(filter==4 && (average>=60 && average<70)){
			int addStatus = addToList(students, size, firstName, lastName, ID, midterm, final);
			if(addStatus==-1){
				return -1;
			}
		}else if(filter==5 && average<60){
			int addStatus = addToList(students, size, firstName, lastName, ID, midterm, final);
			if(addStatus==-1){
				return -1;
			}
		}
	}
	return 0;
}


int main(int argc, char** argv){
	if(argc!=2)
		return 1;
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		return 1;
	
	FILE* output = fopen("output.txt","w");
	if(output==NULL)
		return 1;
		
	Employee* employees = NULL;
	size_t size = 0;
	
	int processStatus = catchData(input,&employees,&size);
	if(processStatus==-1 || size==0){
		fputs("Error in input.txt file.\n",output);
		fclose(input);
		fclose(output);
		free(employees);
		return 0;
	}
	
	listEmployees(output,employees,size);
	fclose(input);
	fclose(output);
	freeEmployees(employees,size);
	return 0;
}
