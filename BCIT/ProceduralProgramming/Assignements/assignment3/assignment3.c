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
	for(size_t i = 0; i<size; i++)
		free(employees[i].name);
	free(employees);
}

int verifyName(char* name, size_t size){
	int state = 0;
	for(size_t i=0; i<size ; i++){
		if(name[i]==' '){
			if(state==0)
				state++;
			else{
				printf("Erreur 6.1\n");
				return -1;
			}
		}
		else if(!((name[i]>='a' && name[i]<='z')||(name[i]>='A' && name[i]<='Z'))){
				printf("Erreur 6.2, temp: %d\n",name[i]);
				return -1;
		}
	}
	return 0;
}

int getID(char* id, size_t size){
	int res = 0;
	for(size_t i=0; i<size; i++){
		if(id[i]<'0' || id[i]>'9')
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

int getSalary(char* salary, size_t size){
	int res = 0;
	int state = 0;
	for(size_t i=0; i<size; i++){
		if(salary[i]>='0' && salary[i]<='9'){
			res*=10;
			res+=(salary[i]-'0');
		}
		if(salary[i]=='.'){
			if(state!=0)
				return -1;
			state++;
		}
	}
	return res;
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
	char temp0[50];
    	char temp1[50];
    	char temp2[50];
    	char line[100];
    	//int i = 2;

    	while (fgets(line, sizeof(line), input)){
    		if(strcmp(line, "E\n") == 0)
    			return 0;
    		sscanf(line, "%49[^,],%49[^,],%49s", temp0, temp1, temp2);
    		printf("ID: %s  Name: %s  Salary: %s\n",temp0,temp1,temp2);
    		
    		// ID
    		int sizeID = strlen(temp0)+1;
    		if(sizeID!=4){
    			printf("Erreur 1\n");
    			return -1;
    		}
    		char* cID = malloc(sizeID);
    		if(cID==NULL){
    			printf("Erreur 2\n");
    			return -1;
    		}
    		strcpy(cID, temp2);
    		int ID = getID(cID,sizeID-1);
    		if(ID<0){
    			printf("Erreur 3\n");
    			return -1;
    		}
    		
    		//name
    		int sizeName = strlen(temp1)+1;
    		if(sizeName==0){
    			printf("Erreur 4\n");
    			return -1;
    		}
    		char* name = malloc(sizeName);
    		if(name==NULL){
    			printf("Erreur 5\n");
    			return -1;
    		}
    		strcpy(name, temp0);
    		int nameStatus = verifyName(name, sizeName-1);
    		if(nameStatus!=0){
    			printf("Erreur 6\n");
    			return -1;
    		}
    		
    		// salary
    		int sizeSalary = strlen(temp2)+1;
    		if(sizeSalary==1){
    			printf("Erreur 7\n");
    			return -1;
    		}
    		char* cSalary = malloc(sizeSalary);
    		if(cSalary==NULL){
    			printf("Erreur 8\n");
    			return -1;
    		}
    		strcpy(cSalary, temp2);
    		int salary = getSalary(cSalary,sizeSalary-1);
    		if(salary<0){
    			printf("Erreur 9\n");
    			return -1;
    		}
    		salary = (float)salary;
    		salary/=100;
    		
    		int checkAdd = addToList(employees, size, ID, name, salary);
    		if(checkAdd!=0){
    			printf("Erreur 10\n");
    			return -1;
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
