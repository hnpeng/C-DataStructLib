#include "SStack.h"

#include "LinkQueue/LinkQueue.h"
#include <stdlib.h>

typedef struct
{
    LinkQueue* queue[2];
    int index;
}TSStack;

SStack* SStack_Create()
{
    TSStack* ret = (TSStack*)malloc(sizeof(TSStack));

    if (ret != NULL) {
        ret->queue[0] = LinkQueue_Create();
        ret->queue[1] = LinkQueue_Create();
        ret->index = 0;

        if (ret->queue[0] == NULL || ret->queue[1] == NULL) {
            LinkQueue_Destroy(ret->queue[0]);
            LinkQueue_Destroy(ret->queue[1]);
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

void SStack_Clear(SStack* stack)
{
    TSStack* sStack = (TSStack*)stack;

    if (sStack != NULL) {
        LinkQueue_Clear(sStack->queue[sStack->index]);
        sStack->index = 0;
    }
}

void SStack_Destroy(SStack* stack)
{
    TSStack* sStack = (TSStack*)stack;

    if (sStack != NULL) {
        LinkQueue_Destroy(sStack->queue[0]);
        LinkQueue_Destroy(sStack->queue[1]);
        free(sStack);
    }
}

int SStack_Push(SStack* stack, void* item)
{
    TSStack* sStack = (TSStack*)stack;
    int ret = sStack != NULL;

    if (ret) {
        ret = LinkQueue_Append(sStack->queue[sStack->index], item);
    }

    return ret;
}

void* SStack_Pop(SStack* stack)
{
    void* ret = NULL;
    TSStack* sStack = (TSStack*)stack;

    if (sStack != NULL) {
        while (LinkQueue_Length(sStack->queue[sStack->index]) > 1) {
            LinkQueue_Append(sStack->queue[!sStack->index],
                    LinkQueue_Retrieve(sStack->queue[sStack->index]));
        }

        ret = LinkQueue_Retrieve(sStack->queue[sStack->index]);
        sStack->index = !sStack->index;
    }

    return ret;
}

void* SStack_Top(SStack* stack)
{
    void* ret = SStack_Pop(stack);

    if (ret != NULL)
        SStack_Push(stack, ret);

    return ret;
}

int SStack_Size(SStack* stack)
{
    int ret = -1;
    TSStack* sStack = (TSStack*)stack;

    if (sStack != NULL) {
        ret = LinkQueue_Length(sStack->queue[sStack->index]);
    }

    return ret;
}
