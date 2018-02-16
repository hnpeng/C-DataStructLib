#include <stdio.h>
#include <stdlib.h>
#include "SeqList.h"

typedef void* TSeqListNode;

typedef struct __tag_seqList
{
    int capacity;
    int length;
    TSeqListNode* node;
}TSeqList;

SeqList* SeqList_Create(int capacity)
{
    TSeqList* sList = (TSeqList*)malloc(sizeof(TSeqList) + capacity * sizeof(TSeqListNode));

    if (sList != NULL) {
        sList->capacity = capacity;
        sList->length = 0;
        sList->node = (TSeqListNode*)(sList + 1);
    }

    return sList;
}

void SeqList_Clear(SeqList* list)
{
    TSeqList* sList = (TSeqList*)list;

    if (sList != NULL) {
        sList->length = 0;
    }
}

void SeqList_Destroy(SeqList* list)
{
    free(list);
}

int SeqList_Length(SeqList* list)
{
    TSeqList* sList = (TSeqList*)list;
    int ret = -1;

    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int SeqList_Capacity(SeqList* list)
{
    TSeqList* sList = (TSeqList*)list;
    int ret = -1;

    if (sList != NULL) {
        ret = sList->capacity;
    }

    return ret;
}

int SeqList_Insert(SeqList* list, SeqListNode* node, int pos)
{
    TSeqList* sList = (TSeqList*)list;
    int ret = sList != NULL && node != NULL && pos >= 0;
    int i;

    ret = ret && sList->capacity > sList->length;

    if (ret) {
        for (i=sList->length; i>pos; i--) {
            sList->node[i] = sList->node[i-1];
        }

        sList->node[i] = node;
        sList->length++;
    }

    return ret;
}

SeqListNode* SeqList_Delete(SeqList* list, int pos)
{
    SeqListNode* ret = NULL;
    TSeqList* sList = (TSeqList*)list;
    int i;

    if (sList != NULL && 0 <= pos && pos < sList->length) {
        ret = sList->node[pos];

        for (i=pos+1; i<sList->length; i++) {
            sList->node[i-1] = sList->node[i];
        }

        sList->length--;
    }

    return ret;
}

SeqListNode* SeqList_Get(SeqList* list, int pos)
{
    SeqListNode* ret = NULL;
    TSeqList* sList = (TSeqList*)list;

    if (sList != NULL && 0 <= pos && pos < sList->length) {
        ret = sList->node[pos];
    }

    return ret;
}
