#ifndef BTREE_H
#define BTREE_H

#include <LinkList/LinkList.h>

typedef void BTree;
typedef unsigned long long BTPos;

typedef struct _tag_BTreeNode BTreeNode;
struct _tag_BTreeNode
{
    BTreeNode* leftNode;
    BTreeNode* rightNode;
};

typedef void (*PrintFunc)(BTreeNode* node);
typedef int (*CompareValFunc)(BTreeNode* n1, BTreeNode* n2);

typedef enum
{
    BT_LEFT,
    BT_RIGHT
}BtFlag;

BTree* BTree_Create();

void BTree_Clear(BTree* tree);

void BTree_Destroy(BTree* tree);

int BTree_Insert(BTree* tree, BTreeNode* node, BTPos pos, int count, BtFlag flag);

BTreeNode* BTree_Delete(BTree* tree, BTPos pos, int count);

BTreeNode* BTree_Get(BTree* tree, BTPos pos, int count);

int BTree_Count(BTree* tree);

BTreeNode* BTree_Root(BTree* tree);

int BTree_Height(BTree* tree);

int BTree_Degree(BTree* tree);

void BTree_Display(BTree* tree, PrintFunc printFunc);

void BTree_PreOrderTraversal(BTree* tree, PrintFunc pFunc);

void BTree_MidOrderTraversal(BTree* tree, PrintFunc pFunc);

void BTree_PostOrderTraversal(BTree* tree, PrintFunc pFunc);

void BTree_LevelOrderTraversal(BTree* tree, PrintFunc pFunc);

void BTree_ThreadViaLeft(BTree* tree);

void BTree_ThreadViaPre(BTree* tree, LinkList* list);

int BTree_Compare(BTree* tree1, BTree* tree2, CompareValFunc isValEqualFunc);

void BTree_DeleteSingleDegree(BTree* tree);

#endif
