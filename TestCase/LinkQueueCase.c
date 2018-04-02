#include "LinkQueueCase.h"

#include <stdio.h>
#include "LinkQueue/LinkQueue.h"

void LinkQueueCase()
{
    LinkQueue* queue = LinkQueue_Create();
    int a[20];
    int i;

    for (i=0; i<20; i++) {
        a[i] = i + 1;
        LinkQueue_Append(queue, a + i);
        printf("length = %d\n", LinkQueue_Length(queue));
        if (i == 9)
            LinkQueue_Clear(queue);
    }

    printf("header = %d\n", *(int*)LinkQueue_Header(queue));
//    LinkQueue_Clear(queue);

    while (LinkQueue_Length(queue) > 0) {
        printf("retrieve = %d\n", *(int*)LinkQueue_Retrieve(queue));
    }

    LinkQueue_Destroy(queue);
}
