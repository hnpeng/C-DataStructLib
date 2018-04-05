#include "GTree.h"

#include "LinkList/LinkList.h"
#include "LinkStack/LinkStack.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct _tag_GTreeNode GTreeNode;
struct _tag_GTreeNode
{
    GTreeData* data;
    GTreeNode* parent;
    LinkList* children;
};

GTree* GTree_Create()
{
    return LinkList_Create();
}

void GTree_Clear(GTree* tree)
{
    GTree_Delete(tree, 0);
}

void GTree_Destroy(GTree* tree)
{
    GTree_Clear(tree);
    LinkList_Destroy((LinkList*)tree);
}

int GTree_Insert(GTree* tree, GTreeData* data, int pPos)
{
    LinkList* list = (LinkList*)tree;
    int ret = list != NULL && data != NULL && pPos < LinkList_Length(list);

    if (ret) {
        GTreeNode* trNode = (GTreeNode*)malloc(sizeof(GTreeNode));
        GTreeNode* pNode = (GTreeNode*)LinkList_Get(list, pPos);

        ret = trNode != NULL;

        if (ret) {

            ret = LinkList_Insert(list, trNode, LinkList_Length(list));

            if (ret) {
                trNode->data = data;
                trNode->children = LinkList_Create();
                trNode->parent = pNode;

                if (pNode != NULL) {
                        ret = LinkList_Insert(pNode->children, trNode, LinkList_Length(pNode->children));
                }

                if (!ret) {
                    LinkList_Destroy(trNode->children);
                    LinkList_Delete(list, LinkList_Length(list) - 1);
                    free(trNode);
                }

            } else {
                free(trNode);
            }
        }
    }

    return ret;
}

static void recursive_delete(LinkList* trList, GTreeNode* node)
{
    if (node != NULL) {
        int i;
        GTreeNode* pNode = node->parent;

        if (pNode != NULL) {
            for (i=0; i<LinkList_Length(pNode->children); i++) {
                if ((GTreeNode*)LinkList_Get(pNode->children, i) == node) {
                    LinkList_Delete(pNode->children, i);
                    break;
                }
            }
        }

        for (i=0; i<LinkList_Length(trList); i++) {
            if ((GTreeNode*)LinkList_Get(trList, i) == node) {
                LinkList_Delete(trList, i);
                break;
            }
        }

        while (LinkList_Length(node->children) > 0) {
            GTreeNode* child = (GTreeNode*)LinkList_Get(node->children, 0);

            recursive_delete(trList, child);
        }

        LinkList_Destroy(node->children);

        free(node);
    }
}

GTreeData* GTree_Delete(GTree* tree, int pos)
{
    LinkList* list = (LinkList*)tree;
    GTreeNode* node = (GTreeNode*)LinkList_Get(list, pos);
    GTreeData* ret = NULL;

    if (list != NULL && node != NULL) {
        ret = node->data;
        recursive_delete(list, node);
    }

    return ret;
}

GTreeData* GTree_Get(GTree* tree, int pos)
{
    LinkList* list = (LinkList*)tree;
    GTreeNode* node = (GTreeNode*)LinkList_Get(list, pos);
    GTreeData* ret = NULL;

    if (node != NULL) {
        ret = node->data;
    }

    return ret;
}

int GTree_Count(GTree* tree)
{
    return LinkList_Length((LinkList*)tree);
}

GTreeData* GTree_Root(GTree* tree)
{
    return GTree_Get(tree, 0);
}

static int recursive_height(GTreeNode* node)
{
    int ret = 0;

    if (node != NULL) {
        int i = 0;
        int cldHight;

        for (i=0; i<LinkList_Length(node->children); i++) {
            GTreeNode* cldNode = (GTreeNode*)LinkList_Get(node->children, i);

            cldHight = recursive_height(cldNode);

            if (cldHight > ret) {
                ret = cldHight;
            }
        }

        ret += 1;
    }

    return ret;
}

int GTree_Hight(GTree* tree)
{
    LinkList* list = (LinkList*)tree;
    int ret = -1;

    if (list != NULL) {
        GTreeNode* node = (GTreeNode*)LinkList_Get(list, 0);

        ret = recursive_height(node);
    }

    return ret;
}

static int recursive_degree(GTreeNode* node)
{
    int ret = 0;

    if (node != NULL) {
        int i;
        int cldDegree;

        ret = LinkList_Length(node->children);

        for (i=0; i<LinkList_Length(node->children); i++) {
            GTreeNode* cldNode = (GTreeNode*)LinkList_Get(node->children, i);

            cldDegree = recursive_degree(cldNode);

            if (ret < cldDegree) {
                ret = cldDegree;
            }
        }
    }

    return ret;
}

int GTree_Degree(GTree* tree)
{
    LinkList* list = (LinkList*)tree;
    int ret = -1;

    if (list != NULL) {
        GTreeNode* node = (GTreeNode*)LinkList_Get(list, 0);

        ret = recursive_degree(node);
    }

    return ret;
}

static void recursive_display(GTreeNode* node, int format, PrintFunc printFunc)
{
    if (node != NULL) {
        int i;

        for (i=0; i<format; i++) {
            printf("-");
        }

        printFunc(node->data);
        printf("\n");

        for (i=0; i<LinkList_Length(node->children); i++) {
            GTreeNode* child = (GTreeNode*)LinkList_Get(node->children, i);

            recursive_display(child, format + 2, printFunc);
        }
    }
}

void GTree_Display(GTree* tree, PrintFunc printFunc)
{
    LinkList* list = (LinkList*)tree;
    GTreeNode* node = (GTreeNode*)LinkList_Get(list, 0);

    if (node != NULL && printFunc != NULL)
        recursive_display(node, 0, printFunc);
}

static void recursive_search(GTreeNode* node, GTreeData* data, PrintFunc pFunc, LinkStack* stack)
{
    if (node != NULL) {
        LinkStack_Push(stack, node->data);
        if (node->data == data) {
            while (LinkStack_Size(stack) > 0) {
                pFunc(LinkStack_Pop(stack));
            }
            printf("\n");
        } else {
            int i;

            for (i=0; i<LinkList_Length(node->children); i++) {
                GTreeNode* cldNode = (GTreeNode*)LinkList_Get(node->children, i);

                recursive_search(cldNode, data, pFunc, stack);
            }
        }
        LinkStack_Pop(stack);
    }
}

void GTree_Search(GTree *tree, GTreeData *data, PrintFunc printFunc)
{
    GTreeNode* trNode = (GTreeNode*)LinkList_Get(tree, 0);

    if (trNode != NULL && data != NULL) {
        LinkStack* stack = LinkStack_Create();

        recursive_search(trNode, data, printFunc, stack);

        LinkStack_Destroy(stack);
    }

}
