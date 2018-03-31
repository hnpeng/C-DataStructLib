#include "SeqStackCase.h"
#include "SeqStack/SeqStack.h"

#include <stdio.h>

void SeqStackCase()
{
    int a[20];
    int i;
    SeqStack* stack = SeqStack_Create(20);

    for (i=0; i<10; i++) {
        a[i] = i;
        SeqStack_Push(stack, a + i);
    }

    printf("size = %d\n", SeqStack_Size(stack));
    printf("capacity = %d\n", SeqStack_Capacity(stack));

    printf("top = %d\n", *(int*)SeqStack_Top(stack));

//    SeqStack_Clear(stack);
    while (SeqStack_Size(stack) > 0) {
        printf("pop = %d\n", *(int*)SeqStack_Pop(stack));
    }

    SeqStack_Destroy(stack);
}
