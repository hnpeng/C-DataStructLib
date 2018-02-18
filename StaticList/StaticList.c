#include "StaticList.h"
#include <stdlib.h>

#define AVAILABLE -1

typedef void* Data;

typedef struct
{
    int next;
    Data data;
}TStaticListNode;

typedef struct
{
    int capacity;
    int nullHeadNode;
    TStaticListNode node[];
}TStaticList;

StaticList *StaticList_Create(int capacity)
{
    TStaticList* ret = (TStaticList*)malloc(sizeof(TStaticList) + sizeof(TStaticListNode) * (capacity + 1));

    if (ret != NULL) {
        int i;

        ret->capacity = capacity;
        ret->nullHeadNode = 1;
        ret->node[0].next = 0;
        ret->node[0].data = 0;

        for (i=1; i<capacity+1; i++) {
            ret->node[i].next = i+1;
        }
    }

    return ret;
}

void StaticList_Clear(StaticList *list)
{
    TStaticList* sList = (TStaticList*)list;

    if (sList != NULL)
    {
        int i;

        sList->node[0].data = 0;
        sList->node[0].next = 0;
        sList->nullHeadNode = 1;

        for (i=1; i<sList->capacity+1; i++) {
            sList->node[i].next = i + 1;
        }
    }
}

void StaticList_Destroy(StaticList *list)
{
    free(list);
}

int StaticList_Length(StaticList *list)
{
    int ret = -1;
    TStaticList* sList = (TStaticList*)list;

    if (sList != NULL) {
        ret = (int)sList->node[0].data;
    }

    return ret;
}

int StaticList_Capacity(StaticList *list)
{
    int ret = -1;
    TStaticList* sList = (TStaticList*)list;

    if (sList != NULL) {
        ret = sList->capacity;
    }

    return ret;
}

int StaticList_Insert(StaticList *list, StaticListNode *node, int pos)
{
    TStaticList* sList = (TStaticList*)list;
    int ret = sList != NULL && node != NULL;

    ret = ret && pos >= 0;
    ret = ret && (int)sList->node[0].data < sList->capacity;

    if (ret) {
        int i;
        int current = 0;
        int availablePos = sList->nullHeadNode;

        sList->nullHeadNode = sList->node[availablePos].next;

        for (i=0; i<pos && sList->node[current].next != 0; i++) {
            current = sList->node[current].next;
        }

        sList->node[availablePos].next = sList->node[current].next;
        sList->node[current].next = availablePos;
        sList->node[availablePos].data = (Data)node;

//        sList->node[0].data  = (int)sList->node[0].data + 1;
        sList->node[0].data++;
    }

    return ret;
}

StaticListNode *StaticList_Get(StaticList *list, int pos)
{
    StaticListNode* ret = NULL;
    TStaticList* sList = (TStaticList*)list;

    if (sList != NULL && 0 <= pos && pos < (int)sList->node[0].data) {
        int i;
        int current = 0;
        int tagIndex = 0;

        for (i=0; i<pos; i++) {
            current = sList->node[current].next;
        }

        tagIndex = sList->node[current].next;
        ret = (StaticListNode*)sList->node[tagIndex].data;
    }

    return ret;
}

StaticListNode *StaticList_Delete(StaticList *list, int pos)
{
    StaticListNode* ret = NULL;
    TStaticList* sList = (TStaticList*)list;

    if (sList != NULL && 0 <= pos && pos < (int)sList->node[0].data) {
        int current = 0;
        int tagIndex = 0;
        int i;

        for (i=0; i<pos; i++) {
            current = sList->node[current].next;
        }

        tagIndex = sList->node[current].next;
        sList->node[current].next = sList->node[tagIndex].next;

        ret = (StaticListNode*)sList->node[tagIndex].data;
        sList->node[tagIndex].next = sList->nullHeadNode;
        sList->nullHeadNode = tagIndex;
        sList->node[0].data--;
    }

    return ret;
}
