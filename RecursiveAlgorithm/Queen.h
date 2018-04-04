#ifndef QUEEN_H
#define QUEEN_H

typedef void Queen;

Queen* Queen_Create(int n);

void Queen_Find(Queen* queen, int i);

void Queen_Destroy(Queen* queen);

#endif
