#include<stdio.h>
// À PEUT ÊTRE ENLEVER
#include<stdlib.h>
#include <string.h>

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
	for(size_t i=0; i<size; i++){
		free(students[i].lastName);
		free(students[i].firstName);
		free(students[i].ID);
	}
	free(students);
}

int verifyName(char* name, size_t size, int type){
	if(type==0){
		for(size_t i=0; i<size; i++){
			if(!((name[i]>='a' && name[i]<='z')||(name[i]>='A' && name[i]<='Z')))
				return -1;
		}
	}
	if(type==1){
		if(name[0]!='A')
			return -1;
		for(size_t i=1; i<size; i++){
			if(name[i]<'0' || name[i]>'9')
				return -1;
		}
	}
	return 0;
}

int getGrade(char text[], size_t size){
	int res = 0;
	for(size_t i=0; i<size; i++){
		if(text[i]<'0' || text[i]>'9' || res>100)
			return -1;
		res*=10;
		res+=text[i]-'0';
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

int addToList(Student** students, size_t* size, char* FirstName, char* LastName, char* id, int Midterm, int Final){	
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
		return -1;
	}
	newStudent->lastName = LastName;
	newStudent->firstName = FirstName;
	newStudent->ID = id;
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
	char temp0[50];
    	char temp1[50];
    	char temp2[50];
    	char temp3[50];
   	char temp4[50];
    	char line[100];
    	//int i = 2;

    	while (fgets(line, sizeof(line), input)){
    		if(strcmp(line, "E\n") == 0)
    			return 0;
    		sscanf(line, "%s %s %s %s %s", temp0, temp1, temp2, temp3, temp4);
    		
    		// last name
    		int sizeLast = strlen(temp0)+1;
    		if(sizeLast==0){
    			return -1;
    		}
    		char* lastName = malloc(sizeLast);
    		if(lastName==NULL){
    			return -1;
    		}
    		strcpy(lastName, temp0);
    		int nameStatus = verifyName(lastName, sizeLast-1, 0);
    		if(nameStatus!=0){
    			return -1;
    		}
    		
    		// first name
    		int sizeFirst = strlen(temp1)+1;
    		if(sizeFirst==0){
    			return -1;
    		}
    		char* firstName = malloc(sizeFirst);
    		if(firstName==NULL){
    			return -1;
    		}
    		strcpy(firstName, temp1);
    		nameStatus = verifyName(firstName, sizeFirst-1, 0);
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
	if(argc!=3)
		return 1;
	
	FILE* input = fopen(argv[1],"r");
	if(input==NULL)
		return 1;
	
	FILE* output = fopen(argv[2],"w");
	if(output==NULL)
		return 1;
		
	int filter = fgetc(input)-'0';
	if(!(filter>=1 && filter<=5)){
		fputs("Error\n",output);
		fclose(input);
		fclose(output);
		return 1;
	}
	fgetc(input);

	Student* students = NULL;
	size_t size = 0;
	
	int processStatus = catchData(input,&students,&size,filter);

	if(processStatus==-1 || size==0){
		fputs("Error\n",output);
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
