#include "SQueue.h"

#include "LinkStack/LinkStack.h"
#include <stdlib.h>

typedef struct
{
    LinkStack* inStack;
    LinkStack* outStack;
}TSQueue;

SQueue* SQueue_Create()
{
    TSQueue* ret = (TSQueue*)malloc(sizeof(TSQueue));

    if (ret != NULL) {
        ret->inStack = LinkStack_Create();
        ret->outStack = LinkStack_Create();

        if (ret->inStack == NULL || ret->outStack == NULL) {
            LinkStack_Destroy(ret->inStack);
            LinkStack_Destroy(ret->outStack);
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

void SQueue_Clear(SQueue* queue)
{
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        LinkStack_Clear(sQueue->inStack);
        LinkStack_Clear(sQueue->outStack);
    }
}

void SQueue_Destroy(SQueue* queue)
{
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        LinkStack_Destroy(sQueue->inStack);
        LinkStack_Destroy(sQueue->outStack);
        free(sQueue);
    }
}

int SQueue_Length(SQueue* queue)
{
    TSQueue* sQueue = (TSQueue*)queue;
    int ret = -1;

    if (sQueue != NULL) {
        ret = LinkStack_Size(sQueue->inStack) + LinkStack_Size(sQueue->outStack);
    }

    return ret;
}

int SQueue_Append(SQueue* queue, void* item)
{
    TSQueue* sQueue = (TSQueue*)queue;
    int ret = sQueue != NULL;

    ret = ret &&  LinkStack_Push(sQueue->inStack, item);

    return ret;
}

void* SQueue_Retrieve(SQueue* queue)
{
    void* ret = NULL;
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        while (LinkStack_Size(sQueue->inStack) > 0) {
            LinkStack_Push(sQueue->outStack, LinkStack_Pop(sQueue->inStack));
        }

        ret = LinkStack_Pop(sQueue->outStack);
    }

    return ret;
}

void* SQueue_Header(SQueue* queue)
{
    void* ret = NULL;
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        while (LinkStack_Size(sQueue->inStack) > 0) {
            LinkStack_Push(sQueue->outStack, LinkStack_Pop(sQueue->inStack));
        }

        ret = LinkStack_Top(sQueue->outStack);
    }

    return ret;
}
