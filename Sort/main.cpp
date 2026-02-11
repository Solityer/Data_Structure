#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sort.h"

// 性能测试函数
void TestOP()
{
	srand((unsigned int)time(0));
	const int N = 100000; // 测试数据量，可以改为 1000000

	// 创建多个相同的数组，用于公平对比不同算法
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);
	int* a8 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
		a7[i] = a1[i];
		a8[i] = a1[i];
	}

	// 1. 插入排序
	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();

	// 2. 希尔排序
	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();

	// 3. 冒泡排序
	int begin3 = clock();
	BubbleSort(a3, N);
	int end3 = clock();

	// 4. 选择排序
	int begin4 = clock();
	SelectSort(a4, N);
	int end4 = clock();

	// 5. 堆排序
	int begin5 = clock();
	HeapSort(a5, N);
	int end5 = clock();

	// 6. 快速排序
	int begin6 = clock();
	QuickSort(a6, 0, N - 1);
	int end6 = clock();

	// 7. 归并排序
	int begin7 = clock();
	MergeSort(a7, N);
	int end7 = clock();

	// 8. 计数排序
	int begin8 = clock();
	CountSort(a8, N);
	int end8 = clock();

	printf("数据量 N = %d\n", N);
	printf("InsertSort: %d ms\n", end1 - begin1);
	printf("ShellSort:  %d ms\n", end2 - begin2);
	printf("BubbleSort: %d ms\n", end3 - begin3);
	printf("SelectSort: %d ms\n", end4 - begin4);
	printf("HeapSort:   %d ms\n", end5 - begin5);
	printf("QuickSort:  %d ms\n", end6 - begin6);
	printf("MergeSort:  %d ms\n", end7 - begin7);
	printf("CountSort:  %d ms\n", end8 - begin8);

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);
	free(a8);
}

int main()
{
    // 可以单独测试某个排序
	int a[] = { 6, 1, 2, 7, 9, 3, 4, 5, 10, 8 };
	int n = sizeof(a) / sizeof(int);
	QuickSort(a, 0, n - 1);
	PrintArray(a, n);

    // 运行性能基准测试
	TestOP();

	return 0;
}