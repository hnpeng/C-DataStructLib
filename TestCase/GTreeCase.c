#include "GTreeCase.h"

#include "GTree/GTree.h"
#include <stdio.h>

void printGTreeData(GTreeData* data)
{
    printf("%c", (char)data);
}

void GTreeCase()
{
    GTree* tree = GTree_Create();

    GTree_Insert(tree, (void*)'a', -1);
    GTree_Insert(tree, (void*)'b', 0);
    GTree_Insert(tree, (void*)'c', 0);
    GTree_Insert(tree, (void*)'d', 0);
    GTree_Insert(tree, (void*)'e', 1);
    GTree_Insert(tree, (void*)'f', 1);
    GTree_Insert(tree, (void*)'g', 3);
    GTree_Insert(tree, (void*)'h', 3);
    GTree_Insert(tree, (void*)'i', 3);
    GTree_Insert(tree, (void*)'j', 8);

    GTree_Display(tree, printGTreeData);

//    printf("delete = %s\n", GTree_Get(tree, 7));
//    printf("delete = %c\n", (char)GTree_Delete(tree, 8));
    printf("degree = %d\n", GTree_Degree(tree));
    printf("hight = %d\n", GTree_Hight(tree));

    GTree_Search(tree, (void*)'j', printGTreeData);

    printf("**************\n");
    GTree_Display(tree, printGTreeData);

    GTree_Destroy(tree);
    printf("**************\n");

    GTree_Display(tree, printGTreeData);
}
