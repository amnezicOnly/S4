#include<stdio.h>
#include<stdlib.h>
#include<err.h>
i
/*
https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/

*/


int thirdBitFromRight(int n){
	// check if the third bit of n from the right is 1	
	int mask = 4;
	return (mask & n)==4;
}

int thirdnOneBitTurnOn(int n){
	// make the first and third bit become 1
	return n|5;
}


int main(int argc, char** argv){
	printf("%d",thirdBitFromRight(8));
	return 0;
}
