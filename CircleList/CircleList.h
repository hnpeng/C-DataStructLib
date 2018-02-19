#ifndef CIRCLELIST_H
#define CIRCLELIST_H

typedef void CircleList;
typedef void CircleListNodeData;

CircleList* CircleList_Create();

void CircleList_Clear(CircleList* list);

void CircleList_Destroy(CircleList* list);

int CircleList_Length(CircleList* list);

int CircleList_Insert(CircleList* list, CircleListNodeData* node, int pos);

CircleListNodeData* CircleList_Get(CircleList* list, int pos);

CircleListNodeData* CircleList_Delete(CircleList* list, int pos);

CircleListNodeData* CircleList_Current(CircleList* list);

CircleListNodeData* CircleList_Next(CircleList* list);

CircleListNodeData* CircleList_Reset(CircleList* list);

CircleListNodeData* CircleList_DeleteNode(CircleList* list, CircleListNodeData* node);

#endif // CIRCLELIST_H
