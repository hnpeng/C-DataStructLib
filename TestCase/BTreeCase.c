#include "BTreeCase.h"

#include "BTree/BTree.h"
#include "LinkList/LinkList.h"
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

int equalFunc(BTreeNode* bn1, BTreeNode* bn2)
{
    Node* n1 = (Node*)bn1;
    Node* n2 = (Node*)bn2;
    int ret = n1 != NULL && n2 != NULL;

    if (ret) {
        ret = n1->v == n2->v;
    }

    return ret;
}

void BTreeCase()
{
    BTree* tree = BTree_Create();
    BTree* tree2 = BTree_Create();
    BTree* tree3 = BTree_Create();
    Node a = {{NULL, NULL}, 'A'};
    Node b = {{NULL, NULL}, 'B'};
    Node c = {{NULL, NULL}, 'C'};
    Node d = {{NULL, NULL}, 'D'};
    Node e = {{NULL, NULL}, 'E'};
    Node f = {{NULL, NULL}, 'F'};

    Node A = {{NULL, NULL}, 'A'};
    Node B = {{NULL, NULL}, 'B'};
    Node C = {{NULL, NULL}, 'C'};
    Node D = {{NULL, NULL}, 'D'};
    Node E = {{NULL, NULL}, 'E'};
    Node F = {{NULL, NULL}, 'F'};

    Node n0 = {{NULL, NULL}, '0'};
    Node n1 = {{NULL, NULL}, '1'};
    Node n2 = {{NULL, NULL}, '2'};
    Node n3 = {{NULL, NULL}, '3'};
    Node n4 = {{NULL, NULL}, '4'};
    Node n5 = {{NULL, NULL}, '5'};
    Node n6 = {{NULL, NULL}, '6'};
    Node n7 = {{NULL, NULL}, '7'};
    Node n8 = {{NULL, NULL}, '8'};

    BTree_Insert(tree, (BTreeNode*)&a, 0, 0, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&b, 0x0, 1, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&c, 0x1, 1, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&d, 0x0, 2, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&e, 0x2, 2, BT_LEFT);
    BTree_Insert(tree, (BTreeNode*)&f, 0x2, 3, BT_LEFT);

    BTree_Insert(tree2, (BTreeNode*)&A, 0x0, 0, BT_LEFT);
    BTree_Insert(tree2, (BTreeNode*)&B, 0x0, 1, BT_LEFT);
    BTree_Insert(tree2, (BTreeNode*)&C, 0x2, 2, BT_LEFT);
    BTree_Insert(tree2, (BTreeNode*)&D, 0x0, 2, BT_LEFT);
    BTree_Insert(tree2, (BTreeNode*)&E, 0x0, 3, BT_LEFT);
    BTree_Insert(tree2, (BTreeNode*)&F, 0x4, 3, BT_LEFT);

    BTree_Insert(tree3, (BTreeNode*)&n0, 0x0, 0, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n1, 0x0, 1, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n2, 0x1, 1, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n3, 0x0, 2, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n4, 0x1, 2, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n5, 0x3, 2, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n6, 0x4, 3, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n7, 0x1, 3, BT_LEFT);
    BTree_Insert(tree3, (BTreeNode*)&n8, 0x3, 3, BT_LEFT);

    printf("equal = %d\n", BTree_Compare(tree, tree2, equalFunc));

    BTree_Display(tree3, printfNode);
    printf("\n");
    BTree_DeleteSingleDegree(tree3);
    BTree_Display(tree3, printfNode);
    printf("\n");

    BTree_Display(tree, printfNode);
    printf("\n");
    BTree_Display(tree2, printfNode);

    printf("count = %d\n", BTree_Count(tree));
    printf("height = %d\n", BTree_Height(tree));
    printf("degree = %d\n", BTree_Degree(tree));

    BTree_PreOrderTraversal(tree, printfNode);
    printf("\n");
//    BTree_PreOrderTraversal(tree2, printfNode);
//    printf("\n");
    BTree_MidOrderTraversal(tree, printfNode);
    printf("\n");
    BTree_PostOrderTraversal(tree, printfNode);
    printf("\n");
    BTree_LevelOrderTraversal(tree, printfNode);
    printf("\n");

//    LinkList* list = LinkList_Create();
//    BTree_ThreadViaPre(tree, list);
//    int i;
//    for (i=0; i<LinkList_Length(list); i++) {
//        printfNode((BTreeNode*)LinkList_Get(list, i));
//    }
//    LinkList_Destroy(list);

//    BTree_ThreadViaLeft(tree);
//    BTreeNode* current = (BTreeNode*)BTree_Root(tree);

//    while (current != NULL) {
//        printfNode(current);
//        current = current->leftNode;
//    }

    printf("\n");

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
    BTree_Destroy(tree2);
    BTree_Destroy(tree3);
}
