#include "LittleAlgorithm/LittleAlgorithm.h"

#include <stdio.h>
#include "LittleAlgorithm/Queen.h"
#include "LittleAlgorithm/Labyrinth.h"

void LittleAlgorithmCase()
{
    char* ss = "abcdefg";
    char sa[] = "abc";

    reverseStr(ss);

    printf("\n");

    printf("strLen = %d\n", strLen(ss));

    hanoi(3, 'a', 'b', 'c');

    permutation(sa, 0, 2);

//    Queen* queen = Queen_Create(8);
//    Queen_Find(queen, 1);
//    Queen_Destroy(queen);

    Labyrinth_Find(17, 0);

}
