#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nr_nodes 100000
#define nr_arcs 100000


void makeTest(FILE *fin);
void readArcsNormalisedMat(FILE *fin, int *nodes, int nrNodes, char adj[nrNodes][nrNodes], int nrArcs);

#endif // TEST_H_INCLUDED
