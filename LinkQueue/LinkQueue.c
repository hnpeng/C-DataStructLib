#include "LinkQueue.h"

#include <stdlib.h>

typedef struct _tag_tlinkqueuenode TLinkQueueNode;
struct _tag_tlinkqueuenode
{
    TLinkQueueNode* next;
    void* item;
};

typedef struct
{
    TLinkQueueNode* front;
    TLinkQueueNode* rear;
    int length;
}TLinkQueue;

LinkQueue* LinkQueue_Create()
{
    TLinkQueue* ret = (TLinkQueue*)malloc(sizeof(TLinkQueue));

    if (ret != NULL) {
        ret->front = NULL;
        ret->rear = NULL;
        ret->length = 0;
    }

    return ret;
}

void LinkQueue_Clear(LinkQueue* queue)
{
    while (LinkQueue_Length(queue) > 0) {
        LinkQueue_Retrieve(queue);
    }
}

void LinkQueue_Destroy(LinkQueue* queue)
{
    LinkQueue_Clear(queue);
    free(queue);
}

int LinkQueue_Length(LinkQueue* queue)
{
    int ret = -1;
    TLinkQueue* sQueue = (TLinkQueue*)queue;

    if (sQueue != NULL) {
        ret = sQueue->length;
    }

    return ret;
}

int LinkQueue_Append(LinkQueue* queue, void* item)
{
    TLinkQueue* sQueue = (TLinkQueue*)queue;
    TLinkQueueNode* newNode = (TLinkQueueNode*)malloc(sizeof(TLinkQueueNode));
    int ret = sQueue != NULL && item != NULL && newNode != NULL;

    if (ret) {
        newNode->item = item;

        if (sQueue->length > 0) {
            sQueue->rear->next = newNode;
            sQueue->rear = newNode;
            newNode->next = NULL;
        } else {
            sQueue->front = newNode;
            sQueue->rear = newNode;
            newNode->next = NULL;
        }

        sQueue->length++;
    }

    return ret;
}

void* LinkQueue_Retrieve(LinkQueue* queue)
{
    void* ret = NULL;
    TLinkQueue* sQueue = (TLinkQueue*)queue;

    if (sQueue != NULL && sQueue->length > 0) {
        TLinkQueueNode* targetNode = sQueue->front;

        ret = targetNode->item;
        sQueue->front = targetNode->next;
        free(targetNode);

        sQueue->length--;

        if (sQueue->length == 0) {
            sQueue->front = NULL;
            sQueue->rear = NULL;
        }
    }

    return ret;
}

void* LinkQueue_Header(LinkQueue* queue)
{
    void* ret = NULL;
    TLinkQueue* sQueue = (TLinkQueue*)queue;

    if (sQueue != NULL && sQueue->length > 0) {

        ret = sQueue->front->item;
    }

    return ret;
}
