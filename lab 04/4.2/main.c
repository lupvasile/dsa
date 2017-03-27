#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
  char id; /* node name */
  /* ... other useful info */
  struct node_type *left, *right;
} NodeT;
void fatalError( const char *msg )
{
 printf( msg );
 printf( "\n" );
 exit ( 1 );
}
void preorder( NodeT *p, int level )
{
  if ( p != NULL )
  {
    for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
    printf( "%c\n", p->id );
    preorder( p->left, level + 1 );
    preorder( p->right, level + 1 );
  }
}
void inorder( NodeT *p, int level )
{
  if ( p != NULL )
  {
    inorder( p->left, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
    printf( "%c\n", p->id );
    inorder( p->right, level + 1 );
  }
}
//-----  --- Code part 04 ----------------------
// Construction and traversals of binary trees (continued)}
void postorder( NodeT *p, int level )
{
  if ( p != NULL )
  {
    postorder( p->left, level + 1 );
    postorder( p->right, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
    printf( "%c\n", p->id );
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
  { /* build node pointed to by p */
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


int main(int argc,char *argv[])
{
    FILE *fin = openCheck(argv[1],"r");
    FILE *fout = openCheck(argv[2],"w");

  NodeT *root;

  root = createBinTree( fin );

  printf("%d\n",getHeight(root,0));
  printf("%d",getNrLeaves(root));

  printf( "\nPreorder listing\n" );
  preorder( root, 0 );
  printf( "Press Enter to continue." );
  while ('\n' != getc(stdin));
  printf( "\nInorder listing\n" );
  inorder( root, 0 );
  printf( "Press Enter to continue." );
  while ('\n' != getc(stdin));
  printf( "\nPostorder listing\n" );
  postorder( root, 0 );
  printf( "Press Enter to continue." );
  while ('\n' != getc(stdin));
  return 0;
}
