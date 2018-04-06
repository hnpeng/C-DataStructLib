#include "BTree.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int count;
    BTreeNode* root;
}TBTree;

BTree* BTree_Create()
{
    TBTree* ret = (TBTree*)malloc(sizeof(TBTree));

    if (ret != NULL) {
        ret->count = 0;
        ret->root = NULL;
    }

    return ret;
}

void BTree_Clear(BTree* tree)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        btree->count = 0;
        btree->root = NULL;
    }
}


void BTree_Destroy(BTree* tree)
{
    free(tree);
}

int BTree_Insert(BTree* tree, BTreeNode* node, BTPos pos, int count, BtFlag flag)
{
    TBTree* btree = (TBTree*)tree;
    int ret = btree != NULL && node != NULL;

    if (ret) {
        BTreeNode* current = btree->root;
        BTreeNode* parent = NULL;
        int bit = 0;

        node->leftNode = NULL;
        node->rightNode = NULL;

        while (current != NULL && count > 0) {
            bit = pos & 1;
            pos >>= 1;

            parent = current;

            if (bit == BT_LEFT)
                current = current->leftNode;
            else if (bit == BT_RIGHT)
                current = current->rightNode;

            count--;
        }

        if (flag == BT_LEFT)
            node->leftNode = current;
        else if (flag == BT_RIGHT)
            node->rightNode = current;

        if (parent != NULL) {
            if (bit == BT_LEFT)
                parent->leftNode = node;
            else if (bit == BT_RIGHT)
                parent->rightNode = node;
        } else {
            btree->root = node;
        }

        btree->count++;
    }

    return ret;
}

static int recursive_count(BTreeNode* root)
{
    int ret = 0;

    if (root != NULL) {
        ret = 1 + recursive_count(root->leftNode) + recursive_count(root->rightNode);
    }

    return ret;
}

BTreeNode* BTree_Delete(BTree* tree, BTPos pos, int count)
{
    TBTree* btree = (TBTree*)tree;
    BTreeNode* ret = NULL;

    if (btree != NULL) {
        BTreeNode* current = btree->root;
        BTreeNode* parent = NULL;
        int bit;

        while (current != NULL && count > 0) {
            bit = pos & 1;
            pos >>= 1;

            parent = current;

            if (bit == BT_LEFT)
                current = current->leftNode;
            else if (bit == BT_RIGHT)
                current = current->rightNode;
            count--;
        }

        if (parent != NULL) {
            if (bit == BT_LEFT)
                parent->leftNode = NULL;
            else if (bit == BT_RIGHT)
                parent->rightNode = NULL;
        }

        ret = current;
        btree->count -= recursive_count(ret);
    }

    return ret;
}

BTreeNode* BTree_Get(BTree* tree, BTPos pos, int count)
{
    BTreeNode* ret = NULL;
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        BTreeNode* current = btree->root;
        int bit;

        while (count > 0 && current != NULL) {
            bit = pos & 1;
            pos >>= 1;

            if (bit == BT_LEFT)
                current = current->leftNode;
            else if (bit == BT_RIGHT)
                current = current->rightNode;

            count--;
        }

        ret = current;
    }

    return ret;
}

int BTree_Count(BTree* tree)
{
    int ret = -1;
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        ret = btree->count;
    }

    return ret;
}

BTreeNode* BTree_Root(BTree* tree)
{
    BTreeNode* ret = NULL;
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        ret = btree->root;
    }

    return ret;
}

static int recursive_height(BTreeNode* root)
{
    int ret = 0;

    if (root != NULL) {
        int lh = recursive_height(root->leftNode);
        int rh = recursive_height(root->rightNode);

        ret = lh > rh ? lh : rh;
        ret += 1;
    }

    return ret;
}

int BTree_Height(BTree* tree)
{
    int ret = -1;
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        ret = recursive_height(btree->root);
    }

    return ret;
}

static int recursive_degree(BTreeNode* root)
{
    int ret = 0;

    if (root != NULL) {
        ret = 1;

        if (root->leftNode != NULL && root->rightNode != NULL) {
            ret = 2;
        } else {
            int ld = recursive_degree(root->leftNode);
            int rd = recursive_degree(root->rightNode);

            if (ld == 2 || rd == 2) {
                ret =2;
            }
        }
    }

    return ret;
}

int BTree_Degree(BTree* tree)
{
    int ret = -1;
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        ret = recursive_degree(btree->root);
    }

    return ret;
}

static void recursive_display(BTreeNode* root, int format, PrintFunc pFunc)
{
    int i;

    if (root != NULL && pFunc != NULL) {
        for (i=0; i<format; i++) {
            printf("-");
        }

        pFunc(root);
        printf("\n");

        if (root->leftNode != NULL || root->rightNode != NULL) {
            recursive_display(root->leftNode, format + 2, pFunc);
            recursive_display(root->rightNode, format + 2, pFunc);
        }
    } else {
        for (i=0; i<format; i++) {
            printf("-");
        }

        printf("\n");
    }
}

void BTree_Display(BTree* tree, PrintFunc printFunc)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        recursive_display(btree->root, 0, printFunc);
    }
}
