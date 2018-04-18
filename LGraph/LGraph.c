#include "LGraph.h"

#include "LinkList/LinkList.h"
#include "LinkQueue/LinkQueue.h"
#include "LinkStack/LinkStack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int count;
    LVertex* v;
    LinkList** listArr;
}TLGraph;

typedef struct
{
    int v;
    int w;
}TListNode;

LGraph* LGraph_Create(LVertex* v, int n)
{
    TLGraph* ret = (TLGraph*)malloc(sizeof(TLGraph));
    int ok = 1;

    if (ret != NULL) {
        int i;

        ret->count = n;
        ret->v = (LVertex*)malloc(sizeof(LVertex) * n);
        ret->listArr = (LinkList**)calloc(n, sizeof(LinkList*));
        ok = ret->v != NULL && ret->listArr != NULL;

        for (i=0; i<n && ok; i++) {
            ok = ok && ((ret->listArr[i] = LinkList_Create()) != NULL);
        }

        if (ok) {
            for (i=0; i<n; i++) {
                ret->v[i] = v[i];
            }
        } else {
            if (ret->listArr != NULL) {
                for (i=0; i<n; i++) {
                    LinkList_Destroy(ret->listArr[i]);
                }
            }

            free(ret->listArr);
            free(ret->v);
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

void LGraph_Clear(LGraph* graph)
{
    TLGraph* tGraph = (TLGraph*)graph;

    if (tGraph != NULL) {
        int i;

        for (i=0; i<tGraph->count; i++) {
            while (LinkList_Length(tGraph->listArr[i]) > 0) {
                TListNode* tNode = LinkList_Delete(tGraph->listArr[i], 0);
                free(tNode);
            }
        }
    }
}

void LGraph_Destroy(LGraph* graph)
{
    TLGraph* tGraph = (TLGraph*)graph;

    if (tGraph != NULL) {
        int i;

        LGraph_Clear(tGraph);
        for (i=0; i<tGraph->count; i++) {
            LinkList_Destroy(tGraph->listArr[i]);
        }

        free(tGraph->listArr);
        free(tGraph->v);
        free(tGraph);
    }
}

int LGraph_AddEdge(LGraph* graph, int v1, int v2, int w)
{
    TLGraph* tGraph = (TLGraph*)graph;
    int ret = tGraph != NULL && w > 0;
    TListNode* node = NULL;

    ret = ret && 0 <= v1 && v1 < tGraph->count;
    ret = ret && 0 <= v2 && v2 < tGraph->count;
    ret = ret && (node = (TListNode*)malloc(sizeof(TListNode))) != NULL;

    if (ret) {

        node->v = v2;
        node->w = w;
        ret = LinkList_Insert(tGraph->listArr[v1], node, 0);

        if (!ret) {
            free(node);
        }
    }

    return ret;
}

int LGraph_RemoveEdge(LGraph* graph, int v1, int v2)
{
    int ret = 0;
    TLGraph* tGraph = (TLGraph*)graph;
    int condiction = tGraph != NULL;

    condiction = condiction && 0 <= v1 && v1 < tGraph->count;
    condiction = condiction && 0 <= v2 && v2 < tGraph->count;

    if (condiction) {
        int i;

        for (i=0; i<LinkList_Length(tGraph->listArr[v1]); i++) {
            TListNode* node = LinkList_Get(tGraph->listArr[v1], i);

            if (node->v == v2) {
                ret = node->w;
                LinkList_Delete(tGraph->listArr[v1], i);
                free(node);
                break;
            }
        }
    }

    return ret;
}

int LGraph_GetEdge(LGraph* graph, int v1, int v2)
{
    int ret = 0;
    TLGraph* tGraph = (TLGraph*)graph;
    int condiction = tGraph != NULL;

    condiction = condiction && 0 <= v1 && v1 < tGraph->count;
    condiction = condiction && 0 <= v2 && v2 < tGraph->count;

    if (condiction) {
        int i;

        for (i=0; i<LinkList_Length(tGraph->listArr[v1]); i++) {
            TListNode* node = LinkList_Get(tGraph->listArr[v1], i);

            if (node->v == v2) {
                ret = node->w;
                break;
            }
        }
    }

    return ret;
}

int LGraph_TD(LGraph* graph, int v)
{
    int ret = 0;
    TLGraph* tGraph = (TLGraph*)graph;

    if (tGraph != NULL && 0 <= v && v < tGraph->count) {
        int i;
        int j;

        for (i=0; i<tGraph->count; i++) {
            for (j=0; j<LinkList_Length(tGraph->listArr[i]); j++) {
                TListNode* node = (TListNode*)LinkList_Get(tGraph->listArr[i], j);

                if (node->v == v)
                    ret += 1;
            }
        }

        ret += LinkList_Length(tGraph->listArr[v]);
    }

    return ret;
}

int LGraph_VertexCount(LGraph* graph)
{
    int ret = 0;
    TLGraph* tGraph = (TLGraph*)graph;

    if (tGraph != NULL) {
        ret = tGraph->count;
    }

    return ret;
}

int LGraph_EdgeCount(LGraph* graph)
{
    int ret = 0;
    TLGraph* tGraph = (TLGraph*)graph;

    if (tGraph != NULL) {
        int i;

        for (i=0; i<tGraph->count; i++) {
            ret += LinkList_Length(tGraph->listArr[i]);
        }
    }

    return ret;
}

void LGraph_Display(LGraph* graph, PFunc* pFunc)
{
    TLGraph* tGraph = (TLGraph*)graph;

    if (tGraph != NULL) {
        int i, j;
        for (i=0; i<tGraph->count; i++) {
            printf("%d:", i);
            pFunc(tGraph->v[i]);
            printf("\t");
        }

        printf("\n");

        for (i=0; i<tGraph->count; i++) {
            for (j=0; j<LinkList_Length(tGraph->listArr[i]); j++) {
                TListNode* node = (TListNode*)LinkList_Get(tGraph->listArr[i], j);
                printf("<");
                pFunc(tGraph->v[i]);
                printf(", %d, ", node->w);
                pFunc(tGraph->v[node->v]);
                printf("> ");
            }
        }
        printf("\n");
    }
}

static void recursive_dfs(TLGraph* tGraph, int v, int* validArr, PFunc* pFunc)
{
    pFunc(tGraph->v[v]);
    printf("\t");
    validArr[v] = 1;
    int i;

    for (i=0; i<LinkList_Length(tGraph->listArr[v]); i++) {
        TListNode* node = LinkList_Get(tGraph->listArr[v], i);

        if (!validArr[node->v]) {
            recursive_dfs(tGraph, node->v, validArr, pFunc);
        }
    }

}

static void dfs(TLGraph* tGraph, int v, int validArr[], PFunc* pFunc)
{
    LinkStack* stack = LinkStack_Create();

    if (stack != NULL) {
        int i;
        LinkStack_Push(stack, tGraph->v + v);
        validArr[v] = 1;

        while (LinkStack_Size(stack) > 0) {
            int n = (LVertex*)LinkStack_Pop(stack) - tGraph->v;
            pFunc(tGraph->v[n]);
            printf("\t");

            for (i=0; i<LinkList_Length(tGraph->listArr[n]); i++) {
                TListNode* node = (TListNode*)LinkList_Get(tGraph->listArr[n], i);
                if (!validArr[node->v]) {
                    LinkStack_Push(stack, node->v + tGraph->v);
                    validArr[node->v] = 1;
                }
            }
        }
    }

    LinkList_Destroy(stack);
}

void LGraph_DFS(LGraph *graph, PFunc *pFunc)
{
    TLGraph* tGraph = (TLGraph*)graph;
    int* validArr = (int*)calloc(tGraph->count, sizeof(int));

    if (tGraph != NULL && pFunc != NULL && validArr != NULL) {
        int i;

//        recursive_dfs(tGraph, 0, validArr, pFunc);
        dfs(tGraph, 0, validArr, pFunc);

        for (i=0; i<tGraph->count; i++) {
            if (!validArr[i]) {
                dfs(tGraph, i, validArr, pFunc);
            }
        }
    }
    printf("\n");

    free(validArr);
}

static void bfs(TLGraph* tGraph, int v, int validArr[], PFunc* pFunc)
{
    LinkQueue* queue = LinkQueue_Create();
    int i;

    LinkQueue_Append(queue, tGraph->v + v);
    validArr[v] = 1;

    while (LinkQueue_Length(queue) > 0) {
        int n = (LVertex*)LinkQueue_Retrieve(queue) - tGraph->v;
        pFunc(tGraph->v[n]);
        printf("\t");

        for (i=0; i<LinkList_Length(tGraph->listArr[n]); i++) {
            TListNode* node = (TListNode*)LinkList_Get(tGraph->listArr[n], i);

            if (!validArr[node->v]) {
                LinkQueue_Append(queue, node->v + tGraph->v);
                validArr[node->v] = 1;
            }

        }
    }

    LinkQueue_Destroy(queue);
}

void LGraph_BFS(LGraph *graph, PFunc *pFunc)
{
    TLGraph* tGraph = (TLGraph*)graph;
    int* validArr = (int*)calloc(tGraph->count, sizeof(int));
    int i;

    if (tGraph != NULL && pFunc != NULL) {
        bfs(tGraph, 0, validArr, pFunc);

        for (i=0; i<tGraph->count; i++) {
            if (!validArr[i])
                bfs(tGraph, i, validArr, pFunc);
        }
        printf("\n");
    }
    free(validArr);
}
