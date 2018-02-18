#include <stdio.h>
#include "SeqList/SeqList.h"

#include "SeqListCase.h"

void seqListCase()
{
    SeqList* list = SeqList_Create(6);
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    int v6 = 6;
    int i;

    SeqList_Insert(list, &v1, 0);
    SeqList_Insert(list, &v2, 0);
    SeqList_Insert(list, &v3, 0);
    SeqList_Insert(list, &v4, 0);
    SeqList_Insert(list, &v5, 0);
    SeqList_Insert(list, &v6, 0);

//    SeqList_Clear(list);

//    SeqList_Reverse(list);

    for (i=0; i<SeqList_Length(list); i++) {
        int *e = (int*)SeqList_Get(list, i);
        printf("element = %d\n", *e);
    }

    printf("capacity = %d\n", SeqList_Capacity(list));
    printf("length = %d\n", SeqList_Length(list));

    while (SeqList_Length(list) > 0) {
        int* e = (int*) SeqList_Delete(list, 0);
        printf("delete = %d\n", *e);
    }

    printf("capacity = %d\n", SeqList_Capacity(list));
    printf("length = %d\n", SeqList_Length(list));

    SeqList_Destroy(list);
}
