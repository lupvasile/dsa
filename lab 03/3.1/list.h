#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char *key;
    struct node *next;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
} ListT;

int isEmpty(ListT *ptr);
ListT *createList();
NodeT *createNode(char *key);//returns pointer to new node
//int insertAtFront(ListT *listPtr,NodeT *nodePtr);
int insertAtRear(ListT *listPtr,NodeT *nodePtr);
void printList(FILE *f, ListT *ptrList,char separator);
//NodeT *find(ListT *ptrList,int key);//returns pointer to node with given key or NULL if not found
//NodeT *deleteByKey(ListT *ptrList,int key);//returns pointer to deleted node with given key or NULL if not found
NodeT *deleteFirst(ListT *ptrList);//returns pointer to first node or NULL if empty list


#endif // LIST_H_INCLUDED
