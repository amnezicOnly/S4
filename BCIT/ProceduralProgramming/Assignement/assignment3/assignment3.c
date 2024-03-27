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

int getID(FILE* input, int* ID){
	char temp;
	while((temp=fgetc(input))!=','){
		if(temp<'0' || temp>'9' || (*ID)>1000)
			return -1;
		(*ID)*=10;
		(*ID)+=(temp-'0');
	}
	if(temp!=',')
		return -1;
	return 0;
}

int getName(FILE* input, char** name){
	char temp;
	size_t i = 0;
	int state = 1;
	while((temp=fgetc(input))!=',' || temp==EOF){
		if(i==0)
			*name = malloc(sizeof(char));
		else
			*name = realloc(*name,(i+1)*sizeof(char));
		if(*name==NULL)
			return 0;
		if(temp==' ')
			state = 0;
		if(!((temp>='a' && temp<='z')||(temp>='A' && temp<='Z'))){
			if(temp!=' ')
				return -1;
		}
		(*name)[i] = temp;
		i++;
	}
	return (state==0 && temp==',');
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

int catchData(FILE* input, Employee** employees, size_t* size){
	char temp;
	while((temp=fgetc(input))!='E' && temp!=EOF){
		if(temp<'0' || temp>'9')
			return -1;
		int ID = temp-'0';
		int statusID = getID(input,&ID);
		if(statusID==-1){
			return -1;
		}		
		
		char* name = NULL;
		int nameStatus = getName(input,&name);
		line++;
		if(nameStatus!=1){
			return -1;
		}
			
		float salary = getSalary(input);
		if(salary<0){
			return -1;
		}
		
		int addStatus = addToList(employees, size, ID, name, salary);
		if(addStatus==-1){
			return -1;
		}	
	}
	if(temp!='E')
		return -1;
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
