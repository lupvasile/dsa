#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    char id; /* node name */
    /* ... other useful info */
    struct node_type *left, *right;
} NodeT;

void preorder( NodeT *p, int level, FILE *fout);
void inorder( NodeT *p, int level, FILE *fout);
void postorder( NodeT *p, int level, FILE *fout);
NodeT* createBinTree(FILE *fin);
NodeT* findNode(NodeT *node, char id);
void swapSons(NodeT *node);
int getHeight(NodeT *node, int level);
int getNrLeaves(NodeT *node);
void showAllTraversals(NodeT *root, FILE *fout);

#endif // TREE_H_INCLUDED
