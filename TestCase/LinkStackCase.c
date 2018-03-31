#include "LinkStackCase.h"

#include "LinkStack/LinkStack.h"
#include <stdio.h>

void LinkStackCase()
{
    int a[20];
    int i;
    LinkStack* stack = LinkStack_Create();

    for (i=0; i<10; i++) {
        a[i] = i;
        LinkStack_Push(stack, a + i);
    }

    printf("size = %d\n", LinkStack_Size(stack));

    printf("top = %d\n", *(int*)LinkStack_Top(stack));

    LinkStack_Clear(stack);
    while (LinkStack_Size(stack) > 0) {
        printf("pop = %d\n", *(int*)LinkStack_Pop(stack));
    }

    LinkStack_Destroy(stack);
}
