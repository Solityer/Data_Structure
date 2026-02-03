#pragma once
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

// 前置声明：告诉编译器 BinaryTreeNode 是一个结构体，具体定义在后面。
// 这样可以在 Queue 中存储指向树节点的指针。
struct BinaryTreeNode;
typedef struct BinaryTreeNode *QDataType; // 队列存储的是树节点的指针

typedef struct QueueNode
{
    struct QueueNode *next;
    QDataType data;
} QNode;

typedef struct Queue
{
    QNode *phead; // 队头（出队）
    QNode *ptail; // 队尾（入队）
    int size; // 计数器，避免遍历计算大小时 O(N)
} Queue;

void QueueInit(Queue *pq);

void QueueDestroy(Queue *pq);

void QueuePush(Queue *pq, QDataType x);

void QueuePop(Queue *pq);

QDataType QueueFront(Queue *pq);

QDataType QueueBack(Queue *pq);

int QueueSize(Queue *pq);

bool QueueEmpty(Queue *pq);
