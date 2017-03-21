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

char *strdup (const char *s)
{
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) // No memory
    {
        printf("not enougn memory for list");
        exit(2);          // No memory
    }
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
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
        ptrList->first = createNode("");
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
NodeT *createNode(char *s)
{
    NodeT *ptr = (NodeT *) malloc(sizeof(NodeT));

    if(ptr)
    {
        ptr->key = (char*) strdup(s);
        ptr->next = ptr->prev = NULL;
    }
    else
    {
        printf("not enougn memory for node");
        exit(2);
    }
    return ptr;
}

/*
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
*/

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
            listPtr->first->next = nodePtr;
            listPtr->first->prev = nodePtr;
            nodePtr->next = nodePtr->prev = listPtr->first;
        }
        else
        {
            nodePtr->prev = listPtr->first->prev;
            nodePtr->next = listPtr->first;
            listPtr->first->prev->next = nodePtr;
            listPtr->first->prev = nodePtr;
        }

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
        NodeT *nodePtr = ptrList->first->next;
        NodeT *firstNode = ptrList->first;

        do
        {
            fprintf(f,"%s%c",nodePtr->key,separator);
            nodePtr = nodePtr->next;
        }
        while(nodePtr != firstNode);
    }

}

///receives a list pointer and a key
///returns a pointer to an element with given key if fount
///NULL otherwise
NodeT *find(ListT *ptrList,char* key)
{
    NodeT *ptrNode = NULL;
    if(isEmpty(ptrList)) return NULL;

    for(ptrNode = ptrList->first->next; ptrNode != ptrList->first; ptrNode = ptrNode->next)
        if(strcmp(ptrNode->key,key)==0) return ptrNode;

    return NULL;
}

/*
///receives a list pointer and a key
///erases a node with given key from list and returns pointer to it
///does not change list and returns NULL if no element with key if found
NodeT *deleteByKey(ListT *ptrList,int key)
{
    NodeT *ptr=NULL,*prevPtr=NULL;

    if(isEmpty(ptrList)) return NULL;

    ptr = ptrList->first;
    while(ptr != NULL)
    {
        if(ptr->key == key) break;
        prevPtr = ptr;
        ptr = ptr->next;
    }

    if(ptr == NULL) return NULL;

    if(ptrList->count == 1)
    {
        ptrList->first = ptrList->last = NULL;
    }
    else
    {
        if(prevPtr) prevPtr->next = ptr->next;
        else return deleteFirst(ptrList);
    }

    ptrList->count--;
    return ptr;
}
*/
/*
static void swap_values(NodeT *a,NodeT *b)
{
    char *key = a->key;
    a->key = b->key;
    b->key = key;

    NodeT *p = a->next;
    a->next = b->next;
    b->next = p;
}
*/
///deletes element given by pointer
NodeT *deleteAtIndex(ListT *ptrList,NodeT *ptrNode)
{
    if(isEmpty(ptrList)) return NULL;

    ptrNode->prev->next = ptrNode->next;
    ptrNode->next->prev = ptrNode->prev;

    ptrList->count--;
    return ptrNode;
}
/*///receives a list pointer
///erases first element and returns pointer to it
///returns NULL if list is empty
NodeT *deleteFirst(ListT *ptrList)
{
    if(isEmpty(ptrList)) return NULL;

    NodeT *ptr = ptrList->first->next;

    if(ptrList->count == 1)
    {
        ptrList->first = NULL;
    }
    else
    {
        swap_values(ptrList->first,ptr);
    }

    ptrList->count--;

    return ptr;
}
*/
