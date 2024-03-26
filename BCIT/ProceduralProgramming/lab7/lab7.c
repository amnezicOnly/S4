#include <stdio.h>
#include <stdlib.h>

typedef struct Student{
	char* lastName;
	char* firstName;
	char* studentID;
	int midterm;
	int final;
	int average;
} Student;

void printText(char* text){
	size_t i =0;
	while(text[i]!='\0'){
		printf("%c",text[i]);
		i++;
	}
}

void printArray(Student* students, size_t size){
	printf("size: %zu\n", size);
	for(size_t i=0; i<size; i++){
		printf("(");
		printText(students[i].studentID);
		printf(")-->");
	}
	printf("NULL\n");
}

int getName(FILE* input, char** name, size_t i){
	char temp;
	while((temp=fgetc(input))!=' '){
		if(!((temp>=65 && temp<=90)||(temp>=97 && temp<=122)))
			return 1;
		if(i==0){
			*name = malloc(sizeof(char));
			if((*name)==NULL)
				perror("Impossible de créer le name\n");
		}
		else{
			*name = realloc(*name,i*sizeof(char));
			if((*name)==NULL)
				perror("Impossible d'agrandir le name\n");
		}
		i++;
		(*name)[i-1] = temp;
	}
	return 0;
}

int getID(FILE* input, char** ID){
	char temp = fgetc(input);
	if(temp!='A')
		return 1;
	*ID = malloc(8*sizeof(char));
	(*ID)[0]=temp;
	short i = 1;
	while((temp=fgetc(input))!=' '){
		if(!((temp>='0' && temp<='9')||i>=8)){
			return -1;
		}
		(*ID)[i] = temp;
		i++;
	}
	return 0;
}

int getNum(FILE* input){
	char temp;
	int res = 0;
	while((temp=fgetc(input))!=' '){
		if(temp<'0' || temp>'9')
			return -1;
		res*=10;
		res+=temp-'0';
	}	
	return res;
}

int getFinal(FILE* input){
	char temp;
	int res = 0;
	while((temp=fgetc(input))!='\n'){
		if(temp<'0' || temp>'9' || res>100)
			return -1;
		res*=10;
		res+=temp-'0';
	}	
	return res;
}

int sortedName(char* name1, char* name2){
	size_t i =0;
	while(name1[i]!='\0' && name2[i]!='\0' && name1[i]==name2[i])
		i++;
	if(name1[i]=='\0' && name2[i]=='\0')
		return 0;
	if(name1[i]=='\0' && name2[i]!='\0')
		return 1;
	if(name1[i]!='\0' && name2[i]=='\0')
		return -1;
	if(name1[i]<name2[i])
		return 1;
	else
		return -1;
}

int addInList(Student** students, size_t* size, Student student){
	for(size_t i = 0; i<*(size); i++){
		if(sortedName(students[i]->studentID,student.studentID)==0){
			return -1;
		}		
	}
	if(*size == 1)
		*students = malloc(sizeof(Student));
	else
		*students = realloc(*students,((*size)+1)*sizeof(Student));
	if(*students==NULL)
		perror("Problème d'alloc de students\n");
	(*students)[(*size)] = student;
	(*size)++;
}

int fillData(FILE* input, Student* students, size_t* size){
	// à chaque ligne, le programme va récupérer les noms avec getName et les numéros avec getNum
	// puis il va les rajouter dans la liste students avec la fonction addInList
	char temp;
	char temp2;
	int i = 1;
	while((temp=fgetc(input))!='E' && ((temp2=fgetc(input))!='\n')){
		printf("i: %d\n",i);
		char* lastName = malloc(sizeof(char));
		if(lastName==NULL)
			perror("Impossible de créer un nouveau lastName dans fillData\n");
		if(!((temp>='a' && temp<='z')||(temp>='A'&&temp<='Z')))
			return -1;
		lastName[0] = temp;
		if(!((temp2>='a' && temp2<='z')||(temp2>='A'&&temp2<='Z')||(temp2!=' '))){
			return -1;
		}
		if(temp2!=' '){
			lastName = realloc(lastName,2*sizeof(char));
			lastName[1] = temp2;
		}
		char* firstName = NULL;
		char* studentID;
		int midterm;
		int final;

		if(getName(input,&lastName,2)!=0)
			return -1;
		if(getName(input,&firstName,0)!=0)
			return -1;
		int studentIDcheck = getID(input,&studentID);
		if(studentIDcheck==-1)
			return -1;
		midterm = getNum(input);
		if(midterm<0 || midterm>100)
			return -1;
		final = getFinal(input);
		if(final<0 || final>100)
			return -1;
		Student student = {lastName,firstName,studentID,midterm,final,(midterm+final)/2};
		if(addInList(&students,size,student)==-1)	// erreur ici
			return -1;
		i++;
	}
	//printf("i: %d\n",i);
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

	int filtre = fgetc(input)-'0';
	char temp = fgetc(input);
	if(filtre<0 || filtre>5 || temp==EOF){
		fputs("Error\n",output);
		fclose(output);
		fclose(input);
	}

	// création d'une liste d'objets Student
	Student* students = NULL;
	size_t size = 0;
	// Remplis la liste avec toutes les infos
	int status = fillData(input,students,&size);
	printf("status: %d, size: %zu\n",status,size);

	//printf("Here it's ok\n");
	if(status==1){
		perror("Rentre dans status==1\n");
		free(students);
		fclose(input);
		fputs("Error\n",output);
		fclose(output);
		return 0;
	}

	printArray(students,size);
	free(students);
	fclose(input);
	fclose(output);
    	return 0;
}
