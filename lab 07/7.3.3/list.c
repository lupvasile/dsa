#include "list.h"

///receives list pointer
///returns 1 if list is empty
///return 0 if list is not empty
int isEmpty(ListT *ptr)
{
    if(ptr == NULL) return 1;
    if(ptr->count == 0) return 1;
    return 0;
}

///attempts to allocate memory for a new empry list
///on succes returns pointer to list
///halts on failure
ListT *createList()
{
    ListT *ptrList = (ListT *) malloc(sizeof(ListT));

    if(ptrList)
    {
        ptrList->count = 0;
        ptrList->first = ptrList->last = NULL;
    }
    else
    {
        printf("not enougn memory for list");
        exit(2);
    }

    return ptrList;
}

///receives key of a node
///attempts to allocate memory for a new node of a list with given key
///on succes returns pointer to node
///halts on failure
NodeT *createNode(void *pData)
{
    NodeT *ptr = (NodeT *) malloc(sizeof(NodeT));

    if(ptr)
    {
        ptr->pData = pData;
        ptr->next = NULL;
    }
    else
    {
        printf("not enougn memory for node");
        exit(2);
    }
    return ptr;
}

///receives a pointer to a list and a pointer to a node
///attempts to insert node at begining of list
///returns 1 on succes
///returns 0 on fail
int insertAtFront(ListT *listPtr,NodeT *nodePtr)
{

    if(listPtr)
    {
        if(isEmpty(listPtr)) listPtr->last = nodePtr;
        nodePtr->next = listPtr->first;
        listPtr->first = nodePtr;
        listPtr->count++;
        return 1;
    }
    return 0;
}

///receives a pointer to a list and a pointer to a node
///attempts to insert node at end of list
///returns 1 on succes
///returns 0 on fail
int insertAtRear(ListT *listPtr,NodeT *nodePtr)
{
    if(listPtr)
    {
        if(isEmpty(listPtr))
        {
            listPtr->first = nodePtr;
        }
        else
        {
            listPtr->last->next = nodePtr;
        }

        nodePtr->next = NULL;
        listPtr->last = nodePtr;
        listPtr->count++;
        return 1;
    }
    return 0;
}

///receives a list pointer
///erases first element and returns pointer to it
///returns NULL if list is empty
NodeT *deleteFirst(ListT *ptrList)
{
    if(isEmpty(ptrList)) return NULL;

    NodeT *ptr = ptrList->first;

    if(ptrList->count == 1)
    {
        ptrList->first = ptrList->last = NULL;
    }
    else
    {
        ptrList->first = ptrList->first->next;
    }

    ptrList->count--;

    return ptr;
}
