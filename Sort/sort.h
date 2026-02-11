#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 打印数组
void PrintArray(int* a, int n);

// 插入排序类
void InsertSort(int* a, int n);
void ShellSort(int* a, int n);

// 选择排序类
void BubbleSort(int* a, int n);
void SelectSort(int* a, int n);
void HeapSort(int* a, int n);

// 快速排序类
void QuickSort(int* a, int begin, int end);
void QuickSortNonR(int* a, int begin, int end); // 非递归

// 归并排序类
void MergeSort(int* a, int n);
void MergeSortNonR(int* a, int n); // 非递归

// 非比较排序
void CountSort(int* a, int n);