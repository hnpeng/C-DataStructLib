#include "BTree.h"

#include <stdlib.h>
#include <stdio.h>
#include <LinkQueue/LinkQueue.h>

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
        if (root->leftNode != NULL) {
            ret++;
        }

        if (root->rightNode != NULL) {
            ret++;
        }

        if (ret == 1) {
            int ld = recursive_degree(root->leftNode);
            int rd = recursive_degree(root->rightNode);

            if (ld > ret)
                ret = ld;
            if (rd > ret)
                ret = rd;
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

static void pre_order_traversal(BTreeNode* root, PrintFunc pFunc)
{
    if (root != NULL && pFunc != NULL) {
        pFunc(root);
        printf(" ");
        pre_order_traversal(root->leftNode, pFunc);
        pre_order_traversal(root->rightNode, pFunc);
    }
}

void BTree_PreOrderTraversal(BTree* tree, PrintFunc pFunc)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        pre_order_traversal(btree->root, pFunc);
    }
}

static void mid_order_traversal(BTreeNode* root, PrintFunc pFunc)
{
    if (root != NULL) {
        mid_order_traversal(root->leftNode, pFunc);
        pFunc(root);
        printf(" ");
        mid_order_traversal(root->rightNode, pFunc);
    }
}

void BTree_MidOrderTraversal(BTree* tree, PrintFunc pFunc)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        mid_order_traversal(btree->root, pFunc);
    }
}

static void post_order_traversal(BTreeNode* root, PrintFunc pFunc)
{
    if (root != NULL) {
        post_order_traversal(root->leftNode, pFunc);
        post_order_traversal(root->rightNode, pFunc);
        pFunc(root);
        printf(" ");
    }
}

void BTree_PostOrderTraversal(BTree* tree, PrintFunc pFunc)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        post_order_traversal(btree->root, pFunc);
    }
}

void BTree_LevelOrderTraversal(BTree* tree, PrintFunc pFunc)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL && btree->root != NULL) {
        LinkQueue* queue = LinkQueue_Create();

        LinkQueue_Append(queue, btree->root);

        while (LinkQueue_Length(queue) > 0) {
            BTreeNode* node = (BTreeNode*)LinkQueue_Retrieve(queue);
            pFunc(node);
            printf(" ");

            if (node->leftNode != NULL) {
                LinkQueue_Append(queue, node->leftNode);
            }

            if (node->rightNode != NULL) {
                LinkQueue_Append(queue, node->rightNode);
            }
        }

        LinkQueue_Destroy(queue);
    }
}

static void thread_via_left(BTreeNode* root, BTreeNode** pp)
{
    if (root != NULL && pp != NULL) {
        if (*pp != NULL) {
            (*pp)->leftNode = root;
            *pp = NULL;
        }

        if (root->leftNode == NULL) {
            *pp = root;
        }

        thread_via_left(root->leftNode, pp);
        thread_via_left(root->rightNode, pp);
    }
}

void BTree_ThreadViaLeft(BTree *tree)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {

        BTreeNode* p = NULL;
        thread_via_left(btree->root, &p);
    }
}

static void thread_via_pre(BTreeNode* root, LinkList* list)
{
    if (root != NULL && list != NULL) {
        LinkList_Insert(list, root, LinkList_Length(list));
        thread_via_pre(root->leftNode, list);
        thread_via_pre(root->rightNode, list);
    }
}

void BTree_ThreadViaPre(BTree *tree, LinkList *list)
{
    TBTree* btree = (TBTree*)tree;

    if (tree != NULL && list != NULL) {
        thread_via_pre(btree->root, list);
    }
}

static int compare_bin_tree(BTreeNode* bt1, BTreeNode* bt2, CompareValFunc isValEqualFucn)
{
    int ret = 1;

    if (bt1 != NULL || bt2 != NULL) {
        ret = isValEqualFucn(bt1, bt2) &&
                compare_bin_tree(bt1->leftNode, bt2->leftNode, isValEqualFucn) &&
                compare_bin_tree(bt1->rightNode, bt2->rightNode, isValEqualFucn);
    }

    return ret;
}

int BTree_Compare(BTree *tree1, BTree *tree2, CompareValFunc isValEqualFunc)
{
    TBTree* bt1 = (TBTree*)tree1;
    TBTree* bt2 = (TBTree*)tree2;
    int ret = bt1 != NULL && bt2 != NULL;

    if (ret) {
        ret = compare_bin_tree(bt1->root, bt2->root, isValEqualFunc);
    }

    return ret;
}

static void deleteSingleDegree(BTreeNode** root)
{
    if (*root != NULL) {
        deleteSingleDegree(&(*root)->leftNode);
        deleteSingleDegree(&(*root)->rightNode);

        if ((*root)->leftNode == NULL && (*root)->rightNode != NULL) {
            (*root) = (*root)->rightNode;
        }

        if ((*root)->leftNode != NULL && (*root)->rightNode == NULL) {
            (*root) = (*root)->leftNode;
        }
    }
}

void BTree_DeleteSingleDegree(BTree *tree)
{
    TBTree* btree = (TBTree*)tree;

    if (btree != NULL) {
        deleteSingleDegree(&btree->root);
    }
}
