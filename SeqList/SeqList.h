#ifndef SEQLIST_H
#define SEQLIST_H

typedef void SeqList;
typedef void SeqListNode;

SeqList *SeqList_Create(int capacity);

void SeqList_Clear(SeqList* list);

void SeqList_Destroy(SeqList* list);

int SeqList_Insert(SeqList* list, SeqListNode* node, int pos);

SeqListNode* SeqList_Get(SeqList* list, int pos);

SeqListNode* SeqList_Delete(SeqList* list, int pos);

int SeqList_Length(SeqList* list);

int SeqList_Capacity(SeqList* list);

void SeqList_Reverse(SeqList* list);

#endif // SEQLIST_H
