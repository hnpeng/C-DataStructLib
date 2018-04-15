#ifndef LGRAPH_H
#define LGRAPH_H

typedef void LGraph;
typedef void* LVertex;

typedef void (PFunc)(LVertex vertex);

LGraph* LGraph_Create(LVertex* v, int n);

void LGraph_Clear(LGraph* graph);

void LGraph_Destroy(LGraph* graph);

int LGraph_AddEdge(LGraph* graph, int v1, int v2, int w);

int LGraph_RemoveEdge(LGraph* graph, int v1, int v2);

int LGraph_GetEdge(LGraph* graph, int v1, int v2);

int LGraph_TD(LGraph* graph, int v);

int LGraph_VertexCount(LGraph* graph);

int LGraph_EdgeCount(LGraph* graph);

void LGraph_Display(LGraph* graph, PFunc* pFunc);

#endif
