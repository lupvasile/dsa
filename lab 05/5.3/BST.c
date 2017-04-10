#include "BST.h"

BST_NodeT *NIL;///dummy node
static BST_NodeT *createNode();

int isEmpty(BST_Tree *T)
{
    return T->root == NIL;
}

BST_Tree *createBstTree(int (*compareKeys)(void*, void*), void* (*extractKey)(void*), void (*printData)(void*))
{
    BST_Tree *p = (BST_Tree*) malloc(sizeof(BST_Tree));
    if(NIL == NULL) NIL = createNode();
    NIL->priority = 0;///lowest priority

    if(NIL == NULL || p == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

    p->root = NIL;
    p->compareKeys = compareKeys;
    p->extractKey = extractKey;
    p->printData = printData;

    srand(time(NULL));

    return p;
}

static BST_NodeT *createNode()
{
    BST_NodeT *p = (BST_NodeT*) malloc(sizeof(BST_NodeT));

    if(p == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

	p->left = p->right = NIL;
    p->pData = NULL;
    p->priority = rand()+1;

    return p;
}

static void rotate_left(BST_NodeT **node)
{
    BST_NodeT *son = (*node)->right;

    (*node)->right = son->left;
    son->left = (*node);
    *node = son;
}

static void rotate_right(BST_NodeT **node)
{
    BST_NodeT *son = (*node)->left;

    (*node)->left = son->right;
    son->right = (*node);
    *node = son;
}

static void balance(BST_NodeT **node)
{
    if((*node)->left->priority > (*node)->priority) rotate_right(node);
    else if((*node)->right->priority > (*node)->priority) rotate_left(node);
}

static void insert_node(BST_Tree *T, BST_NodeT **p2Node, void *pData)
{
    BST_NodeT *pNode = *p2Node;

    if(pNode == NIL)///we are at a leaf
    {
        pNode = createNode();
        pNode->pData = pData;
        *p2Node = pNode;
        return;
    }

    int cmp = T->compareKeys(T->extractKey(pData), T->extractKey(pNode->pData));

    if(cmp == 0)///data already present
    {
        //printf("already exists");
        return;
    }

    if(cmp < 0) insert_node(T, &pNode->left, pData);
    if(cmp > 0) insert_node(T, &pNode->right, pData);

    balance(p2Node);

}

void insertBST(BST_Tree *T, void *pData)
{
    insert_node(T, &T->root, pData);
}

static void delete_node(BST_Tree *T, BST_NodeT **p2Node, void *pKey)
{
    BST_NodeT *pNode = *p2Node;

    if(pNode == NIL) return;

    int cmp = T->compareKeys(pKey, T->extractKey(pNode->pData));

    if(cmp == 0)
    {
        if(pNode->left == NIL && pNode->right == NIL) ///we are in a leaf
        {
            *p2Node = NIL;
            return ;
        }

        if(pNode->left->priority > pNode->right->priority) rotate_right(p2Node);
        else rotate_left(p2Node);

        delete_node(T, p2Node, pKey);
    }

    if(cmp < 0) delete_node(T, &pNode->left, pKey);
    if(cmp > 0) delete_node(T, &pNode->right, pKey);
}

void deleteBST(BST_Tree *T, void *pKey)
{
    delete_node(T, &T->root, pKey);
}

BST_NodeT *findBST(BST_Tree *T, void *pKey)
{
    BST_NodeT *pNode = T->root;

    for(; pNode != NIL; )
    {
        int cmp = T->compareKeys(pKey, T->extractKey(pNode->pData));
        if(cmp == 0) return pNode;

        if(cmp < 0) pNode = pNode->left;
        if(cmp > 0) pNode = pNode->right;
    }

    if(pNode == NIL) return NULL;
    return pNode;
}


BST_NodeT *findMinBST(BST_Tree *T)
{
    BST_NodeT *pNode = T->root;

    while(pNode->left != NIL) pNode = pNode->left;

    if(pNode == NIL) return NULL;
    return pNode;
}


BST_NodeT *findMaxBST(BST_Tree *T)
{
    BST_NodeT *pNode = T->root;

    while(pNode->right != NIL) pNode = pNode->right;

    if(pNode == NIL) return NULL;
    return pNode;
}




static void printPre(BST_Tree *T, BST_NodeT *pNode)
{
    if(pNode == NIL) return;

    T->printData(pNode->pData);
    printPre(T, pNode->left);
    printPre(T, pNode->right);

}

void preBST(BST_Tree *T)
{
    printPre(T, T->root);
}

static void printPost(BST_Tree *T, BST_NodeT *pNode)
{
    if(pNode == NIL) return;

    printPre(T, pNode->left);
    printPre(T, pNode->right);
    T->printData(pNode->pData);

}

void postBST(BST_Tree *T)
{
    printPost(T, T->root);
}

static void printIn(BST_Tree *T, BST_NodeT *pNode)
{
    if(pNode == NIL) return;

    printIn(T, pNode->left);
    T->printData(pNode->pData);
    printIn(T, pNode->right);

}

void inBST(BST_Tree *T)
{
    printIn(T, T->root);
}

static void delete_all(BST_NodeT *pNode)
{
    if(pNode == NIL) return;

    delete_all(pNode->left);
    delete_all(pNode->right);

    free(pNode);
}

void deleteTree(BST_Tree *T)
{
    delete_all(T->root);
    T->root = NIL;
}
