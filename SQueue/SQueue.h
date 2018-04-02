#ifndef SQUEUE_H
#define SQUEUE_H

typedef void SQueue;

SQueue* SQueue_Create();

void SQueue_Clear(SQueue* queue);

void SQueue_Destroy(SQueue* queue);

int SQueue_Length(SQueue* queue);

int SQueue_Append(SQueue* queue, void* item);

void* SQueue_Retrieve(SQueue* queue);

void* SQueue_Header(SQueue* queue);

#endif
