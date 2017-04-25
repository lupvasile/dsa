#ifndef IO_MANAGEMENT_H_INCLUDED
#define IO_MANAGEMENT_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

#define NAMELEN 500

typedef struct edge
{
    int node,val;
} EdgeT;


FILE *openCheck(const char *name,const char *mode);
int getMaxLen(FILE *f, char *delim);///returns max length of a string without characters from delim
void readArcs(FILE *fin, int *nodes, int nrNodes, ListT *adj[], EdgeT arcs[]);
int getNrNodes(FILE *fin, int *nrarcs);

#endif // IO_MANAGEMENT_H_INCLUDED
