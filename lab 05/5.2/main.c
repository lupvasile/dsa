#include <stdio.h>
#include <stdlib.h>
#include "BST.h"


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

FILE *fin,*fout;

int compare (void *key1, void *key2)
{
    char c1 = *(char *)key1;
    char c2 = *(char *)key2;
    return c1 - c2;
}

void *extract(void *item)
{
    return item;
}

void print(void *item)
{
    fprintf(fout,"%c " ,*(char*)item);
}

char *allocChar(char ch)
{
    char *p = malloc(sizeof(char));
    if(p == NULL)
    {
        fprintf(fout,"not eoungh memory");
        exit(2);
    }

    *p = ch;
    return p;
}

int main(int argc,char* argv[])
{
    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    BST_Tree *T = createBstTree(compare,extract,print);

    char buf[4];
    while(fgets(buf,sizeof buf,fin))
    {
        switch (buf[0])
        {
        case 'i':
            insertBST(T,allocChar(buf[1]));
            break;
        case 'd':
            deleteBST(T,&buf[1]);
            break;
        case 'f':
        {
            if(findBST(T,&buf[1])==NULL) fprintf(fout,"not ");
            fprintf(fout,"found key %c\n",buf[1]);
            break;
        }
        case 'g':
        {
            if(isEmpty(T))
            {
                fprintf(fout,"there are no elements\n");
                break;
            }
            if(buf[1] == 'm')
            {
                fprintf(fout,"the minimum is ");
                BST_NodeT *p = findMinBST(T);
                print(p->pData);
                fprintf(fout,"\n");
            }
            if(buf[1] == 'M')
            {
                fprintf(fout,"the maximum is ");
                BST_NodeT *p = findMaxBST(T);
                print(p->pData);
                fprintf(fout,"\n");
            }
            break;
        }
        case 't':
        {
            if(isEmpty(T))
            {
                fprintf(fout,"there are no elements\n");
                break;
            }

            if (buf[1] == 'P')
            {
                fprintf(fout,"Postorder listing: ");
                postBST(T);
                fprintf(fout,"\n");
            }
            if (buf[1] == 'p')
            {
                fprintf(fout,"Preorder listing: ");
                preBST(T);
                fprintf(fout,"\n");
            }
            if (buf[1] == 'i')
            {
                fprintf(fout,"Inorder listing: ");
                inBST(T);
                fprintf(fout,"\n");
            }
        }
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
