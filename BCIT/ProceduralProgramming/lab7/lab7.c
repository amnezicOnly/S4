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

void printArray(Student* students, size_t size){
	for(size_t i=0; i<size; i++)
		printf("(%d)-->",students[i].studentID);
	printf("NULL\n");
}

int getName(FILE* input, char** name){
	char temp;
	int i = 0;
	while((temp=fgetc(input))!=' '){
		if(!((temp>=65 && temp<=90)||(temp>=97 && temp<=122)))
			return 1;
		i++;
		if(*name==NULL)
			*name = malloc(sizeof(char));
		else
			*name = realloc(*name,i*sizeof(char));
		(*name)[i-1] = temp;
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
	int i = 0;
	while(name1[i]!='\0' && name2[i]!='\0'){
		if(name1[i]>name2[i])
			return 1;
		if(name1[i]<name2[i])
			return -1;
		i++;
	}
	
	if(name1[i]=='\0' && name2[i]!='\0')
		return -1;
	if(name2[i]=='\0' && name1[i]!='\0')
		return 1;
	
	return 0;
}

int addInList(Student** students, size_t* size, Student student){
	for(size_t i = 0; i<*(size); i++){
		if((*students)[i].studentID==student.studentID){
			printf("ID: %d, ",(*students)[i].studentID);
			return -1;
		}		
	}
	*(size)++;
	if(*size == 1)
		*students = malloc(sizeof(Student));
	else
		*students = realloc(*students,(*size)*sizeof(Student));
	if(*students==NULL)
		printf("Problème d'alloc de students\n");
	printf("Core dumped après ça\n");
	(*students)[(*size)-1] = student;
	int i = *(size)-1;
	// tri par nom de famille
	while(i>0 && sortedName((*students)[i-1].lastName,(*students)[i].lastName)==1){
		Student temp = (*students)[i-1];
		(*students)[i-1] = (*students)[i];
		(*students)[i] = temp;
		i--;
	}
	//tri par prénom
	while(i>0 && (sortedName((*students)[i-1].lastName,(*students)[i].lastName)==1||sortedName((*students)[i-1].lastName,(*students)[i].lastName)==0) && sortedName((*students)[i-1].firstName,(*students)[i].firstName)==1){
		Student temp = (*students)[i-1];
		(*students)[i-1] = (*students)[i];
		(*students)[i] = temp;
		i--;
	}
	// tri par studentID
	while(i>0 && (sortedName((*students)[i-1].lastName,(*students)[i].lastName)==1||sortedName((*students)[i-1].lastName,(*students)[i].lastName)==0) && (sortedName((*students)[i-1].firstName,(*students)[i].firstName)==1 || sortedName((*students)[i-1].firstName,(*students)[i].firstName)==0) && (*students)[i-1].studentID>(*students)[i].studentID){
		Student temp = (*students)[i-1];
		(*students)[i-1] = (*students)[i];
		(*students)[i] = temp;
		i--;
	}
	// tri par notes de midterm
	while(i>0 && (sortedName((*students)[i-1].lastName,(*students)[i].lastName)==1||sortedName((*students)[i-1].lastName,(*students)[i].lastName)==0) && (sortedName((*students)[i-1].firstName,(*students)[i].firstName)==1 || sortedName((*students)[i-1].firstName,(*students)[i].firstName)==0) && (*students)[i-1].studentID>(*students)[i].studentID && (*students)[i-1].midterm>(*students)[i].midterm){
		Student temp = (*students)[i-1];
		(*students)[i-1] = (*students)[i];
		(*students)[i] = temp;
		i--;
	}
	while(i>0 && (sortedName((*students)[i-1].lastName,(*students)[i].lastName)==1||sortedName((*students)[i-1].lastName,(*students)[i].lastName)==0) && (sortedName((*students)[i-1].firstName,(*students)[i].firstName)==1 || sortedName((*students)[i-1].firstName,(*students)[i].firstName)==0) && (*students)[i-1].studentID>(*students)[i].studentID && (*students)[i-1].midterm>=(*students)[i].midterm && (*students)[i-1].final>(*students)[i].final){
		Student temp = (*students)[i-1];
		(*students)[i-1] = (*students)[i];
		(*students)[i] = temp;
		i--;
	}
}


int fillData(FILE* input, Student* students, size_t* size){
	// à chaque ligne, le programme va récupérer les noms avec getName et les numéros avec getNum
	// puis il va les rajouter dans la liste students avec la fonction addInList
	char temp;
	int i = 0;
	printf("Test dans fillData avant la boucle while\n");
	while((temp=fgetc(input))!=EOF){
		char* lastName = NULL;
		char* firstName = NULL;
		int studentID;
		int midterm;
		int final;

		printf("Rentre dans la boucle while de fillData\n");
		if(getName(input,&lastName)!=0)
			return -1;
		printf("Last name: %s, ",lastName);
		if(getName(input,&firstName)!=0)
			return -1;
		printf("first name: %s, ",firstName);
		if(fgetc(input)!='A')
			return -1;
		studentID = getNum(input);
		printf("ID: A0%d, ",studentID);
		if(studentID==-1)
			return -1;
		midterm = getNum(input);
		printf("midterm: %d, ",midterm);
		if(midterm<0 || midterm>100)
			return -1;
		final = getFinal(input);
		printf("final: %d\n",final);
		if(final<0 || final>100)
			return -1;
		Student student = {lastName,firstName,studentID,midterm,final,(midterm+final)/2};
		i++;
		printf("Ici on est bon\n");
		if(addInList(&students,size,student)==-1)	// erreur ici
			return -1;
	}
	printf("i: %d\n",i);
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
	printf("Avant utilisation de fillData dans le main\n");
	// Remplis la liste avec toutes les infos
	int status = fillData(input,students,&size);
	printf("Après utilisation de fillData dans le main\n");

	//printf("Here it's ok\n");
	if(status==1){
		free(students);
		fclose(input);
		fputs("Error\n",output);
		fclose(output);
		return 0;
	}

	printArray(students,size);

    	return 0;
}
