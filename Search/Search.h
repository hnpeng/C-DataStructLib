#ifndef SEARCH_H
#define SEARCH_H

#include "SeqList/SeqList.h"

int Static_Search(int a[], int len, int key);

int Dynamic_Search(SeqList* list, int key);

int Another_Search(int a[], int len, int key);

int Binary_Search(int a[], int low, int high, int key);

int Binary_Search_Ex(int a[], int low, int high, int key);

int Interpolation_Search(int a[], int low, int high, int key);

int Feibo_Search(int a[], int low, int high, int key);

void Print_Arr(int arr[], int len);

void Print_SeqList(SeqList* list);

int FindTheSingleNumber(int arr[], int len);

int FindTheDuplicateNumber(int arr[], int len);

#endif
