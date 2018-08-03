#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <string.h>
#include "structs.h"


FILE * openFile(char * name);

Bacteriums * initBacteriums(int n);

void setBacteriums(char * sBacteriums, Bacteriums * bacteriums);

Bacteriums * copyBacteriums(Bacteriums * bacteriums);

Bacteriums * getBacteriums(FILE * fp);

int splitBacteriums(int a, int b);

void printBacts(Bacteriums * bacts);

Bacteriums * replaceBact(Bacteriums * bacteriums, int bact, int pos);

int expon(int number,int n);

int bactsToInt(Bacteriums* bacts);

Bacteriums * getMinor(Bacteriums * bacts1, Bacteriums * bacts2);

Bacteriums * reduce(Bacteriums * bacteriums, Bacteriums * min);

int isReducible(Bacteriums * bacteriums);

void writeBacts(FILE * fp, Bacteriums * bacteriums);

void init();

#endif
