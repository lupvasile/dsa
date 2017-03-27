#include "tree.h"

void fatalError( const char *msg )
{
    printf(msg );
    printf("\n" );
    exit ( 1 );
}
void preorder( NodeT *p, int level, FILE *fout)
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ ) fprintf(fout, " " ); /* for nice listing */
        fprintf(fout, "%c\n", p->id );
        preorder( p->left, level + 1, fout );
        preorder( p->right, level + 1, fout );
    }
}
void inorder( NodeT *p, int level, FILE *fout)
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1, fout );
        for ( int i = 0; i <= level; i++ ) fprintf(fout, " " ); /* for nice listing */
        fprintf(fout, "%c\n", p->id );
        inorder( p->right, level + 1, fout );
    }
}

void postorder( NodeT *p, int level, FILE *fout)
{
    if ( p != NULL )
    {
        postorder( p->left, level + 1, fout );
        postorder( p->right, level + 1, fout );
        for ( int i = 0; i <= level; i++ ) fprintf(fout, " " ); /* for nice listing */
        fprintf(fout, "%c\n", p->id );
    }
}
NodeT *createBinTree(FILE *fin)
{
    NodeT *p;
    char c;
    /* read node id */
    fscanf(fin, "%c", &c);
    if ( c == '*' )
        return NULL; /* empty tree; do nothing */
    else /* else included for clarity */
    {
        /* build node pointed to by p */
        p = ( NodeT *) malloc( sizeof( NodeT ));
        if ( p == NULL )
            fatalError( "Out of space in createBinTree" );
        /* fill in node */
        p->id = c;
        p->left = createBinTree(fin);
        p->right = createBinTree(fin);
    }
    return p;
}

///a tree and an node id is given
///on succes, a pointer to a node with given ID is returned
///if not found, NULL is returned
NodeT* findNode(NodeT *node, char id)
{
    if(node == NULL) return NULL;///empty tree

    if(node->id == id) return node;///we have found the node

    NodeT *ptrNode;
    ptrNode = findNode(node->left, id);///search in left child
    if(ptrNode != NULL) return ptrNode;///we have found the node

    return findNode(node->right, id);///we search in the right child
}

///a pointer to a node is given
///the left and right childs of that node are swapped
void swapSons(NodeT *node)
{
    if(node == NULL) return;

    NodeT *aux;
    aux = node->left;
    node->left = node->right;
    node->right = aux;
}

///a tree is given
///returns the height of the tree
///if empty tree, returns -1
int getHeight(NodeT *node, int level)
{
    if(node == NULL) return level-1;

    int leftHeight, rightHeight;
    leftHeight = getHeight(node->left, level+1);
    rightHeight = getHeight(node->right, level+1);

    if(leftHeight > rightHeight) return leftHeight;
    return rightHeight;


}

///returns number of leaves in a tree
int getNrLeaves(NodeT *node)
{
    if(node == NULL) return 0;

    if(node->left == NULL && node->right == NULL) ///we are in a leaf
        return 1;

    int nrLeaves = 0;
    nrLeaves += getNrLeaves(node->left);
    nrLeaves += getNrLeaves(node->right);

    return nrLeaves;
}

void showAllTraversals(NodeT *root, FILE *fout)
{
    fprintf(fout, "Preorder listing\n" );
    preorder( root, 0, fout );

    fprintf(fout, "\nInorder listing\n" );
    inorder( root, 0, fout );

    fprintf(fout, "\nPostorder listing\n" );
    postorder( root, 0, fout );

}
