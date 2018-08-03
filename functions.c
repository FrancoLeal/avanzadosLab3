#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "structs.h"


/*Abrir el archivo*/
FILE * openFile(char * name){
	FILE * fp = fopen(name,"r");
	if(fp==NULL){
		printf("file not found\n");
		return NULL;
	}
	printf("opened file\n");
	return fp;
}
/*Inicializar estructura de datos principal*/
Bacteriums * initBacteriums(int n){
	Bacteriums * bacteriums = (Bacteriums*)malloc(sizeof(Bacteriums));
	if(bacteriums==NULL){
		printf("Memoria insuficiente\n");
		return NULL;
	}
	bacteriums->numbers = (long*)malloc(sizeof(long)*n);
	if(bacteriums->numbers==NULL){
		printf("Memoria insuficiente\n");
		return NULL;
	}
	bacteriums->n = n;
	return bacteriums;
}


/*Transformar de char a int y copiarlos en un arreglo*/
void setBacteriums(char * sBacteriums, Bacteriums * bacteriums){
	int i;
	for(i=0;i<bacteriums->n;i++){
		bacteriums->numbers[i]=sBacteriums[i]-'0';
	}
}


/*Crea una copia del arreglo*/
Bacteriums * copyBacteriums(Bacteriums * bacteriums){
	Bacteriums * copy = initBacteriums(bacteriums->n);
	int i;
	for(i=0;i<bacteriums->n;i++){
		copy->numbers[i]=bacteriums->numbers[i];
	}
	return copy;
}

/*Lee el archivo y guarda las bacterias en un string*/
Bacteriums * getBacteriums(FILE * fp){
	int i;
	char sBacteriums[128];
	fscanf(fp,"%s",sBacteriums);
	i = strlen(sBacteriums);
	Bacteriums * bacteriums = initBacteriums(i);
	printf("bacteriums obtained, %s, len %d\n",sBacteriums,bacteriums->n);
	setBacteriums(sBacteriums,bacteriums);
	return bacteriums;
}

/*Junta bacterias adyacentes y devuelve la que corresponda. Si son iguales, devuelve -1*/
long splitBacteriums(long a, long b){
	if(a > 3 || b > 3){
		return -1;
	}
	if(a!=b){
		return 6-(a+b);
	}
	return -1;
}

/*Muestra arreglo de bacterias por consola*/
void printBacts(Bacteriums * bacts){
	int i;
	for(i=0;i<bacts->n;i++){
		printf("%ld-",bacts->numbers[i]);
	}
	printf(" len %d\n",bacts->n);
}

/*Recibe una estructura de bacterias y se copia en otra, pero jutando dos bacterias*/
Bacteriums * replaceBact(Bacteriums * bacteriums, long bact, int pos){
	int n = bacteriums->n;
	Bacteriums * new = initBacteriums(n-1);
	int i;
	for(i=0;i<bacteriums->n-1;i++){
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

/*Eleva un número a otro, indicados en las entradas*/
long expon(long number,int n){
	int i;
	long value=1;
	for(i=1;i<=n;i++){
		value=value*number;
	}
	return value;
}

/*Transforma el arreglo de enteros de bacterias a una variable long*/
long bactsToLong(Bacteriums* bacts){
	int i;
	long value=0;
	for(i=bacts->n;i>0;i--){
		value=value+bacts->numbers[i-1]*expon(10,bacts->n-i);
	}
	return value;
}

/*Calcula que estructura de bacterias es menor*/
Bacteriums * getMinor(Bacteriums * bacts1, Bacteriums * bacts2){
	long intBacts1 = bactsToLong(bacts1);
	long intBacts2 = bactsToLong(bacts2);
	if(intBacts1<intBacts2){
		return copyBacteriums(bacts1);
	}
	return copyBacteriums(bacts2);
}
/*Compara dos estructuras de bacterias y devuelve la menor*/
Bacteriums * reduce(Bacteriums * bacteriums, Bacteriums * min){
	int i;
	Bacteriums * aux;
	for(i=0;i<bacteriums->n-1;i++){
		long bact = splitBacteriums(bacteriums->numbers[i],bacteriums->numbers[i+1]);
		if(bact!=-1){
			aux = replaceBact(bacteriums,bact,i);
			min = getMinor(aux,min);
		}
	}
	return min;
}

/*Verifica si todas las bacterias son iguales*/
int isReducible(Bacteriums * bacteriums){
	int i;
	long bact=bacteriums->numbers[0];
	for(i=0;i<bacteriums->n;i++){
		long aux = bacteriums->numbers[i];
		if(aux != bact){
			return 1;
		}
	}
	return 0;
}

/*Escribe el archivo de salida*/
void writeBacts(FILE * fp, Bacteriums * bacteriums){
	long bacts = bactsToLong(bacteriums);
	fprintf(fp,"%ld\n",bacts);
}

/*Inicializa el programa*/
void init(){
	FILE * fp = openFile("entrada.in");
	FILE * fpOut = fopen("salida.out","w");
	Bacteriums * bacteriums = getBacteriums(fp);
	writeBacts(fpOut,bacteriums);
	Bacteriums * min = copyBacteriums(bacteriums);
	while(isReducible(min)){
		bacteriums = copyBacteriums(min);
		min = reduce(bacteriums,min);
		writeBacts(fpOut,min);
	}
}