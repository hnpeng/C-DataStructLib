#include "SearchCase.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Search/Search.h"
#include "SortAlgorithm/SortAlgorithm.h"

#define SIZE 50

void SearchCase()
{
    int a[SIZE] = {0};
    int index = -1;
    int i;
    int key;

    srand((unsigned int)time(NULL));

    for (i=0; i<SIZE; i++) {
        a[i] = rand() % 100;
    }

    key = rand() % 100;

    MergeSort(a, SIZE);
//    index = Feibo_Search(a, 0, SIZE-1, key);
    index = Interpolation_Search(a, 0, SIZE-1, key);
//    index = Binary_Search_Ex(a, 0, SIZE-1, key);
//    index = Binary_Search(a, 0, SIZE-1, key);
//    index = Static_Search(a, SIZE, key);

    if (index >= 0) {
        printf("array:\n");
        Print_Arr(a, SIZE);
        printf("Succes!\n");
        printf("key = %d, index = %d\n", key, index);
    } else {
        Print_Arr(a, SIZE);
        printf("Fail!\n");
        printf("key = %d, index = %d\n", key, index);
    }


//    SeqList* list = SeqList_Create(SIZE);
//
//    for (i=0; i<SIZE; i++) {
//        SeqList_Insert(list, (SeqListNode*)(a + i), i);
//    }
//
//    Print_SeqList(list);
//
//    index = Dynamic_Search(list, key);
//
//    if (index != -1) {
//        Print_SeqList(list);
//        printf("Succes!\n");
//        printf("key = %d, index = %d\n", key, index);
//    } else {
//        Print_SeqList(list);
//        printf("Fail!\n");
//        printf("key = %d, index = %d\n", key, index);
//    }
//
//    SeqList_Destroy(list);
//    int a[SIZE+1] = {0};
//    int index = -1;
//    int i;
//    int key;
//
//    srand((unsigned int)time(NULL));
//
//    for (i=1; i<=SIZE; i++) {
//        a[i] = rand() % 100;
//    }
//
//    key = rand() % 100;
//
//    index = Another_Search(a, SIZE, key);
//
//    if (index > 0) {
//        Print_Arr(a, SIZE);
//        printf("succes!\n");
//        printf("key = %d, index = %d\n", key, index);
//    } else {
//        Print_Arr(a, SIZE);
//        printf("Fail!\n");
//        printf("key = %d, index = %d\n", key, index);
//
//    }

}

void OthreCase()
{
    int a[] = {1, 1, 2, 3, 2, 3, 4, 4, 6, 5, 7, 5, 6, 7, 10};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10};

    printf("single number = %d\n", FindTheSingleNumber(a, sizeof(a) / sizeof(*a)));
    printf("duplicate number = %d\n", FindTheDuplicateNumber(b, sizeof(b) / sizeof(*b)));
}
