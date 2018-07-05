#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bacteriums{
	int * numbers;
	int n;
} Bacteriums;

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

Bacteriums * copyBacteriums(Bacteriums * bacteriums){
	Bacteriums * copy = initBacteriums(bacteriums->n);
	int i;
	for(i=0;i<bacteriums->n;i++){
		copy->numbers[i]=bacteriums->numbers[i];
	}
	return copy;
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

int splitBacteriums(int a, int b){
	if(a!=b){
		return 6-(a+b);
	}
	return -1;
}
void printBacts(Bacteriums * bacts){
	int i;
	for(i=0;i<bacts->n;i++){
		printf("%d-",bacts->numbers[i]);
	}
	printf(" len %d\n",bacts->n);
}

Bacteriums * replaceBact(Bacteriums * bacteriums, int bact, int pos){
	Bacteriums * new = initBacteriums(bacteriums->n-1);
	int i;
	for(i=0;i<bacteriums->n;i++){
		if(i<pos){
			new->numbers[i]=bacteriums->numbers[i];
		}
		else if(i==pos){
			new->numbers[i]=bact;	
		}
		else{
			new->numbers[i]=bacteriums->numbers[i+1];	
		}
	}
	return new;
}

int expon(int number,int n){
	int i,value=1;
	for(i=1;i<=n;i++){
		value=value*number;
	}
	return value;
}

int bactsToInt(Bacteriums* bacts){
	int i,value=0;
	for(i=bacts->n;i>0;i--){
		value=value+bacts->numbers[i-1]*expon(10,bacts->n-i);
	}
	return value;
}

Bacteriums * getMinor(Bacteriums * bacts1, Bacteriums * bacts2){
	int intBacts1 = bactsToInt(bacts1);
	int intBacts2 = bactsToInt(bacts2);
	if(intBacts1<intBacts2){
		return copyBacteriums(bacts1);
	}
	return copyBacteriums(bacts2);
}

Bacteriums * reduce(Bacteriums * bacteriums, Bacteriums * min){
	int i;
	Bacteriums * aux;
	for(i=0;i<bacteriums->n-1;i++){
		int bact = splitBacteriums(bacteriums->numbers[i],bacteriums->numbers[i+1]);
		printf("Bacteria a reemplazar: %d\n",bact);
		if(bact!=-1){
			aux = replaceBact(bacteriums,bact,i);
			min = getMinor(aux,min);

	printf("****************Bacterias posible menor*************\n");
	printBacts(min);
		}
	}
	printf("****************Bacterias menor*************\n");
	printBacts(min);
	return min;
}


int isReducible(Bacteriums * bacteriums){
	int i,bact=bacteriums->numbers[0];
	for(i=1;i<bacteriums->n;i++){
		if(bacteriums->numbers[i]!=bact){
			return 1;
		}
	}
	return 0;
}

void main(){
	FILE * fp = openFile("entrada.in");
	Bacteriums * bacteriums = getBacteriums(fp);
	Bacteriums * min = copyBacteriums(bacteriums);
	while(isReducible(min)){
		bacteriums = copyBacteriums(min);
		min = reduce(bacteriums,min);
	}
	printBacts(min);
}