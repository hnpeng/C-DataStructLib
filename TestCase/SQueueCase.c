#include "SQueueCase.h"

#include "SQueue/SQueue.h"
#include <stdio.h>

void SQueueCase()
{
    SQueue* queue = SQueue_Create();
    int a[20];
    int i;

    for (i=0; i<20; i++) {
        a[i] = i + 1;
        SQueue_Append(queue, a + i);
        printf("length = %d\n", SQueue_Length(queue));
        if (i == 9)
            SQueue_Clear(queue);
    }

    printf("header = %d\n", *(int*)SQueue_Header(queue));
//    SQueue_Clear(queue);

    while (SQueue_Length(queue) > 0) {
        printf("retrieve = %d\n", *(int*)SQueue_Retrieve(queue));
    }

    SQueue_Destroy(queue);
}
