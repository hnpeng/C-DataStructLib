#include "LGraphCase.h"

#include "LGraph/LGraph.h"
#include <stdio.h>

void pFuncc(LVertex v)
{
    printf("%s", v);
}

void LGraphCase()
{
    LVertex v[5] = {"A", "B", "C", "D", "E"};
    LGraph* graph = LGraph_Create(v, 5);

    LGraph_AddEdge(graph, 0, 1, 1);
    LGraph_AddEdge(graph, 0, 2, 2);
    LGraph_AddEdge(graph, 1, 2, 3);
    LGraph_AddEdge(graph, 2, 3, 4);
    LGraph_AddEdge(graph, 3, 4, 5);

    printf("count = %d\n", LGraph_VertexCount(graph));
    printf("edgeCout = %d\n", LGraph_EdgeCount(graph));
    LGraph_Display(graph, pFuncc);
    printf("TD2 = %d\n",  LGraph_TD(graph, 2));
    LGraph_RemoveEdge(graph, 2, 3);
    LGraph_Clear(graph);
    LGraph_Display(graph, pFuncc);

    LGraph_Destroy(graph);

}
