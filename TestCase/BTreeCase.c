#include "BTreeCase.h"

#include "BTree/BTree.h"
#include <stdio.h>

typedef struct
{
    BTreeNode header;
    char v;
}Node;

void printfNode(BTreeNode* btNode)
{
    Node* node = (Node*)btNode;

    if (node != NULL) {
        printf("%c", node->v);
    }
}

void BTreeCase()
{
    BTree* tree = BTree_Create();
    Node a = {{NULL, NULL}, 'A'};
    Node b = {{NULL, NULL}, 'B'};
    Node c = {{NULL, NULL}, 'C'};
    Node d = {{NULL, NULL}, 'D'};
    Node e = {{NULL, NULL}, 'E'};
    Node f = {{NULL, NULL}, 'F'};

    BTree_Insert(tree, (BTreeNode*)&a, 0, 0, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&b, 0x0, 1, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&c, 0x1, 1, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&d, 0x0, 2, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&e, 0x2, 2, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&f, 0x2, 3, BT_LEFT);

    BTree_Display(tree, printfNode);

    printf("count = %d\n", BTree_Count(tree));
    printf("height = %d\n", BTree_Height(tree));
    printf("degree = %d\n", BTree_Degree(tree));

    printf("after ***********\n");


    printf("get node = ");
    printfNode(BTree_Get(tree, 0x2, 3));
    printf("\n");
    printf("delete node = ");
    printfNode(BTree_Delete(tree, 0x0, 1));
    printf("\n");
    printf("count = %d\n", BTree_Count(tree));
    printf("root = ");
    printfNode(BTree_Root(tree));
    printf("\n");
    printf("height = %d\n", BTree_Height(tree));
    printf("degree = %d\n", BTree_Degree(tree));
    BTree_Display(tree, printfNode);

    BTree_Destroy(tree);
}
