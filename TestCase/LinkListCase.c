#include "LinkListCase.h"
#include "LinkList/LinkList.h"
#include <stdio.h>

void LinkListCase()
{
    LinkList* list = LinkList_Create(7);
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    int v6 = 6;
    int i;

    LinkList_Insert(list, &v1, 10);
    LinkList_Insert(list, &v2, 10);
    LinkList_Insert(list, &v3, 10);
    LinkList_Insert(list, &v4, 10);
    LinkList_Insert(list, &v5, 10);
    LinkList_Insert(list, &v6, 10);

//    LinkList_Reverse(list);
    LinkList_Clear(list);

    LinkList_Insert(list, &v1, 10);
    LinkList_Insert(list, &v2, 10);
    LinkList_Insert(list, &v3, 10);
    LinkList_Insert(list, &v4, 10);
    LinkList_Insert(list, &v5, 10);
    LinkList_Insert(list, &v6, 10);
    printf("length = %d\n", LinkList_Length(list));

    for (i=0; i<LinkList_Length(list); i++) {
        int *e = (int*)LinkList_Get(list, i);
        printf("element = %d\n", *e);
    }

    int* v = (int*)LinkList_GetMidNode(list);
    printf("mid = %d\n", *v);


//    while (LinkList_Length(list) > 0) {
//        int* e = (int*) LinkList_Delete(list, 0);
//        printf("delete = %d\n", *e);
//    }

    printf("length = %d\n", LinkList_Length(list));

    LinkList_Clear(list);
    LinkList_Destroy(list);
}
