#include "MGraphCase.h"

#include <stdio.h>
#include <MGraph/MGraph.h>

void pFunc(MVertex v)
{
    printf("%s", v);
}

void MGraphCase()
{
    MVertex v[5] = {"A", "B", "C", "D", "E"};
    MGraph* graph = MGraph_Create(v, 5);

    MGraph_AddEdge(graph, 0, 1, 1);
    MGraph_AddEdge(graph, 0, 2, 2);
    MGraph_AddEdge(graph, 1, 2, 3);
    MGraph_AddEdge(graph, 2, 3, 4);
    MGraph_AddEdge(graph, 3, 4, 5);

    MGraph_DFS(graph, pFunc);
    MGraph_BFS(graph, pFunc);

    printf("count = %d\n", MGraph_VertexCount(graph));
    printf("edgeCout = %d\n", MGraph_EdgeCount(graph));
    MGraph_Display(graph, pFunc);
    printf("TD2 = %d\n",  MGraph_TD(graph, 2));
    MGraph_RemoveEdge(graph, 2, 3);
//    MGraph_Clear(graph);
    MGraph_Display(graph, pFunc);

    MGraph_Destroy(graph);
}
