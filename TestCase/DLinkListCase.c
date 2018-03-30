#include "DLinkListCase.h"
#include "DLinkList/DLinkList.h"

#include <stdio.h>

void DLinkListCase()
{
    DLinkList* list = DLinkList_Create();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    int i;
    int l;

    DLinkList_Insert(list, &v1, 0);
    DLinkList_Insert(list, &v2, 0);
    DLinkList_Insert(list, &v3, 0);
    DLinkList_Insert(list, &v4, 0);
    DLinkList_Insert(list, &v5, 0);

    l = DLinkList_Length(list);

    printf("length = %d\n", l);

    for (i=0; i<l; i++) {
        int* value = DLinkList_Get(list, i);
        printf("%d\n", *value);
    }

    DLinkList_DeleteNode(list, &v1);
    DLinkList_DeleteNode(list, &v5);

    l = DLinkList_Length(list);

    printf("length = %d\n", l);

    for (i=0; i<l; i++) {
        int* value = DLinkList_Next(list);
        printf("%d\n", *value);
    }

    DLinkList_Reset(list);
    DLinkList_Next(list);
    DLinkList_Next(list);
    DLinkList_Pre(list);
    DLinkList_Pre(list);
    int* value = DLinkList_Current(list);
    printf("current = %d\n", *value);

    while (DLinkList_Length(list) > 0) {
        int* value = DLinkList_Delete(list, 0);
        printf("Delete = %d\n", *value);
    }

    DLinkList_Clear(list);
    DLinkList_Destroy(list);
}
