#ifndef MGRAPH_H
#define MGRAPH_H

typedef void MGraph;
typedef void* MVertex;

typedef void (PFunc)(MVertex vertex);

MGraph* MGraph_Create(MVertex* v, int n);

void MGraph_Clear(MGraph* graph);

void MGraph_Destroy(MGraph* graph);

int MGraph_AddEdge(MGraph* graph, int v1, int v2, int w);

int MGraph_RemoveEdge(MGraph* graph, int v1, int v2);

int MGraph_GetEdge(MGraph* graph, int v1, int v2);

int MGraph_TD(MGraph* graph, int v);

int MGraph_VertexCount(MGraph* graph);

int MGraph_EdgeCount(MGraph* graph);

void MGraph_Display(MGraph* graph, PFunc* pFunc);

#endif
