#include<stdio.h>

int main(){
	short int i = 1;
	char* p=(char*) &i;
	char firstByte = *p;
	if(firstByte)
		printf("LittleEndian");
	else
		printf("BigEndian");
}
