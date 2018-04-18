#ifndef BSTREE_H
#define BSTREE_H

typedef void BSTree;
typedef void BSKey;

typedef struct _tag_bsTreeNode BSTreeNode;
struct _tag_bsTreeNode
{
    BSKey* key;
    BSTreeNode* left;
    BSTreeNode* right;
};

typedef int (BSTree_Compare)(BSKey*, BSKey*);
typedef void (BSTree_Print)(BSTreeNode*);

BSTree* BSTree_Create();

void BSTree_Clear(BSTree* tree);

void BSTree_Destroy(BSTree* tree);

int BSTree_Insert(BSTree* tree, BSTreeNode* node, BSTree_Compare* compare);

BSTreeNode* BSTree_Delete(BSTree* tree, BSKey* key, BSTree_Compare* compare);

BSTreeNode* BSTree_Get(BSTree* tree, BSKey* key, BSTree_Compare* compare);

BSTreeNode* BSTree_Root(BSTree* tree);

int BSTree_Count(BSTree* tree);

int BSTree_Height(BSTree* tree);

int BSTree_Degree(BSTree* tree);

void BSTree_Display(BSTree* tree, BSTree_Print* pFunc);

#endif
