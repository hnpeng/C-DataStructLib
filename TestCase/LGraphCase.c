#include "LGraphCase.h"

#include "LGraph/LGraph.h"
#include <stdio.h>

void pFuncc(LVertex v)
{
    printf("%s", v);
}

void LGraphCase()
{
    LVertex v[6] = {"A", "B", "C", "D", "E", "F"};
    LGraph* graph = LGraph_Create(v, 6);

    LGraph_AddEdge(graph, 0, 1, 1);
    LGraph_AddEdge(graph, 0, 2, 1);
    LGraph_AddEdge(graph, 0, 3, 1);
    LGraph_AddEdge(graph, 1, 5, 1);
    LGraph_AddEdge(graph, 1, 4, 1);
    LGraph_AddEdge(graph, 2, 1, 1);
    LGraph_AddEdge(graph, 3, 4, 1);
//    LGraph_AddEdge(graph, 4, 2, 1);

    printf("count = %d\n", LGraph_VertexCount(graph));
    printf("edgeCout = %d\n", LGraph_EdgeCount(graph));
    LGraph_Display(graph, pFuncc);
    printf("TD2 = %d\n",  LGraph_TD(graph, 2));
    LGraph_RemoveEdge(graph, 2, 3);
//    LGraph_Clear(graph);
//    LGraph_Display(graph, pFuncc);

    LGraph_DFS(graph, pFuncc);
    LGraph_BFS(graph, pFuncc);

    LGraph_Destroy(graph);

}
