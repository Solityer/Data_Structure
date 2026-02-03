#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

// 定义堆的数据类型
typedef int HPDataType;

typedef struct Heap
{
    HPDataType *a; // 指向动态数组的指针
    int size; // 当前有效元素个数
    int capacity; // 数组的总容量
} HP;

// 核心调整算法（内部接口）
void Swap(HPDataType *p1, HPDataType *p2);

void AdjustUp(HPDataType *a, int child);

void AdjustDown(int *a, int n, int parent);

// 堆的对外接口
void HeapInit(HP *php);

void HeapDestroy(HP *php);

void HeapPush(HP *php, HPDataType x); // O(logN)
void HeapPop(HP *php); // O(logN)
HPDataType HeapTop(HP *php); // O(1)
bool HeapEmpty(HP *php);

int HeapSize(HP *php);
