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

int addToList(Employee** employees, size_t* size, int id, char* Name, float Salary, FILE* output){
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
    	
    	//listEmployees(output,*employees,(*size));
    	
    	
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

int catchData(FILE* input, FILE* output, Employee** employees, size_t* size){
	char temp;
	while((temp = fgetc(input))!='E' && temp!=EOF){
		//printf("%c\n",temp);
		if(temp<'0' || temp>'9'){
			printf("Erreur 1\n");
			return -1;
		}
		
		int ID = temp-'0';
		while((temp = fgetc(input))!=',' && temp!='\n' && temp!=EOF){
			if(temp<'0' || temp>'9'){
				printf("Erreur 2\n");
				return -1;
			}
			ID*=10;
			ID+=temp-'0';
		}
		if(temp!=','){
			printf("Erreur 3\n");
			return -1;
		}
		
		temp = fgetc(input);
		printf("%c(%d)\n",temp,temp);
		if(!((temp>='a' && temp<='z')||(temp>='A' && temp<='Z'))){
			printf("Erreur 4\n");
			return -1;
		}
		size_t sizeName = 0;
		char* name = malloc(sizeName*sizeof(char));
		if(name==NULL){
			printf("Erreur 5\n");
			return -1;
		}
		name[sizeName] = temp;
		sizeName++;
		int state = 0;
		while((temp = fgetc(input))!=',' && temp!='\n' && temp!=EOF){
			printf("%c(%d)\n",temp,temp);
			if(temp==' ')
				state++;
			if(((temp>='a' && temp<='z')||(temp>='A' && temp<='Z')) || (temp==' ' && state==1)){
				name[sizeName] = temp;
				sizeName++;
			}
			else{
				printf("Erreur 7\n");
				return -1;
			}
		}
		if(temp!=',' || state!=1){
			printf("Erreur 8\n");
			return -1;
		}
		
		int salary = 0;
		state = 0;
		while((temp = fgetc(input))!='\n' && temp!=EOF){
			if(temp=='.'){
				if(state==0)
					state++;
				else{
					printf("Erreur 9\n");
					return -1;
				}
			}
			else if(temp>='0' && temp<='9'){
				salary*=10;
				salary+=temp-'0';
			}
			else{
				printf("Erreur 10\n");
				return -1;
			}
		}
		
		salary = (float)salary;
		salary/=100;
		
		int checkAdd = addToList(employees, size, ID, name, salary, output);
    		if(checkAdd!=0){
    			printf("Erreur 11\n");
    			return -1;
    		}
	}
	
	
   


	/*
	char temp0[50];
    	char temp1[50];
    	char temp2[50];
    	char line[100];
    	//int i = 2;

    	while (fgets(line, sizeof(line), input)){
    		if(strcmp(line, "E\n") == 0)
    			return 0;
    		sscanf(line, "%49[^,],%49[^,],%49s", temp0, temp1, temp2);
    		//printf("ID: %s, Name: %s, Salary: %s\n",temp0,temp1,temp2);
    		
    		// ID
    		//printf("cID: %s\n",temp0);
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
    		strcpy(cID, temp0);
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
    		strcpy(name, temp1);
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
    		
    		//printf("ID: %d\n",ID);
    		
    		int checkAdd = addToList(employees, size, ID, name, salary);
    		if(checkAdd!=0){
    			printf("Erreur 10\n");
    			return -1;
    		}
	}*/
	if(temp!='E')
		return -1;
	return 0;
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
	
	int processStatus = catchData(input,output,&employees,&size);
	//printf("processStatus: %d, size: %zu\n",processStatus, size);
	if(processStatus==-1 || size==0){
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
