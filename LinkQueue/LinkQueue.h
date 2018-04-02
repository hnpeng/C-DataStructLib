#ifndef LINKQUEUE_H
#define LINKQUEUE_H

typedef void LinkQueue;

LinkQueue* LinkQueue_Create();

void LinkQueue_Clear(LinkQueue* queue);

void LinkQueue_Destroy(LinkQueue* queue);

int LinkQueue_Length(LinkQueue* queue);

int LinkQueue_Append(LinkQueue* queue, void* item);

void* LinkQueue_Retrieve(LinkQueue* queue);

void* LinkQueue_Header(LinkQueue* queue);

#endif
