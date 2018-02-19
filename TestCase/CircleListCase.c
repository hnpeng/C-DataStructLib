#include "CircleListCase.h"

#include "CircleList/CircleList.h"
#include <stdio.h>

void CircleListCase()
{
    CircleList* list = CircleList_Create();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    int v6 = 6;
    int v7 = 7;
    int v8 = 8;

    CircleList_Insert(list, &v1, CircleList_Length(list));
    CircleList_Insert(list, &v2, CircleList_Length(list));
    CircleList_Insert(list, &v3, CircleList_Length(list));
    CircleList_Insert(list, &v4, CircleList_Length(list));
    CircleList_Insert(list, &v5, CircleList_Length(list));
    CircleList_Insert(list, &v6, CircleList_Length(list));
    CircleList_Insert(list, &v7, CircleList_Length(list));
    CircleList_Insert(list, &v8, CircleList_Length(list));

    CircleList_Clear(list);

    CircleList_Insert(list, &v1, CircleList_Length(list));
    CircleList_Insert(list, &v2, CircleList_Length(list));
    CircleList_Insert(list, &v3, CircleList_Length(list));
    CircleList_Insert(list, &v4, CircleList_Length(list));
    CircleList_Insert(list, &v5, CircleList_Length(list));
    CircleList_Insert(list, &v6, CircleList_Length(list));
    CircleList_Insert(list, &v7, CircleList_Length(list));
    CircleList_Insert(list, &v8, CircleList_Length(list));
    printf("length = %d\n", CircleList_Length(list));

//    CircleList_DeleteNode(list, &v3);

    for (int i=0; i<CircleList_Length(list); i++) {
        int* v = CircleList_Get(list, i);

        printf("v = %d\n", *v);
    }

//    while (CircleList_Length(list) > 0) {
//        int* v = CircleList_Delete(list, 0);

//        printf("v = %d\n", *v);
//    }

    int* reset = CircleList_Reset(list);
    printf("reset = %d\n", *reset);
    int* toDel = NULL;

    for (int i=0; i<20; i++) {
        toDel = (int*)CircleList_Next(list);
        printf("toDel = %d\n", *toDel);
    }

//    while (CircleList_Length(list) > 0) {
//        CircleList_Next(list);
//        CircleList_Next(list);
//        toDel = (int*)CircleList_Current(list);
//        CircleList_DeleteNode(list, toDel);

//        printf("toDel = %d\n", *toDel);
//    }


    CircleList_Destroy(list);
}
