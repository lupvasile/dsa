#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *pData;
    struct node *next;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

int isEmpty(ListT *ptr);
ListT *createList();
NodeT *createNode(void *pData);//returns pointer to new node
int insertAtFront(ListT *listPtr,NodeT *nodePtr);
int insertAtRear(ListT *listPtr,NodeT *nodePtr);
NodeT *deleteFirst(ListT *ptrList);//returns pointer to first node or NULL if empty list


#endif // LIST_H_INCLUDED
