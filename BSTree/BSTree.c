#include "BSTree.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int count;
    BSTreeNode* root;
}TBSTree;

BSTree* BSTree_Create()
{
    TBSTree* ret = (TBSTree*)malloc(sizeof(TBSTree));

    if (ret != NULL) {
        ret->count = 0;
        ret->root = NULL;
    }

    return ret;
}

void BSTree_Clear(BSTree* tree)
{
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL) {
        btree->count = 0;
        btree->root = NULL;
    }
}

void BSTree_Destroy(BSTree* tree)
{
    free(tree);
}

static int recursive_insert(BSTreeNode* root, BSTreeNode* node, BSTree_Compare* compare)
{
    int ret = 1;

    if (root != NULL) {
        int r = compare(node->key, root->key);

        if (r == 0) {
            ret = 0;
        } else if (r < 0) {
            if (root->left == NULL) {
                root->left = node;
            } else {
                ret = recursive_insert(root->left, node, compare);
            }
        } else if (r > 0) {
            if (root->right == NULL) {
                root->right = node;
            } else {
                ret = recursive_insert(root->right, node, compare);
            }
        }
    }

    return ret;
}

int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare)
{
    TBSTree* btree = (TBSTree*)tree;
    int ret = btree != NULL && node != NULL && compare != NULL;

    if (ret) {
        node->left= NULL;
        node->right= NULL;

        if (btree->root == NULL) {
            btree->root = node;
        } else {
            ret = recursive_insert(btree->root, node, compare);
        }

        if (ret) {
            btree->count++;
        }
    }

    return ret;
}

static BSTreeNode* delete_node(BSTreeNode** pRoot)
{
    BSTreeNode* ret = *pRoot;

    if ((*pRoot)->right == NULL) {
        *pRoot = (*pRoot)->left;
    } else if ((*pRoot)->left == NULL) {
        *pRoot = (*pRoot)->right;
    } else {
        BSTreeNode* g = *pRoot;
        BSTreeNode* c = (*pRoot)->left;

        while (c->right != NULL) {
            g = c;
            c = c->right;
        }

        if (g != *pRoot)
            g->right = c->left;
        else
            g->left = c->left;

        c->left = (*pRoot)->left;
        c->right = (*pRoot)->right;

        *pRoot = c;
    }

    return ret;
}

static BSTreeNode* recursive_delete(BSTreeNode** pRoot, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;

    if (pRoot != NULL && *pRoot != NULL) {
        int r = compare(key, (*pRoot)->key);

        if (r == 0) {
            ret = delete_node(pRoot);
        } else if (r < 0) {
            ret = recursive_delete(&((*pRoot)->left), key, compare);
        } else {
            ret = recursive_delete(&((*pRoot)->right), key, compare);
        }
    }

    return ret;
}

BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL && key != NULL && compare != NULL) {
        ret = recursive_delete(&(btree->root), key, compare);

        if (ret != NULL) {
            btree->count--;
        }
    }

    return ret;
}

static BSTreeNode* recursive_get(BSTreeNode* root, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;

    if (root != NULL) {
        int r = compare(key, root->key);

        if (r == 0) {
            ret = root;
        } else if (r < 0) {
            ret = recursive_get(root->left, key, compare);
        } else {
            ret = recursive_get(root->right, key, compare);
        }
    }

    return ret;
}

BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare)
{
    BSTreeNode* ret = NULL;
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL && key != NULL && compare != NULL) {
        ret = recursive_get(btree->root, key, compare);
    }

    return ret;
}

BSTreeNode* BSTree_Root(BSTree* tree)
{
    BSTreeNode* ret = NULL;
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL) {
        ret = btree->root;
    }

    return ret;
}

int BSTree_Count(BSTree* tree)
{
    int ret = -1;
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL) {
        ret = btree->count;
    }

    return ret;
}

static int recursive_height(BSTreeNode* root)
{
    int ret = 0;

    if (root != NULL) {
        int lh = recursive_height(root->left);
        int rh = recursive_height(root->right);

        ret = lh > rh ? lh : rh;
        ret += 1;
    }

    return ret;
}

int BSTree_Height(BSTree* tree)
{
    int ret = -1;
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL) {
        ret = recursive_height(btree->root);
    }

    return ret;
}

static int recursive_degree(BSTreeNode* root)
{
    int ret = 0;

    if (root != NULL) {
        if (root->left != NULL) {
            ret++;
        }

        if (root->right != NULL) {
            ret++;
        }

        if (ret == 1) {
            int ld = recursive_degree(root->left);
            int rd = recursive_degree(root->right);

            if (ld > ret)
                ret = ld;
            if (rd > ret)
                ret = rd;
        }
    }

    return ret;
}

int BSTree_Degree(BSTree* tree)
{
    int ret = 0;
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL) {
       ret = recursive_degree(btree->root);
    }

    return ret;
}

static void recursive_display(BSTreeNode* root, int format, BSTree_Print* pFunc)
{
    int i;

    if (root != NULL) {
        int i;
        for (i=0; i<format; i++) {
            printf("-");
        }
        pFunc(root);
        printf("\n");
        if (root->left != NULL || root->right != NULL) {
            recursive_display(root->left, format + 4, pFunc);
            recursive_display(root->right, format + 4, pFunc);
        }
    } else {
        for (i=0; i<format; i++) {
            printf("-");
        }
        printf("\n");
    }
}

void BSTree_Display(BSTree *tree, BSTree_Print* pFunc)
{
    TBSTree* btree = (TBSTree*)tree;

    if (btree != NULL && pFunc != NULL) {
        recursive_display(btree->root, 0, pFunc);
    }
}
