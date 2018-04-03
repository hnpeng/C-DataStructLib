#include "SStackCase.h"

#include <stdio.h>
#include <SStack/SStack.h>

void SStackCase()
{
    int a[20];
    int i;
    SStack* stack = SStack_Create();

    for (i=0; i<10; i++) {
        a[i] = i;
        SStack_Push(stack, a + i);
    }

    printf("size = %d\n", SStack_Size(stack));

    printf("top = %d\n", *(int*)SStack_Top(stack));

//    SStack_Clear(stack);

    while (SStack_Size(stack) > 0) {
        printf("pop = %d\n", *(int*)SStack_Pop(stack));
    }

    SStack_Pop(stack);

    SStack_Destroy(stack);
}
