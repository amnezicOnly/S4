#include<stdio.h>
// À PEUT ÊTRE ENLEVER
#include<stdlib.h>

typedef struct Student{
	char* firstName;
	char* lastName;
	char* ID;
	int midterm;
	int final;
} Student;

int line = 1;

void listStudents(FILE* output, Student* students, size_t size){
	for(size_t i=0; i<size; i++)
		fprintf(output,"%s %s %s %d %d\n",students[i].lastName,students[i].firstName,students[i].ID,students[i].midterm,students[i].final);
}

void freeStudents(Student* students, size_t size){
	for(size_t i = 0; i<size; i++){
		free(students[i].firstName);
		free(students[i].lastName);
		free(students[i].ID);
	}
	free(students);
}

int getName(FILE* input, char** name, size_t* size,int type){
	char temp;
	//printf("Type: %d\n",type);
	while(!((temp=fgetc(input))==' ' || temp=='\n' || temp==EOF)){
		printf("%c",temp);
		if((*size)==0)
			*name = malloc(sizeof(char));
		else
			*name = realloc(*name,((*size)+1)*sizeof(char));
		if(*name==NULL){
			printf("Erreur 1\n");
			return -1;
		}
		if(type==0){
			if(!((temp>='a' && temp<='z')||(temp>='A' && temp<='Z'))){
				printf("Erreur 2\n");
				return -1;
			}
		}
		if(type==1){
			if(temp==' ')
				break;
			if((*size)==0 && temp!='A'){
				printf("Erreur 3\n");
				return -1;
			}
			if((*size)!=0 && (temp<'0' || temp>'9')){
				printf("Erreur 4\n");
				return -1;
			}
		}
		(*name)[(*size)] = temp;
		(*size)++;
	}
	printf("\n");
	if(temp!=' ' || (type==1 && (*size)!=8)){
		printf("Erreur 5\n");
		return -1;
	}
	return 0;
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

int getGrade(FILE* input, int type){
	char temp;
	int res = 0;
	while((temp=fgetc(input))!='\n' && temp!=' '){
		//printf("res: %d, temp: %c\n",res,temp);
		if(temp<'0' || temp>'9' || temp>100)
			return -1;
		res*=10;
		res+=(temp-'0');
	}
	//printf("res: %d\n",res);
	if((type==0 && temp!=' ')||(type==1 && temp!='\n'))
		return -1;
	return res;
}

int addToList(Student** students, size_t* size, char* FirstName, char* LastName, char* id, int Midterm, int Final){
	//printf("Average: %d\n",(Midterm+Final)/2);
	/*for(size_t i=0; i<(*size); i++){
		if(sortNames((*students)[i].ID,id)==0)
			return 0;
	}*/
	
	if((*size)==0){
		*students = (Student*)malloc(sizeof(Student));
		if(students==NULL)
			return -1;
	}
	else{
		Student* temp = (Student*)realloc(*students, (*size + 1) * sizeof(Student));
		if(temp==NULL)
			return -1;
		*students = temp;
	}
		
		
	Student* newStudent = (Student*)malloc(sizeof(Student));
	if(newStudent==NULL){
		printf("Erreur lors du malloc de newStudent\n");
		return -1;
	}
	
	newStudent->ID = id;
    	newStudent->firstName = FirstName;
    	newStudent->lastName = LastName;
    	newStudent->midterm = Midterm;
    	newStudent->final = Final;
    	
    	(*students)[*size] = *newStudent;
    	(*size)++;
    	
    	
    	/*
    	last name > first name > student number > midterm grade > final grade
    	*/
    	size_t i = (*size)-1;
    	// sorting on lastName
    	while(i>0 && sortNames((*students)[i].lastName, (*students)[i-1].lastName)>0){
		Student temp = (*students)[i];
		(*students)[i] = (*students)[i-1];
	    	(*students)[i-1] = temp;
	    	i--;
	}
	// sorting on firstName
	while(i>0 && (sortNames((*students)[i].lastName, (*students)[i-1].lastName)==0 && sortNames((*students)[i].firstName, (*students)[i-1].firstName)>0)){
		Student temp = (*students)[i];
		(*students)[i] = (*students)[i-1];
	    	(*students)[i-1] = temp;
	    	i--;
	}
	// sorting on student number
	while(i>0 && (sortNames((*students)[i].lastName, (*students)[i-1].lastName)==0 && sortNames((*students)[i].firstName, (*students)[i-1].firstName)==0) && (sortNames((*students)[i].ID, (*students)[i-1].ID))>0){
		Student temp = (*students)[i];
		(*students)[i] = (*students)[i-1];
	    	(*students)[i-1] = temp;
	    	i--;
	}
	// sorting midterm grade
	while(i>0 && (sortNames((*students)[i].lastName, (*students)[i-1].lastName)==0 && sortNames((*students)[i].firstName, (*students)[i-1].firstName)==0) && (sortNames((*students)[i].ID, (*students)[i-1].ID))==0 && (*students)[i-1].midterm>(*students)[i].midterm){
		Student temp = (*students)[i];
		(*students)[i] = (*students)[i-1];
	    	(*students)[i-1] = temp;
	    	i--;
	}
	// sorting on final grade
	while(i>0 && (sortNames((*students)[i].lastName, (*students)[i-1].lastName)==0 && sortNames((*students)[i].firstName, (*students)[i-1].firstName)==0) && (sortNames((*students)[i].ID, (*students)[i-1].ID))==0 && (*students)[i-1].midterm==(*students)[i].midterm && (*students)[i-1].final>(*students)[i].final){
		Student temp = (*students)[i];
		(*students)[i] = (*students)[i-1];
	    	(*students)[i-1] = temp;
	    	i--;
	}
	
    	free(newStudent);
    	return 1;
}

int catchData(FILE* input, Student** students, size_t* size, int filter){
	char temp;
	char temp2;
	int i = 1;
	//printf("Rentre dans catchData\n");
	while(!(((temp=fgetc(input)=='E')&&((temp2=fgetc(input))==EOF)))){
		//printf("Rentre dans la boucle de catchData\n");
		char* lastName = malloc(2*sizeof(char));
		lastName[0] = temp;
		lastName[1] = temp2;
		size_t size2 = 2;
		int nameStatus = getName(input,&lastName,&size2,0);
		if(nameStatus==-1){
			printf("Error in getName0\n");
			return -1;
		}
		
		char* firstName = NULL;
		size2 = 0;
		nameStatus = getName(input,&firstName,&size2,0);
		if(nameStatus==-1){
			printf("Error in getName0\n");
			return -1;
		}
		
		size2 = 0;
		char* id = NULL;
		int idStatus = getName(input,&id,&size2,1);
		if(idStatus==-1){
			printf("Error in getName1\n");
			return -1;
		}
		
		int midterm = getGrade(input,0);
		if(midterm<0){
			printf("Error in getGrade0\n");
			return -1;
		}
		
		int final = getGrade(input,1);
		if(final<0){
			printf("Error in getGrade1\n");
			return -1;
		}
		//printf("Ligne %d: Average: %d\n",i,(midterm+final)/2);
		//printf("Filter value: %d\n",filter);
		int average = (midterm+final)/2;
		if(filter==1 && average>=90){
			//printf("Filter 1\n");
			int addStatus = addToList(students, size, firstName, lastName, id, midterm, final);
			if(addStatus==-1){
				printf("Error here1\n");
				return -1;
			}
		}
		else if(filter==2 && (average<90 && average>=80)){
			//printf("Filter 2\n");
			int addStatus = addToList(students, size, firstName, lastName, id, midterm, final);
			if(addStatus==-1){
				printf("Error here2\n");
				return -1;
			}
		}
		else if(filter==3 && (average<80 && average>=70)){
			//printf("Filter 3\n");
			int addStatus = addToList(students, size, firstName, lastName, id, midterm, final);
			if(addStatus==-1){
				printf("Error here3\n");
				return -1;
			}
		}else if(filter==4 && (average<70 && average>=60)){
			//printf("Filter 4\n");
			int addStatus = addToList(students, size, firstName, lastName, id, midterm, final);
			if(addStatus==-1){
				printf("Error here4\n");
				return -1;
			}
		}else if(filter==5 && average<60){
			//printf("Filter 5\n");
			int addStatus = addToList(students, size, firstName, lastName, id, midterm, final);
			if(addStatus==-1){
				printf("Error here5\n");
				return -1;
			}
		}
		i++;
	}
	if(temp!='E'){
		printf("Error here too\n");
		return -1;
	}
	printf("Temp: %c, Temp2: %c\n",temp,temp2);
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
		
	int filter = fgetc(input)-'0';
	//printf("Filter: %d\n",filter);
	if(filter<=0 || filter>5){
		fputs("Error in input.txt file.\n",output);
		fclose(input);
		fclose(output);
		return 1;
	}
	fgetc(input);

	Student* students = NULL;
	size_t size = 0;
	
	//printf("Avant catchData\n");
	//printf("Filter: %d\n",filter);
	int processStatus = catchData(input,&students,&size,filter);
	//printf("Après catchData\n");

	if(processStatus==-1 || size==0){
		fputs("Error in input.txt file.\n",output);
		fclose(input);
		fclose(output);
		freeStudents(students,size);
		return 1;
	}
	
	listStudents(output,students,size);
	fclose(input);
	fclose(output);
	freeStudents(students,size);
	return 0;
}
