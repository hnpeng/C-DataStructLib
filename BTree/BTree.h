#ifndef BTREE_H
#define BTREE_H

typedef void BTree;
typedef unsigned long long BTPos;

typedef struct _tag_BTreeNode BTreeNode;
struct _tag_BTreeNode
{
    BTreeNode* leftNode;
    BTreeNode* rightNode;
};

typedef void (*PrintFunc)(BTreeNode* node);

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

#endif
