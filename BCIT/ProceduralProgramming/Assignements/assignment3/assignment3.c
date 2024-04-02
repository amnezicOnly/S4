#include<stdio.h>
// À PEUT ÊTRE ENLEVER
#include<stdlib.h>
#include<string.h>

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
	free(employees);
}

int getID(char id[]){
	int res = 0;
	for(size_t i = 0; id[i]!='\0'; i++){
		if(id[i]<'0' || id[i]>'9')
			return -1;
		res*=10;
		res+=id[i]-'0';
	}
	return res;
}

int checkName(char name[]){
	int state = 0;	
	for(size_t i = 0; name[i]!='\0' ; i++){
		if(!((name[i]>='a' && name[i]<='z')||(name[i]>='A' && name[i]<='Z')) && state!=0)
			return -1;
		if(name[i]==' ')
			state++;
	}
	if(state!=1)
		return -1;
	return 0;
}

float getSalary(char salary[]){
	int res = 0;
	int state = 0;
	for(size_t i = 0; salary[i]!='\0'; i++){
		if((salary[i]<'0' || salary[i]>'9') && state!=0)
			return -1;
		if(salary[i]=='.')
			state++;
		else{
			res*=10;
			res+=salary[i]-'0';
		}
	}
	res = (float)res;
	res/=100;
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

int addToList(Employee** employees, size_t* size, int id, char Name[], float Salary){
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
	char* newName = (char*)malloc(strlen(Name) + 1);
	if(newName == NULL)
        	return -1;
    	strcpy(newName, Name);
	
	newEmployee->ID = id;
    	newEmployee->name = newName;
    	newEmployee->salary = Salary;
    	
    	(*employees)[*size] = *newEmployee;
    	(*size)++;
    	
    	size_t i = (*size)-1;
    	while(i>0 && sortNames(((*employees)[i]).name, ((*employees)[i-1]).name)>0){
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
    	 return 0;
}

int catchData(FILE* input, Employee** employees, size_t* size){
	char ligne[100];
	int state = 0;
	while (fgets(ligne, sizeof(ligne), input) != NULL){
		if(ligne[0]=='E' && ligne[1]=='\n' && strlen(ligne)==2){
			state++;
			break;
		}
		char id[50], name[50], salary[50];
		sscanf(ligne, "%[^,],%[^,],%s", id, name, salary);
		
		int ID = getID(id);
		if(ID<0)
			return -1;
		
		int nameCheck = checkName(name);
		if(nameCheck<0)
			return -1;
		
		float salaire = getSalary(salary);
		if(salaire<0)
			return -1;
			
		int addStatus = addToList(employees, size, ID, name, salaire);
		if(addStatus<0)
			return -1;
		
	}
	return state;
}


int main(int argc, char** argv){
	if(argc!=3)
		return 1;
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		return 1;
	
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		return 1;
		
	Employee* employees = NULL;
	size_t size = 0;
	
	int processStatus = catchData(input,&employees,&size);
	if(processStatus<0 || size==0){
		fputs("Error\n",output);
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
