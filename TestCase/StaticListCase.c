#include "StaticListCase.h"

#include "StaticList/StaticList.h"
#include <stdio.h>

void StaticListCase()
{
    StaticList* list = StaticList_Create(5);
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    int i = 0;

    StaticList_Insert(list, &v1, 10);
    StaticList_Insert(list, &v2, 10);
    StaticList_Insert(list, &v3, 10);
    StaticList_Insert(list, &v4, 10);
    StaticList_Insert(list, &v5, 10);

    printf("length = %d\n", StaticList_Length(list));

    for (i=0; i<StaticList_Length(list); i++) {
        int* e = StaticList_Get(list, i);
        printf("element = %d\n", *e);
    }

//    while (StaticList_Length(list) > 0) {
//        int* e = StaticList_Delete(list, 0);
//        printf("element = %d\n", *e);
//    }

    StaticList_Delete(list, 4);
//    StaticList_Clear(list);

    StaticList_Insert(list, &v1, 10);
    StaticList_Insert(list, &v2, 10);
    StaticList_Insert(list, &v3, 10);
    StaticList_Insert(list, &v4, 10);
    StaticList_Insert(list, &v5, 10);

    printf("length = %d\n", StaticList_Length(list));

    for (i=0; i<StaticList_Length(list); i++) {
        int* e = StaticList_Get(list, i);
        printf("element = %d\n", *e);
    }

    StaticList_Clear(list);
    StaticList_Destroy(list);
}
