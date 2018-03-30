#include "CircleList.h"
#include "stdlib.h"

typedef struct __tag_circleListNode CircleListNode;
struct __tag_circleListNode
{
    CircleListNode* next;
};

typedef struct
{
    CircleListNode header;
    CircleListNode* slider;
    int length;
}TCircleList;

typedef void* Data;
typedef struct
{
    CircleListNode header;
    Data data;
}TCircleListNode;

CircleList* CircleList_Create()
{
    TCircleList* ret = (TCircleList*)malloc(sizeof(TCircleList));

    if (ret != NULL) {
        ret->header.next = NULL;
        ret->slider = NULL;
        ret->length = 0;
    }

    return ret;
}

void CircleList_Clear(CircleList* list)
{
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL) {
        while (CircleList_Length(list) > 0) {
            CircleList_Delete(list, 0);
        }
    }
}

void CircleList_Destroy(CircleList* list)
{
    CircleList_Clear(list);
    free(list);
}

int CircleList_Length(CircleList* list)
{
    int ret = -1;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int CircleList_Insert(CircleList* list, CircleListNodeData *node, int pos)
{
    TCircleList* sList = (TCircleList*)list;
    int ret = sList != NULL && node != NULL;

    ret = ret && 0 <= pos;

    if (ret) {
        CircleListNode* current = (CircleListNode*)sList;
        TCircleListNode* sNode = (TCircleListNode*)malloc(sizeof(TCircleListNode));
        int i;

        for (i=0; i<pos && current != NULL; i++) {
            current = current->next;
        }

        sNode->header.next = current->next;
        current->next = (CircleListNode*)sNode;
        sNode->data = (Data)node;
        sList->length++;

        if (sList->length == 1) {
            sNode->header.next = (CircleListNode*)sNode;
            sList->slider = (CircleListNode*)sNode;
        }
    }

    return ret;
}

CircleListNodeData* CircleList_Get(CircleList* list, int pos)
{
    CircleListNodeData* ret = NULL;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL && 0 <= pos && sList->length > 0) {
        CircleListNode* current = (CircleListNode*)sList;
        CircleListNode* object = NULL;
        int i;

        for (i=0; i<pos; i++) {
            current = current->next;
        }

        object = current->next;

        ret = (CircleListNodeData*)((TCircleListNode*)object)->data;
    }

    return ret;
}

CircleListNodeData* CircleList_Delete(CircleList* list, int pos)
{
    CircleListNodeData* ret = NULL;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL && 0 <= pos && sList->length > 0) {
        CircleListNode* current = (CircleListNode*)sList;
        CircleListNode* object = NULL;
        CircleListNode* first = sList->header.next;
        CircleListNode* last = (CircleListNode*)sList;
        int i;


        for (i=0; i<sList->length; i++) {
            last = last->next;
        }

        current = (CircleListNode*)sList;

        for (i=0; i<pos; i++) {
            current = current->next;
        }

        object = current->next;
        current->next = object->next;
        ret = (CircleListNode*)((TCircleListNode*)object)->data;

        if (sList->length == 1) {
            sList->header.next = NULL;
            sList->slider = NULL;
        } else {
            if (object == first) {
                last->next = object->next;
                sList->header.next = object->next;
            }

            if (sList->slider == object) {
                sList->slider = object->next;
            }
        }

        sList->length--;

        free(object);
    }

    return ret;
}

CircleListNodeData* CircleList_Current(CircleList* list)
{
    CircleListNodeData* ret = NULL;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL) {
        ret = (CircleListNodeData*)((TCircleListNode*)sList->slider)->data;
    }

    return ret;
}

CircleListNodeData* CircleList_Next(CircleList* list)
{
    CircleListNodeData* ret = NULL;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL && sList->slider != NULL) {
        ret = (CircleListNodeData*)((TCircleListNode*)sList->slider)->data;
        sList->slider = sList->slider->next;
    }

    return ret;
}

CircleListNodeData* CircleList_Reset(CircleList* list)
{
    CircleListNodeData* ret = NULL;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL) {
        sList->slider = sList->header.next;
        ret = (CircleListNodeData*)((TCircleListNode*)sList->slider)->data;
    }

    return ret;
}

CircleListNodeData* CircleList_DeleteNode(CircleList* list, CircleListNodeData* node)
{
    CircleListNodeData* ret = NULL;
    TCircleList* sList = (TCircleList*)list;

    if (sList != NULL && node != NULL) {
        int i;

        for (i=0; i<sList->length; i++) {
            if (node == CircleList_Get(list, i)) {
                ret = CircleList_Delete(list, i);
                break;
            }
        }

    }

    return ret;
}
