#include "SeqQueueCase.h"

#include "SeqQueue/SeqQueue.h"
#include <stdio.h>

void SeqQueueCase()
{
    SeqQueue* queue = SeqQueue_Create(10);
    int a[20];
    int i;

    printf("capacity = %d\n", SeqQueue_Capacity(queue));

    for (i=0; i<20; i++) {
        a[i] = i + 1;
        SeqQueue_Append(queue, a + i);
        printf("length = %d\n", SeqQueue_Length(queue));
    }

    for (i=10; i<20; i++) {
        printf("%d\n", *(int*)SeqQueue_Retrieve(queue));
        SeqQueue_Append(queue, a + i);
    }

    printf("header = %d\n", *(int*)SeqQueue_Header(queue));
    SeqQueue_Clear(queue);

    while (SeqQueue_Length(queue) > 0) {
        printf("retrieve = %d\n", *(int*)SeqQueue_Retrieve(queue));
    }

    SeqQueue_Destroy(queue);
}
