#ifndef LDTREE_H_INCLUDED
#define LDTREE_H_INCLUDED

#include "IO_Management.h"

#define NOCHAR -1

typedef struct ld_node
{
    char key;
    struct ld_node *left;
    struct ld_node *right;
} LD_NodeT;

LD_NodeT *LineDotCodeTree(FILE *fin);
char translate(LD_NodeT *root,char *from);

#endif // LDTREE_H_INCLUDED
