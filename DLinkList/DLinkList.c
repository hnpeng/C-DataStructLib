#include "DLinkList.h"

#include <stdlib.h>

typedef struct __tag_TDLinkListNode TDLinkListNode;
struct __tag_TDLinkListNode
{
    TDLinkListNode* next;
    TDLinkListNode* pre;
};

typedef struct
{
    TDLinkListNode header;
    void* tNode;
}TNode;

typedef struct
{
    TDLinkListNode header;
    int length;
    TDLinkListNode* slider;
}TDLinkList;

DLinkList* DLinkList_Create()
{
    TDLinkList* ret = (TDLinkList*)malloc(sizeof(TDLinkList));

    if (ret != NULL) {
        ret->header.next = NULL;
        ret->header.pre = NULL;
        ret->length = 0;
    }

    return ret;
}

void DLinkList_Clear(DLinkList* list)
{
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL) {
        while (sList->length > 0) {
            DLinkList_Delete(sList, 0);
        }
    }
}

void DLinkList_Destroy(DLinkList* list)
{
    DLinkList_Clear(list);
    free(list);
}

int DLinkList_Length(DLinkList* list)
{
    int ret = -1;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int DLinkList_Insert(DLinkList* list, DLinkListNode* node, int pos)
{
    TDLinkList* sList = (TDLinkList*)list;
    int ret = sList != NULL && node != NULL && pos >= 0;

    if (ret) {
        TNode* newNode = (TNode*)malloc(sizeof(TNode));
        ret = newNode != NULL;

        if (ret) {
            TDLinkListNode* current = (TDLinkListNode*)sList;
            TDLinkListNode* next = NULL;
            int i;

            for (i=0; i<pos && sList->header.next != NULL; i++) {
                current = current->next;
            }

            newNode->tNode = node;
            next = current->next;

            current->next = (TDLinkListNode*)newNode;
            newNode->header.next = next;

            if (next != NULL) {
                next->pre = (TDLinkListNode*)newNode;
            }

            newNode->header.pre = current;

            if (pos == 0) {
                newNode->header.pre = NULL;
                sList->slider = sList->header.next;
            }

            sList->length++;
        }
    }

    return ret;
}

DLinkListNode* DLinkList_Get(DLinkList* list, int pos)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL && 0 <= pos && pos < sList->length) {
        TDLinkListNode* current = (TDLinkListNode*)sList;
        TNode* targetNode = NULL;
        int i;

        for (i=0; i<pos; i++) {
            current = current->next;
        }

        targetNode = (TNode*)current->next;
        ret = (DLinkListNode*)targetNode->tNode;
    }

    return ret;
}

DLinkListNode* DLinkList_Delete(DLinkList* list, int pos)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL && 0 <= pos && pos < sList->length) {
        TDLinkListNode* current = (TDLinkListNode*)sList;
        TNode* targetNode = NULL;
        int i;

        for (i=0; i<pos; i++) {
            current = current->next;
        }

        targetNode = (TNode*)current->next;
        ret = (DLinkListNode*)targetNode->tNode;

        current->next = targetNode->header.next;

        if (targetNode->header.next != NULL) {
            targetNode->header.next->pre = current;

            if (current == (TDLinkListNode*)sList)
                targetNode->header.next->pre = NULL;
        }

        if ((TDLinkListNode*)targetNode == sList->slider) {
            sList->slider = sList->slider->next;
        }

        sList->length--;
        free(targetNode);
    }

    return ret;
}

DLinkListNode* DLinkList_Reset(DLinkList* list)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL) {
        sList->slider = sList->header.next;

        if (sList->slider != NULL)
            ret = ((TNode*)sList->slider)->tNode;
    }

    return ret;
}

DLinkListNode* DLinkList_Current(DLinkList* list)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL) {
        if (sList->slider != NULL)
            ret = ((TNode*)sList->slider)->tNode;
    }

    return ret;
}

DLinkListNode* DLinkList_Next(DLinkList* list)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL) {
        if (sList->slider != NULL) {
            ret = ((TNode*)sList->slider)->tNode;
            sList->slider = sList->slider->next;
        }
    }

    return ret;
}

DLinkListNode* DLinkList_Pre(DLinkList* list)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL) {
        if (sList->slider != NULL) {
            ret = ((TNode*)sList->slider)->tNode;
            sList->slider = sList->slider->pre;
        }
    }

    return ret;
}

DLinkListNode* DLinkList_DeleteNode(DLinkList* list, DLinkListNode* node)
{
    DLinkListNode* ret = NULL;
    TDLinkList* sList = (TDLinkList*)list;

    if (sList != NULL && node != NULL) {
        int i;

        for (i=0; i<sList->length; i++) {
            if (DLinkList_Get(sList, i) == node) {
                ret = DLinkList_Delete(sList, i);
                break;
            }
        }
    }

    return ret;
}
