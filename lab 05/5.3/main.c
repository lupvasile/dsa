#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
#include "pharma.h"
#include "TEST.h"

FILE *fin,*fout;

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

int compareKeys(void *key1, void *key2)
{
    return strcmp((char*)key1, (char*)key2);
}

void *extractKey(void *it)
{
    return ((ItemT *)it)->name;
}

void printItem(void *it)
{
    ItemT *p = (ItemT*) it;
    fprintf(fout,"%s %g %g ",p->name,p->amount,p->price);
    struct tm *time = localtime(&p->dateOfManufacturing);
    fprintf(fout,"%04d%02d%02d",time->tm_year+1900, time->tm_mon+1,time->tm_mday);

    time = localtime(&p->dateOfExpiration);
    fprintf(fout," %04d%02d%02d\n",time->tm_year+1900, time->tm_mon+1,time->tm_mday);
}

void update(BST_Tree *T, FILE *fin)
{
    ItemT *newItem;

    char buf[NAME_SIZE];
    fscanf(fin,"%[^,]200s",buf);
    fgetc(fin);

    BST_NodeT *oldItem = findBST(T,buf);
    if(oldItem == NULL) return;

    newItem = getItem(fin);
    if(newItem->name[0] == '~') strcpy(newItem->name,((ItemT*)(oldItem->pData))->name);
    if(newItem->dateOfExpiration == -inf) newItem->dateOfExpiration = ((ItemT*)(oldItem->pData))->dateOfExpiration;
    if(newItem->dateOfManufacturing == -inf) newItem->dateOfManufacturing = ((ItemT*)(oldItem->pData))->dateOfManufacturing;
    if(newItem->amount == -inf)  newItem->amount = ((ItemT*)(oldItem->pData))->amount;
    if(newItem->price == -inf) newItem->price = ((ItemT*)(oldItem->pData))->price;

    if(strcmp(newItem->name,((ItemT*)(oldItem->pData))->name) == 0)
    {
        free(oldItem->pData);
        oldItem->pData = newItem;
    }
    else
    {
        deleteBST(T,((ItemT*)(oldItem->pData))->name);
        free(oldItem->pData);
        insertBST(T,newItem);
    }

}


void dfs(BST_NodeT *pNode, BST_Tree *T)
{
    if (pNode == NIL) return ;

    if(expirat(pNode->pData))
        insertBST(T,pNode->pData);

    dfs(pNode->left,T);
    dfs(pNode->right,T);
}

void addExpired(BST_Tree *to, BST_Tree *from)
{
    dfs(from->root,to);
}


int main(int argc,char *argv[])
{

	///name lenght maximum 200 characters
    fin = openCheck(argv[1],"w");
    makeTest(fin);///currently nr_MED is 1e5
    fclose(fin);


    fin = openCheck(argv[1],"r");
    fout = openCheck(argv[2],"w");

    BST_Tree *T = createBstTree(compareKeys,extractKey, printItem);
    BST_Tree *ExpiredT = createBstTree(compareKeys,extractKey, printItem);

    char op;
    while((op = readOp(fin))!=EOF)
    {


        switch (op)
        {
            case 'i':
                {
                    ItemT *ptr = getItem(fin);
                    insertBST(T,ptr);
                    break;
                }
            case 'u':
                {
                    update(T,fin);
                    break;
                }
            case 'd':
                {
                    char buf[NAME_SIZE];
                    fscanf(fin,"%[^\n]200s",buf);
                    deleteBST(T,buf);
                    break;
                }
            case 'c':
                {
                    fgetc(fin);///read e
                    deleteTree(ExpiredT);
                    addExpired(ExpiredT,T);
                    fprintf(fout,"\nexpired medicines\n");
                    inBST(ExpiredT);
                }

        }

    }

    fprintf(fout,"\nall medicines in DB\n");
    inBST(T);

    fclose(fin);
    fclose(fout);
    return 0;
}
