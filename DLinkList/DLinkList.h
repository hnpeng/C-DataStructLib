#ifndef DLINKLIST_H
#define DLINKLIST_H

typedef void DLinkList;
typedef void DLinkListNode;

DLinkList* DLinkList_Create();

void DLinkList_Clear(DLinkList* list);

void DLinkList_Destroy(DLinkList* list);

int DLinkList_Length(DLinkList* list);

int DLinkList_Insert(DLinkList* list, DLinkListNode* node, int pos);

DLinkListNode* DLinkList_Get(DLinkList* list, int pos);

DLinkListNode* DLinkList_Delete(DLinkList* list, int pos);

DLinkListNode* DLinkList_Reset(DLinkList* list);

DLinkListNode* DLinkList_Current(DLinkList* list);

DLinkListNode* DLinkList_Next(DLinkList* list);

DLinkListNode* DLinkList_Pre(DLinkList* list);

DLinkListNode* DLinkList_DeleteNode(DLinkList* list, DLinkListNode* node);

#endif //DLINKLIST_H
