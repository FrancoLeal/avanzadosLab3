#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bacteriums{
	int * numbers;
	int n;
} Bacteriums;

typedef struct max{
	int max;
	int pos;
} Max;

FILE * openFile(char * name){
	FILE * fp = fopen(name,"r");
	if(fp==NULL){
		printf("file not found\n");
		return NULL;
	}
	printf("opened file\n");
	return fp;
}

Bacteriums * initBacteriums(int n){
	Bacteriums * bacteriums = (Bacteriums*)malloc(sizeof(Bacteriums));
	bacteriums->numbers = (int*)malloc(sizeof(n));
	bacteriums->n = n;
	return bacteriums;
}

void setBacteriums(char * sBacteriums, Bacteriums * bacteriums){
	int i;
	for(i=0;i<bacteriums->n;i++){
		bacteriums->numbers[i]=sBacteriums[i]-'0';
	}
}

Bacteriums * getBacteriums(FILE * fp){
	int i;
	char sBacteriums[128];
	printf("getting bacteriums\n");
	fscanf(fp,"%s",sBacteriums);
	i = strlen(sBacteriums);
	Bacteriums * bacteriums = initBacteriums(i);
	printf("bacteriums obtained, %s, len %d\n",sBacteriums,bacteriums->n);
	setBacteriums(sBacteriums,bacteriums);
	return bacteriums;
}

Max getMax(Bacteriums * bacteriums){
	Max max;
	max.max=0;
	int i;
	for(i=0;i<bacteriums->n;i++){
		if(bacteriums->numbers[i]>max.max){
			max.max=bacteriums->numbers[i];
			max.pos=i;
		}
	}
	return max;
}

int getPrev(Bacteriums * bacteriums, int pos){
	if(pos == 0){
		return -1;
	}
	return bacteriums->numbers[pos-1];
}

int getNext(Bacteriums * bacteriums, int pos){
	if(pos == bacteriums->n-1){
		return -1;
	}
	return bacteriums->numbers[pos+1];
}

Bacteriums * splitMajors(Bacteriums * bacteriums){
	Max max = getMax(bacteriums);
	int prev = getPrev(bacteriums,max.pos);
	int next = getNext(bacteriums,max.pos);
	if(prev != -1){
		if(next != -1){
			printf("Prev %d, next %d\n",prev,next);
		}
	}
}

void main(){
	FILE * fp = openFile("entrada.in");
	Bacteriums * bacteriums = getBacteriums(fp);
	int i,j; 
	splitMajors(bacteriums);
}