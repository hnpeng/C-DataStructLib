#include "SortAlgorithm.h"

#include <stdio.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void PrintArray(int arr[], int len)
{
    int i;

    for (i=0; i<len; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void SelectionSort(int arr[], int len)
{
    int i, j, k;

    for (i=0; i<len; i++) {
        k = i;

        for (j=i; j<len; j++) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }

        swap(&arr[k], &arr[i]);
    }
}

void InsertionSort(int arr[], int len)
{
    int i, j, k;

    for (i=1; i<len; i++) {
        k = i;
        int temp = arr[k];

        for (j=i-1; j>=0 && temp < arr[j]; j--) {
            arr[j+1] = arr[j];
            k = j;
        }

        arr[k] = temp;
    }
}

void BubbleSort(int arr[], int len)
{
    int i, j;
    int exchange = 1;

    for (i=0; i<len-1 && exchange; i++) {

        exchange = 0;

        for (j=len-1; j>i; j--) {
            if (arr[j] < arr[j-1]) {
                swap(&arr[j], &arr[j-1]);
                exchange = 1;
            }
        }
    }
}

void ShellSort(int arr[], int len)
{
    int i, j, k;
    int gap = len;

    do {
        gap = gap / 3 + 1;

        for (i=gap; i<len; i+=gap) {
            k = i;
            int temp = arr[k];

            for (j=i-gap; j >= 0 && temp < arr[j]; j-=gap) {
                arr[j + gap] = arr[j];
                k = j;
            }

            arr[k] = temp;
        }

    } while (gap > 1);
}

void ShellBubble(int arr[], int len)
{
    int i,j;
    int gap = len;

    do {
        gap = gap / 3 + 1;

        int exchange = 1;
        for (i=0; i<len-gap && exchange; i+=gap) {
            exchange = 0;
            for (j=len-1; j>i; j-=gap) {
                if (arr[j] < arr[j-gap]) {
                    swap(&arr[j], &arr[j-gap]);
                    exchange = 1;
                }
            }
        }
    } while (gap > 1);
}

int partition(int arr[], int low, int high)
{
    int i = low;
    int j = high;
    int temp = arr[i];

    while (i < j) {
        while (arr[j] >= temp && i < j) {
            j--;
        }

        arr[i] = arr[j];

        while (arr[i] <= temp && i < j) {
            i++;
        }

        arr[j] = arr[i];
    }

    arr[i] = temp;

    return i;
}

void QSort(int arr[], int low, int high)
{
    if (low < high) {
        int pos = partition(arr, low, high);

        QSort(arr, low, pos-1);
        QSort(arr, pos+1, high);
    }
}

void QuickSort(int arr[], int len)
{
    QSort(arr, 0, len-1);
}

void Merge(int arr[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;
    int buf[high - low + 1];
    int index;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            buf[k++] = arr[i++];
        } else {
            buf[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        buf[k++] = arr[i++];
    }

    while (j <= high) {
        buf[k++] = arr[j++];
    }

    k = 0;

    for (index = low; index <= high; index++) {
        arr[index] = buf[k++];
    }
}

void MSort(int arr[], int low, int high)
{
    if (low < high) {
        int mid = (low + high) / 2;

        MSort(arr, low, mid);
        MSort(arr, mid + 1, high);

        Merge(arr, low, mid, high);
    }
}

void MergeSort(int arr[], int len)
{

    MSort(arr, 0, len - 1);
}
