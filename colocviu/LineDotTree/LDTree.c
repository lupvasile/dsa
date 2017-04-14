#include "LDTree.h"

static LD_NodeT *createNode(char key)
{
    LD_NodeT *p = (LD_NodeT*) malloc(sizeof(LD_NodeT));

    if(p == NULL)
    {
        printf("not enough memory");
        exit(2);
    }

	p->left = p->right = NULL;
    p->key = key;

    return p;
}

LD_NodeT *insertNode(LD_NodeT *root, char *code, char key)
{
    if(root == NULL) root = createNode(NOCHAR);

    if(*code == '\0')
    {
        root->key = key;
        return root;
    }

    if(*code == '.') root->left = insertNode(root->left,code+1,key);
    if(*code == '-') root->right = insertNode(root->right,code+1,key);

    return root;
}

LD_NodeT *LineDotCodeTree(FILE *fin)
{
    LD_NodeT *root = NULL;

    int bufLen = getMaxLen(fin,"\n")+2;
    char buf[bufLen];
    char ins[bufLen];
    while (fgets(buf,sizeof buf,fin))
    {
        sscanf(buf+1,"%s",ins);
        root = insertNode(root,ins,buf[0]);
    }

    return root;
}

static char dfsLD(LD_NodeT *root,char *from)
{
    if(root == NULL) return NOCHAR;

    if (*from == '\0') return root->key;

    if(*from == '.') return dfsLD(root->left,from+1);
    if(*from == '-') return dfsLD(root->right,from+1);

    return NOCHAR;
}

char translate(LD_NodeT *root,char *from)
{
     return dfsLD(root,from);
}
