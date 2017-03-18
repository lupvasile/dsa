#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


typedef struct node
{
    char *s;
    int count;
    struct node *next;
} NodeT;

void toLower(char *s)
{
    for(;*s;++s)
        if('A'<=*s && *s<='Z') *s += 'a' - 'A';
    else if(!isalnum(*s)) *s = '\0';
}

void swap_values(NodeT *a,NodeT *b)
{
    int x = a->count;
    a->count = b->count;
    b->count = x;

    char *s = a->s;
    a->s = b->s;
    b->s = s;

    NodeT *p = a->next;
    a->next = b->next;
    b->next = p;
}

void insertNode(NodeT **ptrList, char *s)
{
    NodeT *ptr = *ptrList,*prevPtr = NULL;
    for(;ptr && strcmp(ptr->s,s)<0;ptr = ptr->next) prevPtr = ptr;

    if(ptr && strcmp(ptr->s,s) == 0)///the word already exits
        ptr->count++;
    else///new word
    {
        ///make the new node
        NodeT *elem = malloc(sizeof(NodeT));
        if(!elem) printf("not enough memory"),exit(2);

        elem->count = 1;
        elem->s = strdup(s);
        elem->next = NULL;

        if(*ptrList == NULL) ///empty list
        {
            *ptrList = elem;
            return;
        }
        else///list not empty
        {
            if(prevPtr == NULL)///node at begining of list
            {
                elem->next = *ptrList;
                *ptrList = elem;
            }
            else
            {
                elem->next = ptr;
                prevPtr->next = elem;
            }

        }
    }
}

void printList(NodeT *ptr,FILE *fout)
{
    for(;ptr;ptr = ptr->next)
        fprintf(fout,"%s : %d ",ptr->s,ptr->count);
}

int main(int argc,char* argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

    NodeT *ptrList = NULL;

    char buf[1024];
    while(fscanf(fin,"%s",buf) != EOF)
    {
        toLower(buf);
        insertNode(&ptrList,buf);
    }

    printList(ptrList,fout);
    return 0;
}
