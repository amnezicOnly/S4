#include<stdio.h>
// À PEUT ÊTRE ENLEVER
#include<stdlib.h>

typedef struct Employee{
	int ID;
	char* firstName;
	char* lastName;
	float salary;
} Employee;

void listEmployee(FILE* output, Employee* employees, size_t size){
	printf("size: %zu\n",size);
	for(size_t i=0; i<size; i++)
		printf("ID: %d\n",employees[i].ID);
}

int getID(FILE* input, int ID){
	char temp;
	while((temp=fgetc(input))!=','){
		if(temp<'0' || temp>'9' || ID>1000)
			return -1;
		ID*=10;
		ID+=(temp-'0');
	}
	if(temp!=',')
		return -1;
	return ID;
}

int getName(FILE* input, char** name, int type){
	char temp;
	size_t i = 0;
	while((temp=fgetc(input))!=' ' && temp!=','){
		if(i==0)
			*name = malloc(sizeof(char));
		else
			*name = realloc(*name,(i+1)*sizeof(char));
		if(*name==NULL)
			perror("Impossible de créer ou d'agrandir le nom dans getName\n");
		(*name)[i] = temp;
		i++;
	}
	return ((type==0 && temp!=' ') || (type==1 && temp!=','));
}

int sortNames(char* name1, char* name2){
	size_t i = 0;
	while(name1[i]!='\0' && name2[i]!='\0' && name1[i]==name2[i])
		i++;
	
	if(name1[i]=='\0' && name2[i]!='\0')
		return 1;
	if(name1[i]!='\0' && name2[i]=='\0')
		return -1;
	if(name1[i]=='\0' && name2[i]=='\0')
		return 0;
	if(name1[i]!='\0' && name2[i]!='\0' && name1[i]<name2[i])
		return 1;
	else
		return -1;
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

int addToList(Employee** employees, size_t* size, int ID, char* firstName, char* lastName, float salary){
	for(size_t i=0; i<(*size); i++){
		if((*employees)[i].ID==ID)
			return -1;
	}
	
	if((*size)==0)
		*employees = malloc(sizeof(Employee));
	else
		*employees = realloc((*employees),((*size)+1)*sizeof(Employee));
	if(*employees==NULL)
		perror("Impossible d'ajouter un nouvel employé.\n");
	(*employees)[(*size)].ID = ID;
	(*employees)[(*size)].firstName = firstName;
	(*employees)[(*size)].lastName = lastName;
	(*employees)[(*size)].salary = salary;
	(*size)++;
	
	size_t i = (*size)-1;
	while(i>0 && sortNames((*employees)[i].firstName,(*employees)[i-1].firstName)){
		i--;
	}
}

int catchData(FILE* input, Employee* employees, size_t* size){
	char temp;
	int i = 1;
	while((temp=fgetc(input))!='E' && temp!=EOF){
		//printf("Début traitement ligne %d\n",i);
		int ID = temp-'0';
		ID = getID(input,ID);
		if(ID<0){
			printf("Erreur getID.\n");
			return -1;
		}			
		
		char* firstName = NULL;
		int firstNameStatus = getName(input,&firstName,0);
		if(firstNameStatus==-1){
			printf("Erreur getName 0.\n");
			return -1;
		}
		
		char* lastName = NULL;
		int lastNameStatus = getName(input,&lastName,1);
		if(lastNameStatus==-1){
			printf("Erreur getName1.\n");
			return -1;
		}
			
		float salary = getSalary(input);
		if(salary<0){
			printf("Erreur getSalary.\n");
			return -1;
		}
		
		//Employee employee = {ID,firstName,lastName,salary};
		int addStatus = addToList(&employees, size, ID, firstName, lastName, salary);
		if(addStatus==-1){
			printf("Erreur addToList.\n");
			return -1;
		}
		//printf("Fin traitement ligne %d\n",i);
		//printf("%d,%s %s, %.2f\n",employees[i-1].ID, employees[i-1].firstName, employees[i-1].lastName, employees[i-1].salary);
		return 0;		
	}
}


int main(){
	FILE* input = fopen("input.txt","r");
	if(input==NULL)
		perror("Unable to open input.txt.\n");
	
	FILE* output = fopen("output.txt","w");
	if(output==NULL)
		perror("Unable to open output.txt.\n");
		
	Employee* employees = NULL;
	size_t size = 0;
	
	int processStatus = catchData(input,employees,&size);
	if(processStatus==-1){
		fputs("Error in input.txt file.\n",output);
		fclose(input);
		fclose(output);
		free(employees);
		return 0;
	}
	
	printf("size: %zu\n",size);
	
	listEmployee(output,employees,size);
	fclose(input);
	fclose(output);
	free(employees);
	return 0;
}
