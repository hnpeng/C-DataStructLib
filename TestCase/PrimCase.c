#include "PrimCase.h"
#include <stdio.h>

#define VNUM 9
#define MV 65535

int P[VNUM];
int Cost[VNUM];
int Mark[VNUM];
int Matrix[VNUM][VNUM] = {
    {0, 10, MV, MV, MV, 11, MV, MV, MV},
    {10, 0, 18, MV, MV, MV, 16, MV, 12},
    {MV, 18, 0, 22, MV, MV, MV, MV, 8},
    {MV, MV, 22, 0, 20, MV, 24, 16, 21},
    {MV, MV, MV, 20, 0, 26, MV, 7, MV},
    {11, MV, MV, MV, 26, 0, 17, MV, MV},
    {MV, 16, MV, 24, MV, 17, 0, 19, MV},
    {MV, MV, MV, 16, 7, MV, 19, 0, MV},
    {MV, 12, 8, 21, MV, MV, MV, MV, 0},
};

void PrimCase(int sv)
{
    int i, j;

    for (i=0; i<VNUM; i++) {
        Cost[i] = Matrix[sv][i];
        Mark[i] = 0;
        P[i] = sv;
    }

    Mark[sv] = 1;

    for (i=0; i<100; i++) {
        int min = MV;
        int index = -1;

        for (j=0; j<VNUM; j++) {
//            if (Cost[j] < min && !Mark[j]) {
            if (Cost[j] < min && !Mark[j]) {
                min = Cost[j];
                index = j;
            }
        }

        if (index != -1) {
            Mark[index] = 1;
            printf("%d-%d-%d\n", P[index], index, Cost[index]);

            for (j=0; j<VNUM; j++) {
                if (Matrix[index][j] < Cost[j] && !Mark[j]) {
                    Cost[j] = Matrix[index][j];
                    P[j] = index;
                }
            }
        }
    }
}
