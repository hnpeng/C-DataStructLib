#include "BSTreeCase.h"

#include "BSTree/BSTree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    BSTreeNode header;
    char* v;
}Node;

int compare(BSKey* k1, BSKey* k2)
{
    return (int)k1 - (int)k2;
}

void pfunc(BSTreeNode* node)
{
    printf("%s", ((Node*)node)->v);
}

void BSTreeCase()
{
    BSTree* tree = BSTree_Create();
    Node n50 = {{(BSKey*)50, NULL, NULL}, "50"};
    Node n30 = {{(BSKey*)30, NULL, NULL}, "30"};
    Node n60 = {{(BSKey*)60, NULL, NULL}, "60"};
    Node n20 = {{(BSKey*)20, NULL, NULL}, "20"};
    Node n40 = {{(BSKey*)40, NULL, NULL}, "40"};
    Node n10 = {{(BSKey*)10, NULL, NULL}, "10"};
    Node n25 = {{(BSKey*)25, NULL, NULL}, "25"};
    Node n11 = {{(BSKey*)11, NULL, NULL}, "11"};
    Node n5 = {{(BSKey*)5, NULL, NULL}, "5"};

    BSTree_Insert(tree, (BSTreeNode*)&n50, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n30, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n60, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n20, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n40, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n10, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n25, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n11, compare);
    BSTree_Insert(tree, (BSTreeNode*)&n5, compare);

    BSTree_Display(tree, pfunc);
    printf("height = %d\n", BSTree_Height(tree));
    printf("degree = %d\n", BSTree_Degree(tree));
    BSTree_Delete(tree, (BSKey*)30, compare);

    printf("********************\n");

    BSTree_Display(tree, pfunc);
//    printf("get 6 vlue = %c\n", ((Node*)(BSTree_Get(tree, (BSKey*)6, compare)))->v);

    BSTree_Destroy(tree);
}
