#pragma once
#include<stdio.h>    // 标准输入输出，用于perror等错误处理
#include<stdlib.h>   // 标准库，提供malloc、free、realloc等内存管理函数
#include<assert.h>   // 断言库，用于程序运行时检查条件，防止非法操作
#include<stdbool.h>  // 布尔类型库，提供bool、true、false定义

// 堆数据类型定义
// 说明：根据实际需求可以修改为其他类型（如double、结构体指针等）
// 注意：如果修改为结构体类型，需要自定义比较规则
typedef int HPDataType;

// 堆结构体定义
// 设计思路：使用动态数组实现完全二叉树的存储
// 优势：利用数组下标快速定位父子节点，内存连续访问效率高
typedef struct Heap
{
    HPDataType *a;   // 指向动态数组的指针，存储堆元素
    int size;        // 当前堆中有效元素个数
    int capacity;    // 数组总容量，用于动态扩容
} HP;

// 核心调整算法（内部接口）
// 说明：这些函数主要在堆的其他操作中被调用，通常不直接对外暴露

// 交换两个元素的值
// 参数：p1, p2 - 指向待交换元素的指针
void Swap(HPDataType *p1, HPDataType *p2);

// 向上调整算法（用于插入操作）
// 时间复杂度：O(logN)，其中N为堆的高度
// 参数：a - 堆数组指针，child - 新插入元素的下标
// 注意：默认实现为小堆，改为大堆需修改比较条件
void AdjustUp(HPDataType *a, int child);

// 向下调整算法（用于删除堆顶和堆排序）
// 时间复杂度：O(logN)，其中N为堆的高度
// 参数：a - 堆数组指针，n - 堆中元素个数，parent - 需要调整的起始位置
// 注意：默认实现为小堆，改为大堆需修改比较条件
void AdjustDown(int *a, int n, int parent);

// ==================== 堆的对外接口 ====================
// 说明：这些函数提供堆的基本操作，是用户可以调用的API

// 初始化堆
// 参数：php - 指向堆结构体的指针
// 注意：必须在使用堆之前调用，否则行为未定义
void HeapInit(HP *php);

// 销毁堆，释放动态分配的内存
// 参数：php - 指向堆结构体的指针
// 重要：使用完堆后必须调用，防止内存泄漏
void HeapDestroy(HP *php);

// 向堆中插入元素
// 参数：php - 指向堆结构体的指针，x - 待插入的元素值
// 实现：1.在数组末尾插入 2.执行向上调整恢复堆性质
void HeapPush(HP *php, HPDataType x);

// 删除堆顶元素
// 参数：php - 指向堆结构体的指针
// 实现：1.交换堆顶和堆底 2.删除堆底 3.向下调整恢复堆性质
// 注意：删除前必须确保堆非空，否则assert会触发
void HeapPop(HP *php);

// 获取堆顶元素（不删除）
// 参数：php - 指向堆结构体的指针
// 返回值：堆顶元素的值
// 注意：调用前必须确保堆非空
HPDataType HeapTop(HP *php);

// 判断堆是否为空
// 参数：php - 指向堆结构体的指针
// 返回值：true表示堆为空，false表示堆非空
bool HeapEmpty(HP *php);

// 获取堆中元素个数
// 参数：php - 指向堆结构体的指针
// 返回值：当前堆中的元素数量
int HeapSize(HP *php);