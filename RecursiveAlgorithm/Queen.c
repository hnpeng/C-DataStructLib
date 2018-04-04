#include "Queen.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int N;
    char **board;
}TQueen;

typedef struct
{
    int ios;
    int jos;
}OSPos;

void boardDisplay(Queen* queen)
{
    TQueen* sQueen = (TQueen*)queen;

    if (sQueen != NULL) {
        int i,j;

        for (i=0; i < sQueen->N+2; i++) {
            for (j=0; j < sQueen->N+2; j++) {
                printf("%c", sQueen->board[i][j]);
            }
            printf("\n");
        }
    }
}

int check(Queen* queen, int i, int j)
{
    int ret = 1;
    TQueen* sQueen = (TQueen*)queen;

    if (sQueen != NULL) {
        int index;
        OSPos osPos[3] = {{-1, -1}, {-1, 0}, {-1, 1}};

        for (index=0; index<3; index++) {
            int in = i;
            int jn = j;
            while (ret && sQueen->board[in][jn] != '#') {
                in = in + osPos[index].ios;
                jn = jn + osPos[index].jos;

                ret = ret && (sQueen->board[in][jn] != '*');
            }

            if (!ret) {
                break;
            }
        }
    } else {
        ret = 0;
    }

    return ret;
}

Queen *Queen_Create(int n)
{
    TQueen* ret = (TQueen*)malloc(sizeof(TQueen));

    if (ret != NULL) {
        ret->N = n;
        ret->board = (char**)malloc(sizeof(char*) * (ret->N+2));

        if (ret->board != NULL) {
            int i,j;

            for (i=0; i < ret->N + 2; i++) {
                ret->board[i] = (char*)malloc(sizeof(char));
            }

            for (i=0; i < ret->N + 2; i++) {
                ret->board[0][i] = '#';
                ret->board[ret->N+1][i] = '#';
                ret->board[i][0] = '#';
                ret->board[i][ret->N+1] = '#';
            }

            for (i=1; i<ret->N+1; i++) {
                for (j=1; j<ret->N+1; j++) {
                    ret->board[i][j] = ' ';
                }
            }
        } else {
            free(ret);
            ret = NULL;
        }
    }

    return ret;
}

int count = 0;

void Queen_Find(Queen* queen, int i)
{
    TQueen* sQueen = (TQueen*)queen;

    if (sQueen != NULL) {
        if (i > sQueen->N) {
            count++;
            printf("count = %d\n", count);
            boardDisplay(queen);
        } else {
            int j;

            for (j=1; j < sQueen->N+1; j++) {
                if (check(queen, i, j)) {
                    sQueen->board[i][j] = '*';
                    Queen_Find(queen, i + 1);
                    sQueen->board[i][j] = ' ';
                }
            }
        }
    }
}


void Queen_Destroy(Queen* queen)
{
    TQueen* sQueen = (TQueen*)queen;

    if (sQueen != NULL) {
        int i;

        for (i=0; i<sQueen->N+2; i++) {
            free(sQueen->board[i]);
        }

        free(sQueen->board);
        free(sQueen);
    }
}
