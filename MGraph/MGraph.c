#include "MGraph.h"

#include "LinkQueue/LinkQueue.h"
#include "LinkStack/LinkStack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int count;
    MVertex* v;
    int** matrix;
}TMGraph;

MGraph* MGraph_Create(MVertex* v, int n)
{
    TMGraph* ret = (TMGraph*)malloc(sizeof(TMGraph));

    if (ret != NULL) {
        int* p = NULL;
        ret->count = n;

        ret->v = (MVertex*)malloc(sizeof(MVertex) * n);
        ret->matrix = (int**)malloc(sizeof(int*) * n);
        p = (int*)calloc(n * n, sizeof(int));

        if (ret->v != NULL && ret->matrix != NULL && p != NULL) {
            int i;

            for (i=0; i<n; i++) {
                ret->v[i] = v[i];
                ret->matrix[i] = p + i * n;
            }
        } else {
            free(ret->v);
            free(ret->matrix);
            free(p);
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

void MGraph_Clear(MGraph* graph)
{
    TMGraph* tGraph = (TMGraph*)graph;

    if (tGraph != NULL) {
        int i,j;

        for (i=0; i<tGraph->count; i++) {
            for (j=0; j<tGraph->count; j++) {
                tGraph->matrix[i][j] = 0;
            }
        }
    }
}

void MGraph_Destroy(MGraph* graph)
{
    TMGraph* tGraph = (TMGraph*)graph;

    if (tGraph != 0) {
        free(tGraph->v);
        free(tGraph->matrix[0]);
        free(tGraph->matrix);
        free(tGraph);
    }
}

int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w)
{
    TMGraph* tGraph = (TMGraph*)graph;
    int ret = tGraph != NULL;

    ret = ret && 0 <= v1 && v1 < tGraph->count;
    ret = ret && 0 <= v2 && v2 < tGraph->count;

    if (ret) {
        tGraph->matrix[v1][v2] = w;
    }

    return ret;
}

int MGraph_RemoveEdge(MGraph* graph, int v1, int v2)
{
    int ret = MGraph_GetEdge(graph, v1, v2);

    if (ret) {
        ((TMGraph*)graph)->matrix[v1][v2] = 0;
    }

    return ret;
}

int MGraph_GetEdge(MGraph* graph, int v1, int v2)
{
    int ret = 0;
    TMGraph* tGraph = (TMGraph*)graph;
    int condiction = tGraph != NULL;

    condiction = condiction && 0 <= v1 && v1 <= tGraph->count;
    condiction = condiction && 0 <= v2 && v2 <= tGraph->count;

    if (condiction) {
        ret = tGraph->matrix[v1][v2];
    }

    return ret;
}

int MGraph_TD(MGraph* graph, int v)
{
    int ret = 0;
    TMGraph* tGraph = (TMGraph*)graph;
    int condiction = tGraph != NULL;

    condiction = condiction && 0 <= v < tGraph->count;

    if (condiction) {
        int i;

        for (i=0; i<tGraph->count; i++) {
            if (tGraph->matrix[i][v] != 0)
                ret += 1;
            if (tGraph->matrix[v][i] != 0)
                ret += 1;
        }
    }

    return ret;
}

int MGraph_VertexCount(MGraph* graph)
{
    int ret = -1;
    TMGraph* tGraph = (TMGraph*)graph;

    if (tGraph != NULL) {
        ret = tGraph->count;
    }

    return ret;
}

int MGraph_EdgeCount(MGraph* graph)
{
    int ret = 0;
    TMGraph* tGraph = (TMGraph*)graph;

    if (tGraph) {
        int i, j;

        for (i=0; i<tGraph->count; i++) {
            for (j=0; j<tGraph->count; j++) {
                if (tGraph->matrix[i][j] != 0)
                    ret += 1;
            }
        }
    }

    return ret;
}

void MGraph_Display(MGraph *graph, PFunc* pFunc)
{
    TMGraph* tGraph = (TMGraph*)graph;

    if (tGraph != NULL) {
        int i;
        int j;

        for (i=0; i<tGraph->count; i++) {
            printf("%d:", i);
            pFunc(tGraph->v[i]);
            printf("\t");
        }

        printf("\n");
        for (i=0; i<tGraph->count; i++) {
            for (j=0; j<tGraph->count; j++) {
                if (tGraph->matrix[i][j] != 0) {
                    printf("<");
                    pFunc(tGraph->v[i]);
                    printf(",");
                    printf("%d", tGraph->matrix[i][j]);
                    printf(",");
                    pFunc(tGraph->v[j]);
                    printf(">\n");
                }
            }
        }
    }
}

static void recursive_dfs(TMGraph* tGraph, int v, int validArr[], PFunc* pFunc)
{
    int i;
    pFunc(tGraph->v[v]);
    printf("\t");
    validArr[v] = 1;

    for (i=0; i<tGraph->count; i++) {
        if (!validArr[i] && tGraph->matrix[v][i] != 0) {
            recursive_dfs(tGraph, i, validArr, pFunc);
        }
    }
}

static void dfs(TMGraph* tGraph, int v, int validArr[], PFunc* pFunc)
{
    LinkStack* stack = LinkStack_Create();

    if (stack != NULL) {
        int i;
        LinkStack_Push(stack, tGraph->v + v);
        validArr[v] = 1;

        while (LinkStack_Size(stack) > 0) {
            int n = (MVertex*)LinkStack_Pop(stack) - tGraph->v;

            pFunc(tGraph->v[n]);
            printf("\t");

            for (i=0; i<tGraph->count; i++) {
                if (!validArr[i] && tGraph->matrix[n][i] != 0) {
                    LinkStack_Push(stack, tGraph->v + i);
                    validArr[i] = 1;
                }
            }
        }
    }

    LinkStack_Destroy(stack);
}

void MGraph_DFS(MGraph *graph, PFunc *pFunc)
{
    TMGraph* tGraph = (TMGraph*)graph;
    int* validArr;
    int condiction = tGraph != NULL;

    condiction = condiction && pFunc != NULL;
    condiction = condiction && ((validArr = (int*)calloc(tGraph->count, sizeof(int))) != NULL);

    if (condiction) {
        int i;
//        recursive_dfs(tGraph, 0, validArr, pFunc);
        dfs(tGraph, 0, validArr, pFunc);

        for (i=0; i<tGraph->count; i++) {
            if (!validArr[i]) {
//                recursive_dfs(tGraph, i, validArr, pFunc);
                dfs(tGraph, i, validArr, pFunc);
            }
        }
        printf("\n");
    }

    free(validArr);
}

static void bfs(TMGraph* tGraph, int v, int validArr[], PFunc* pFunc)
{
    LinkQueue* queue = LinkQueue_Create();

    if (queue != NULL) {
        int i;
        LinkQueue_Append(queue, tGraph->v + v);
        validArr[v] = 1;

        while (LinkQueue_Length(queue) > 0) {
            int n = (MVertex*)LinkQueue_Retrieve(queue) - tGraph->v;

            pFunc(tGraph->v[n]);
            printf("\t");

            for (i=0; i<tGraph->count; i++) {
                if (!validArr[i] && tGraph->matrix[n][i] != 0) {
                    LinkQueue_Append(queue, tGraph->v + i);
                    validArr[i] = 1;
                }
            }
        }
    }

    LinkQueue_Destroy(queue);
}

void MGraph_BFS(MGraph *graph, PFunc *pFunc)
{
    TMGraph* tGraph = (TMGraph*)graph;
    int condiction = tGraph != NULL && pFunc != NULL;
    int* validArr;

    condiction = condiction && (validArr = (int*)calloc(tGraph->count, sizeof(int))) != NULL;

    if (condiction) {
        int i;
        bfs(tGraph, 0, validArr, pFunc);

        for (i=0; i<tGraph->count; i++) {
            if (!validArr[i]) {
                bfs(tGraph, i, validArr, pFunc);
            }
        }

        printf("\n");
    }

    free(validArr);
}
