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
NodeT *createNode(int key)
{
    NodeT *ptr = (NodeT *) malloc(sizeof(NodeT));

    if(ptr)
    {
        ptr->key = key;
        ptr->next = NULL;
    }
    else
    {
        printf("not enougn memory for node");
        exit(2);
    }
    return ptr;
}

///given Node->next and prevNode adress
///returns via next and last the pointers to next and previous elements in list
void getNextPrev(NodeT *prevPtr, NodeT *ptr, NodeT **next, NodeT **last)
{
    *next = (NodeT*) ( (int)ptr ^ (int) prevPtr );
    *last = (NodeT*) ( (int)ptr ^ (int) *next );
}

///receives a pointer to a list and a pointer to a node
///attempts to insert node at begining of list
///returns 1 on succes
///returns 0 on fail
int insertAtFront(ListT *listPtr,NodeT *nodePtr)
{

    if(listPtr)
    {
        nodePtr->next = listPtr->first;

        if(isEmpty(listPtr))
        {
            listPtr->last = nodePtr;
            listPtr->first = nodePtr;
            listPtr->count++;
            return 1;
        }

        listPtr->first->next = (NodeT*) ((int)listPtr->first->next ^ (int)nodePtr);
        listPtr->first = nodePtr;
        listPtr->count++;
        return 1;
    }
    return 0;
}

///receives a file and a pointer to a list
///prints to file the content of the lists
///if the list is empty, it prints "none"
void printList(FILE *f, ListT *ptrList, char separator)
{
    if(isEmpty(ptrList)) fprintf(f,"none%c",separator);
    else
    {
        NodeT *nodePtr = ptrList->first, *prevNode = NULL, *next, *prev;
        for(; nodePtr != NULL; )
        {
            fprintf(f,"%d%c",nodePtr->key,separator);
            getNextPrev(prevNode, nodePtr->next, &next, &prev);

            if(prevNode!=prev) printf("asdf");

            prevNode = nodePtr;
            nodePtr = next;

        }
    }

}
