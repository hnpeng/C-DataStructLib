#include "LinkStack.h"

#include "LinkList/LinkList.h"

LinkStack* LinkStack_Create()
{
    return LinkList_Create();
}

void LinkStack_Clear(LinkStack* stack)
{
    LinkList_Clear(stack);
}

void LinkStack_Destroy(LinkStack* stack)
{
    LinkList_Destroy(stack);
}

int LinkStack_Push(LinkStack* stack, void* item)
{
    return LinkList_Insert(stack, item, 0);
}

void* LinkStack_Pop(LinkStack* stack)
{
    return LinkList_Delete(stack, 0);
}

void* LinkStack_Top(LinkStack* stack)
{
    return LinkList_Get(stack, 0);
}

int LinkStack_Size(LinkStack* stack)
{
    return LinkList_Length(stack);
}
