#pragma once
#include<stdlib.h>  // 标准库头文件，提供malloc、free等内存管理函数
#include<assert.h>  // 断言头文件，用于运行时检查条件是否满足
#include<stdbool.h> // 布尔类型头文件，提供bool、true、false定义

// 前置声明：告诉编译器 BinaryTreeNode 是一个结构体，具体定义在其他文件中
// 作用：避免头文件循环包含，同时允许在 Queue 中使用指向树节点的指针
struct BinaryTreeNode;

// 定义队列数据类型：存储二叉树节点的指针
// 设计思路：队列作为辅助数据结构，用于二叉树的层序遍历等算法
typedef struct BinaryTreeNode *QDataType;

// 队列节点结构体定义
typedef struct QueueNode
{
    struct QueueNode *next;  // 指向下一个队列节点，形成链表结构
    QDataType data;          // 数据域：存储二叉树节点指针
} QNode;

// 队列结构体定义
typedef struct Queue
{
    QNode *phead;
    QNode *ptail;
    int size;
} Queue;

// 初始化队列：将队列结构体各成员设置为初始状态
void QueueInit(Queue *pq);

// 销毁队列：释放队列中所有节点占用的内存，防止内存泄漏
void QueueDestroy(Queue *pq);

// 入队操作：在队尾插入一个新元素
void QueuePush(Queue *pq, QDataType x);

// 出队操作：删除队头元素
void QueuePop(Queue *pq);

// 获取队头元素：返回队头数据但不删除
QDataType QueueFront(Queue *pq);

// 获取队尾元素：返回队尾数据但不删除
QDataType QueueBack(Queue *pq);

// 获取队列大小：返回当前队列中元素的个数
int QueueSize(Queue *pq);

// 判断队列是否为空：队列为空返回true，非空返回false
bool QueueEmpty(Queue *pq);