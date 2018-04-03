#ifndef SSTACK_H
#define SSTACK_H

typedef void SStack;

SStack* SStack_Create();

void SStack_Clear(SStack* stack);

void SStack_Destroy(SStack* stack);

int SStack_Push(SStack* stack, void* item);

void* SStack_Pop(SStack* stack);

void* SStack_Top(SStack* stack);

int SStack_Size(SStack* stack);

#endif
