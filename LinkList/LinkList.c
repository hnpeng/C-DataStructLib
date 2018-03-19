#include "LinkList.h"

#include <stdlib.h>

//typedef struct __linkList_node LinkListNode;
//struct __linkList_node
//{
//    LinkListNode* next;
//};

typedef struct __tag_linkListNode TLinkListNode;
struct __tag_linkListNode
{
    TLinkListNode* next;
};

typedef struct
{
    TLinkListNode tNode;
    void* value;
}TNode;


typedef struct
{
    TLinkListNode headNode;
    int length;
}TLinkList;

LinkList* LinkList_Create()
{
    TLinkList* ret = (TLinkList*)malloc(sizeof(TLinkList));

    if (ret) {
        ret->length = 0;
        ret->headNode.next = NULL;
    }

    return ret;
}

void LinkList_Clear(LinkList* list)
{
    TLinkList* sList = (TLinkList*)list;

    if (sList != NULL) {
        while (sList->length > 0) {
            LinkList_Delete(list, 0);
        }
    }
}

void LinkList_Destroy(LinkList* list)
{
    LinkList_Clear(list);
    free(list);
}

int LinkList_Length(LinkList* list)
{
    TLinkList* sList = (TLinkList*)list;
    int ret = -1;

    if (sList != NULL) {
        ret = sList->length;
    }

    return ret;
}

int LinkList_Insert(LinkList* list, LinkListNode* node, int pos)
{
    TLinkList* sList = (TLinkList*)list;
    int ret = sList != NULL && node != NULL && pos >= 0;

    if (ret) {
        TNode* newNode = (TNode*)malloc(sizeof(TNode));
        ret = newNode != NULL;

        if (ret) {
            TLinkListNode* current = (TLinkListNode*)sList;
            int i;

            for (i = 0; i<pos && current->next != NULL; i++) {
                current = current->next;
            }

            newNode->value = node;
            newNode->tNode.next = current->next;
            current->next = (TLinkListNode*)newNode;

            sList->length++;
        }
    }

    return ret;
}

LinkListNode* LinkList_Get(LinkList* list, int pos)
{
    LinkListNode* ret = NULL;
    TLinkList* sList = (TLinkList*)list;
    int i;

    if (sList != NULL && 0 <= pos && pos < sList->length) {
        TLinkListNode* current = (TLinkListNode*)sList;
        TNode* targetNode = NULL;

        for (i=0; i<pos; i++) {
            current = current->next;
        }

        targetNode = (TNode*)current->next;
        ret = targetNode->value;
    }

    return ret;
}

LinkListNode* LinkList_Delete(LinkList* list, int pos)
{
    LinkListNode* ret = NULL;
    TLinkList* sList = (TLinkList*)list;
    int i;

    if (sList != NULL && 0 <= pos && pos < sList->length) {
        TLinkListNode* current = (TLinkListNode*)sList;
        TNode* targetNode = NULL;

        for (i=0; i<pos; i++) {
            current = current->next;
        }

        targetNode = (TNode*)current->next;
        current->next = targetNode->tNode.next;
        ret = targetNode->value;

        free(targetNode);

        sList->length--;
    }

    return ret;
}

//void LinkList_Reverse(LinkList *list)
//{
//    TLinkList* sList = (TLinkList*)list;

//    if (sList != NULL) {
//        TLinkListNode* curNode = sList->headNode;
//        TLinkListNode* preNode = NULL;

//        while (curNode != NULL) {
//            TLinkListNode* nextNode = curNode->next;
//            curNode->next = preNode;
//            preNode = curNode;
//            curNode = nextNode;
//        }

//        sList->headNode = preNode;
//    }
//}

TLinkListNode* recursiveReverse(TLinkListNode* node)
{
    TLinkListNode* ret = node;

    if (node->next != NULL) {
        TLinkListNode* nextNode = node->next;
        ret = recursiveReverse(nextNode);
        nextNode->next = node;
        node->next = NULL;
    }

    return ret;
}

void LinkList_Reverse(LinkList* list)
{
    TLinkList* sList = (TLinkList*)list;
    if (sList != NULL) {
        TLinkListNode* headNode = sList->headNode.next;

        sList->headNode.next = recursiveReverse(headNode);
    }
}

LinkListNode *LinkList_GetMidNode(LinkList *list)
{
    LinkListNode* ret = NULL;
    TLinkList* sList = (TLinkList*)list;

    if (sList != NULL) {
        TLinkListNode* pForward = sList->headNode.next;
        TLinkListNode* pSlowForward = sList->headNode.next;
        int count = 0;

        while (pForward != NULL) {
            pForward = pForward->next;
            count++;
            if (count % 2 == 0) {
                pSlowForward = pSlowForward->next;
            }
        }

        ret = ((TNode*)pSlowForward)->value;
    }

    return ret;
}
