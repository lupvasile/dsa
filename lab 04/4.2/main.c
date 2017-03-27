#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

FILE *openCheck(const char *name,const char *mode)
{
    FILE *f = fopen(name,mode);
    if(f == NULL)
    {
        perror("");
        exit(1);
    }

    return f;
}


int main(int argc,char *argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    NodeT *root;

    root = createBinTree( fin );

    fprintf(fout,"Height of tree: %d\n",getHeight(root,0));
    fprintf(fout,"Nr. of leaves: %d\n",getNrLeaves(root));

    fprintf(fout,"\ntraversals before swapping\n");
    showAllTraversals(root,fout);

    swapSons(findNode(root,'A'));
    fprintf(fout,"\ntraversals after swapping sons of A\n");
    showAllTraversals(root,fout);


    return 0;
}
