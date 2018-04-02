#include "SeqQueue.h"

#include <stdlib.h>

typedef void* TSeqQueueNode;
typedef struct
{
    int capacity;
    int front;
    int rear;
    int length;
    TSeqQueueNode* node;
}TSeqQueue;

SeqQueue* SeqQueue_Create(int capacity)
{
    TSeqQueue* ret = (TSeqQueue*)malloc(sizeof(TSeqQueue) + sizeof(TSeqQueueNode) * capacity);

    if (ret != NULL) {
        ret->capacity = capacity;
        ret->front = 0;
        ret->rear = 0;
        ret->length = 0;
        ret->node = (TSeqQueueNode*)(ret + 1);
    }

    return ret;
}

void SeqQueue_Clear(SeqQueue* queue)
{
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if (sQueue != NULL) {
        sQueue->front = 0;
        sQueue->rear = 0;
        sQueue->length = 0;
    }
}

void SeqQueue_Destroy(SeqQueue* queue)
{
    free(queue);
}

int SeqQueue_Length(SeqQueue* queue)
{
    int ret = -1;
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if (sQueue != NULL) {
        ret = sQueue->length;
    }

    return ret;
}

int SeqQueue_Capacity(SeqQueue* queue)
{
    int ret = -1;
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if (sQueue != NULL) {
        ret = sQueue->capacity;
    }

    return ret;
}

int SeqQueue_Append(SeqQueue* queue, void* item)
{
    TSeqQueue* sQueue = (TSeqQueue*)queue;
    int ret = sQueue != NULL && item != NULL;

    ret = ret && sQueue->length < sQueue->capacity;

    if (ret) {
        sQueue->node[sQueue->rear] = (TSeqQueueNode*)item;
        sQueue->rear = (sQueue->rear + 1) % sQueue->capacity;
        sQueue->length++;
    }

    return ret;
}

void* SeqQueue_Retrieve(SeqQueue* queue)
{
    void* ret = SeqQueue_Header(queue);
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if (ret) {
        sQueue->front = (sQueue->front + 1) % sQueue->capacity;
        sQueue->length--;
    }

    return ret;
}

void* SeqQueue_Header(SeqQueue* queue)
{
    void* ret = NULL;
    TSeqQueue* sQueue = (TSeqQueue*)queue;

    if (sQueue != NULL && sQueue->length > 0) {
        ret = sQueue->node[sQueue->front];
    }

    return ret;
}
