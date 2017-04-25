#ifndef IO_MANAGEMENT_H_INCLUDED
#define IO_MANAGEMENT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#define NAMELEN 500

FILE *openCheck(const char *name,const char *mode);
int getMaxLen(FILE *f, char *delim);///returns max length of a string without characters from delim
void readArcsNormalised(FILE *fin, int *nodes, int nrNodes, ListT *adj[], int nrArcs);
int getNrNodes(FILE *fin);
int getNrArcs(FILE *fin);
void readNodes(FILE *fin,char *name, int *nodes, int nrNodes);
int binSrc(int a[],int n, int val);

#endif // IO_MANAGEMENT_H_INCLUDED
