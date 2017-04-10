#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdlib.h>
#include <time.h>///for rand
#include <stdio.h>

typedef struct bst_node
{
    void *pData;
    struct bst_node *left, *right;
    int priority;
} BST_NodeT;

typedef struct bst_tree
{
    BST_NodeT *root;
    int (*compareKeys)(void*, void*);
    void *(*extractKey)(void*);
    void (*printData)(void*);

} BST_Tree;

extern BST_NodeT *NIL;///dummy node

int isEmpty(BST_Tree *T);///returns 1 if T is empty
BST_Tree *createBstTree(int (*compareKeys)(void*, void*), void* (*extractKey)(void*), void (*printData)(void*));
void insertBST(BST_Tree *T, void *pData);//insert an element
void deleteBST(BST_Tree *T, void *pKey);//delete element
BST_NodeT *findBST(BST_Tree *T, void *pKey);//find element
BST_NodeT *findMinBST(BST_Tree *T);//find minimum element
BST_NodeT *findMaxBST(BST_Tree *T);//find maximum element
void preBST(BST_Tree *T);//print BST in preorder
void postBST(BST_Tree *T);//print BST in postorder
void inBST(BST_Tree *T);//print BST in inorder
void deleteTree(BST_Tree *T);//delete BST tree

#endif // BST_H_INCLUDED
