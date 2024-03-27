#include<stdio.h>
// À PEUT ÊTRE ENLEVER
#include<stdlib.h>

typedef struct Student{
	char* name;
	char* ID;
	int midterm;
	int final;
} Student;

int line = 1;

void listStudents(FILE* output, Student* students, size_t size){
	for(size_t i=0; i<size; i++)
		fprintf(output,"%s %s %d %d\n",students[i].name,students[i].ID,students[i].midterm,students[i].final);
}

void freeStudents(Student* students, size_t size){
	for(size_t i = 0; i<size; i++){
		free(students[i].name);
		free(students[i].ID);
	}
	free(students);
}

int getName(FILE* input, char** name, size_t* size,int type){
	char temp;
	while((temp=fgetc(input))!=' ' || temp=='\n' || temp!=EOF){
		printf("%c",temp);
		if((*size)==0)
			*name = malloc(sizeof(char));
		else
			*name = realloc(*name,((*size)+1)*sizeof(char));
		if(*name==NULL){
			printf("Erreur 1\n");
			return -1;
		}
		if(type==0 && !((temp>='a' && temp<='z')||(temp>='A' && temp<='Z'))){
			printf("Erreur 2\n");
				return -1;
		}
		if(type==1 && (((*size)==0 && temp!='A')||((*size)==0 && (temp<'0' || temp>'9')))){
			printf("Erreur 3\n");
			return -1;
		}
		(*name)[(*size)] = temp;
		(*size)++;
	}
	if(temp!=' '){
		printf("Erreur 4\n");
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
	while((temp=fgetc(input))!='\n' || temp!=' '){
		if(temp<'0' || temp>'9' || temp>100)
			return -1;
		res*=10;
		res+=(temp-'0');
	}
	if((type==0 && temp!=' ')||(type==1 && temp!='\n'))
		return -1;
	return res;
}

int addToList(Student** students, size_t* size, char* Name, char* id, int Midterm, int Final){
	for(size_t i=0; i<(*size); i++){
		if(sortNames((*students)[i].ID,id)==0)
			return -1;
	}
	
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
	if(newStudent==NULL)
		return -1;
	
	newStudent->ID = id;
    	newStudent->name = Name;
    	newStudent->midterm = Midterm;
    	newStudent->final = Final;
    	
    	(*students)[*size] = *newStudent;
    	(*size)++;
    	
    	
    	size_t i = (*size)-1;
    	// RESTE À FAIRE LE TRI DE LA LISTE
    	free(newStudent);    	
    	
    	 return 1;
}

int catchData(FILE* input, Student** students, size_t* size){
	char temp;
	char temp2;
	int i = 1;
	printf("Rentre dans catchData\n");
	while((temp=fgetc(input))!='E' && ((temp2=fgetc(input))!=EOF)){
		printf("Rentre dans la boucle de catchData\n");
		char* name = malloc(2*sizeof(char));
		name[0] = temp;
		name[1] = temp2;
		size_t size2 = 2;
		int nameStatus = getName(input,&name,&size2,0);
		if(nameStatus==-1){
			printf("Error in getName0\n");
			return -1;
		}
		nameStatus = getName(input,&name,&size2,0);
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
			printf("Error in getGrade\n");
			return -1;
		}
		
		int final = getGrade(input,1);
		if(final<0){
			printf("Error in getGrade\n");
			return -1;
		}
		printf("Ligne %d ok\n",i);
		i++;
		
		int addStatus = addToList(students, size, name, id, midterm, final);
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
		
	Student* students = NULL;
	size_t size = 0;
	
	int processStatus = catchData(input,&students,&size);
	if(processStatus==-1 || size==0){
		fputs("Error in input.txt file.\n",output);
		fclose(input);
		fclose(output);
		free(students);
		return 0;
	}
	
	listStudents(output,students,size);
	fclose(input);
	fclose(output);
	freeStudents(students,size);
	return 0;
}
