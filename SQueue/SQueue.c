#include "SQueue.h"

#include "LinkStack/LinkStack.h"
#include <stdlib.h>

typedef struct
{
    LinkStack* inStack;
    LinkStack* outStack;
    LinkStack* inStackMaxAddrBuf; //stack's Top save the instack's max value;
    LinkStack* outStackMaxAddrBuf; //stack's Top save the outstack's max value;
}TSQueue;

SQueue* SQueue_Create()
{
    TSQueue* ret = (TSQueue*)malloc(sizeof(TSQueue));

    if (ret != NULL) {
        ret->inStack = LinkStack_Create();
        ret->outStack = LinkStack_Create();
        ret->inStackMaxAddrBuf = LinkStack_Create();
        ret->outStackMaxAddrBuf = LinkStack_Create();

        if (ret->inStack == NULL ||
                ret->outStack == NULL ||
                ret->inStackMaxAddrBuf == NULL ||
                ret->outStackMaxAddrBuf == NULL) {
            LinkStack_Destroy(ret->inStack);
            LinkStack_Destroy(ret->outStack);
            LinkStack_Destroy(ret->inStackMaxAddrBuf);
            LinkStack_Destroy(ret->outStackMaxAddrBuf);
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
        LinkStack_Clear(sQueue->inStackMaxAddrBuf);
        LinkStack_Clear(sQueue->outStackMaxAddrBuf);
    }
}

void SQueue_Destroy(SQueue* queue)
{
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        LinkStack_Destroy(sQueue->inStack);
        LinkStack_Destroy(sQueue->outStack);
        LinkStack_Destroy(sQueue->inStackMaxAddrBuf);
        LinkStack_Destroy(sQueue->outStackMaxAddrBuf);
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

    if (ret) {
        if (LinkStack_Size(sQueue->inStackMaxAddrBuf) == 0 ||
                item > LinkStack_Top(sQueue->inStackMaxAddrBuf)) {
            LinkStack_Push(sQueue->inStackMaxAddrBuf, item);
        }
    }

    return ret;
}

void preHandleOutStackNull(TSQueue* sQueue)
{
    if (LinkStack_Size(sQueue->outStack) == 0) {

        while (LinkStack_Size(sQueue->inStack) > 0) {
            void* item = LinkStack_Pop(sQueue->inStack);

            LinkStack_Push(sQueue->outStack, item);

            if (item == LinkStack_Top(sQueue->inStackMaxAddrBuf)) {
                LinkStack_Pop(sQueue->inStackMaxAddrBuf);
            }

            if (LinkStack_Size(sQueue->outStackMaxAddrBuf) == 0 ||
                    item > LinkStack_Top(sQueue->outStackMaxAddrBuf)) {
                LinkStack_Push(sQueue->outStackMaxAddrBuf, item);
            }
        }
    }
}

void* SQueue_Retrieve(SQueue* queue)
{
    void* ret = NULL;
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        preHandleOutStackNull(sQueue);

        ret = LinkStack_Pop(sQueue->outStack);

        if (ret == LinkStack_Top(sQueue->outStackMaxAddrBuf)) {
            LinkStack_Pop(sQueue->outStackMaxAddrBuf);
        }
    }

    return ret;
}

void* SQueue_Header(SQueue* queue)
{
    void* ret = NULL;
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        preHandleOutStackNull(sQueue);

        ret = LinkStack_Top(sQueue->outStack);
    }

    return ret;
}

void *SQueue_MaxAddress(SQueue *queue)
{
    void* ret = NULL;
    TSQueue* sQueue = (TSQueue*)queue;

    if (sQueue != NULL) {
        void* inBufTop = LinkStack_Top(sQueue->inStackMaxAddrBuf);
        void* outBufTop = LinkStack_Top(sQueue->outStackMaxAddrBuf);

        ret = inBufTop > outBufTop ? inBufTop : outBufTop;
    }

    return ret;
}
