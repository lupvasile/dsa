#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *key;
    int count;
    struct node *next;
    struct node *prev;
} NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
} ListT;

int isEmpty(ListT *ptr);
ListT *createList();
NodeT *createNode(char *key);//returns pointer to new node
//int insertAtFront(ListT *listPtr,NodeT *nodePtr);
//int insertAtRear(ListT *listPtr,NodeT *nodePtr);
void insertInOrder(ListT *ptrList, char  *key);
void printList(FILE *f, ListT *ptrList, char separator);
//NodeT *find(ListT *ptrList,int key);//returns pointer to node with given key or NULL if not found
//NodeT *deleteByKey(ListT *ptrList,int key);//returns pointer to deleted node with given key or NULL if not found
//NodeT *deleteFirst(ListT *ptrList);//returns pointer to first node or NULL if empty list


#endif // LIST_H_INCLUDED
