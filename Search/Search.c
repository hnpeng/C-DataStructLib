#include "Search.h"

#include <stdio.h>
#include <stdlib.h>
#include "SeqList/SeqList.h"


int Static_Search(int a[], int len, int key)
{
    int ret = -1;
    int i;

    for (i=0; i<len; i++) {
        if (a[i] == key) {
            ret = i;
            break;
        }
    }

    return ret;
}

int Dynamic_Search(SeqList* list, int key)
{
    int ret = -1;
    int i;
    int *num;

    for (i=0; i<SeqList_Length(list); i++) {
        num = (int*)SeqList_Get(list, i);
        if (*num == key) {
            SeqList_Delete(list, i);
            ret = i;
            break;
        }
    }

    return ret;

}

void Print_Arr(int arr[], int len)
{
    int i;

    for (i=0; i<len; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void Print_SeqList(SeqList* list)
{
    int i;

    for (i=0; i<SeqList_Length(list); i++) {
        printf("%d ", *(int*)SeqList_Get(list, i));
    }

    printf("\n");
}

int Another_Search(int a[], int len, int key)
{
    int ret = len;

    a[0] = key;

    while (a[ret] != a[0]) {
        ret--;
    }

    return ret;
}

int Binary_Search(int a[], int low, int high, int key)
{
    int ret = -1;

    if (low <= high) {
        int mid = (low + high) / 2;

        if (a[mid] == key) {
            ret = mid;
        } else if (key < mid) {
            ret = Binary_Search(a, low, mid - 1, key);
        } else {
            ret = Binary_Search(a, mid + 1, high, key);
        }
    }

    return ret;
}

int Binary_Search_Ex(int a[], int low, int high, int key)
{
    int ret = -1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;

        if (a[mid] == key) {
            ret = mid;
            break;
        } else if (key < a[mid]) {
            high = mid -1;
        } else {
            low = mid + 1;
        }
    }

    return ret;
}

int Interpolation_Search(int a[], int low, int high, int key)
{
    int ret = -1;
    float f;
    int mid;

    while (low <= high && a[low] <= key && key <= a[high]) {
        f = 1.0f * (key - a[low]) / (a[high] - a[low]);
        mid = (int)(low + f * (high - low));

        if (a[mid] == key) {
            ret = mid;
            break;
        } else if (key < a[mid]) {
            high = mid -1;
        } else {
            low = mid + 1;
        }
    }

    return ret;
}

int feibo_func()
{
    int ret = 0;
    static int last = 1;
    static int lastlast = 0;

    ret = last + lastlast;
    lastlast = last;
    last = ret;

    return ret;
}

int Feibo_Search(int a[], int low, int high, int key)
{
    int ret = -1;
    int mid;

    while (low <= high && a[low] <= key && key <= a[high]) {
        mid = low + feibo_func();

        if (key == a[mid]) {
            ret = mid;
            break;
        } else if (key < a[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ret;
}


int FindTheSingleNumber(int arr[], int len)
{
    int ret = 0;
    int i;
    int buf[20] = {0};

    for (i=0; i<len; i++) {
        buf[arr[i]]++;
    }

    for (i=0; i<20; i++) {
        if (buf[i] == 1) {
            ret = i;
        }
    }

    return ret;
}

int FindTheDuplicateNumber(int arr[], int len)
{
    int ret = 0;
    int i;
    int buf[20] = {0};

    for (i=0; i<len; i++) {
        buf[arr[i]]++;
    }

    for (i=0; i<20; i++) {
        if (buf[i] == 2) {
            ret = i;
        }
    }

    return ret;
}
