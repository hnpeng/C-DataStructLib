#ifndef LINKLIST_H
#define LINKLIST_H

typedef void LinkListNode;
typedef void LinkList;

LinkList* LinkList_Create();

void LinkList_Clear(LinkList* list);

void LinkList_Destroy(LinkList* list);

int LinkList_Length(LinkList* list);

int LinkList_Insert(LinkList* list, LinkListNode* node, int pos);

LinkListNode* LinkList_Get(LinkList* list, int pos);

LinkListNode* LinkList_Delete(LinkList* list, int pos);

void LinkList_Reverse(LinkList* list);

LinkListNode* LinkList_GetMidNode(LinkList* list);

#endif // LINKLIST_H
