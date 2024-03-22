#include <stdio.h>
// À PEUT ÊTRE ENLEVER
#include <stdlib.h>

typedef struct Student{
	char* lastName;
	char* firstName;
	int studentID;
	int midterm;
	int final;
	int average;
} Student;

int getName(FILE* input, char** name){
	return 0;
}

int getNum(FILE* file){
	
	return -1;
}

int addInList(Student* students, size_t* size, Student student){
	for(size_t i = 0; i<*(size); i++){
		if(students[i].studentID==student.studentID)
			return 1;		
	}
	*(size)++;
	if(*size == 1)
		students = malloc(sizeof(Student));
	else
		students = realloc(students,*(size)*sizeof(Student));

	
}


int fillData(FILE* input, Student* students, size_t* size){
	// à chaque ligne, le programme va récupérer les noms avec getName et les numéros avec getNum
	// puis il va les rajouter dans la liste students avec la fonction addInList
	char temp;
	char* lastName;
	char* firstName;
	int studentID;
	int midterm;
	int final;
	while((temp=fgetc(input))!='E' && temp!='EOF'){
		if(getName(input,lastName)!=0)
			return -1;
		if(getName(input,firstName)!=0)
			return -1;
		studentID = getNum(input);
		if(studentID==-1)
			return -1;
		midterm = getNum(input);
		if(midterm==-1)
			return -1;
		final = getNum(file);
		if(final==-1)
			return -1;
		Student student = {lastName,firstName,studentID,midterm,final,(midterm+final)/2};
		if(addInList(students,&size,student)==-1)
			return -1;
	}
	// Si pas de problème
	return 0;	
}

int main(){
	// ouverture des fichiers
	FILE* input = fopen("input.txt","r");
	if(input==NULL){
		perror("Unable to read the input file.\n");
		return 0;
	}

	FILE* output = fopen("output.txt","w");
	if(output==NULL){
		perror("Unable to open output.txt.\n");
		return 0;
	}

	int filtre = fgtec(input)-'0';
	char temp = fgetc(input);
	if(filtre<0 || filtre>5 || temp!='\n'){
		fputs("Error\n",output);
		fclose(output);
		fclose(input);
	}

	// création d'une liste d'objets Student
	Student* students = NULL;
	size_t size = 0;

	// Remplis la liste avec toutes les infos
	int status = fillData(input,students,&size);

	if(status==1){
		free(students);
		fclose(input);
		fputs("Error\n",output);
		fclose(output);
		return 0;
	}


    	return 0;
}
