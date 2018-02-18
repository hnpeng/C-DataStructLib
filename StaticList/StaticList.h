#ifndef STATICLIST_H
#define STATICLIST_H

typedef void StaticList;
typedef void StaticListNode;

StaticList* StaticList_Create(int capacity);

void StaticList_Clear(StaticList* list);

void StaticList_Destroy(StaticList* list);

int StaticList_Length(StaticList* list);

int StaticList_Capacity(StaticList* list);

int StaticList_Insert(StaticList* list, StaticListNode* node, int pos);

StaticListNode* StaticList_Get(StaticList* list, int pos);

StaticListNode* StaticList_Delete(StaticList* list, int pos);


#endif // STATICLIST_H
