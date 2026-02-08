#include "Queue.h"
#include <stdio.h> // 补充引入，防止 perror 报错

// 初始化队列
/*pq：这是一个指向 Queue 结构体的指针
	即 Queue* 类型
	它指向一个包含队列头尾指针和大小信息的结构体*/
void QueueInit(Queue *pq)
{
    assert(pq); // 确保pq不为空
    pq->phead = NULL; // 头指针置空
    pq->ptail = NULL; // 尾指针置空
    pq->size = 0;     // 队列大小初始化为0
}

// 销毁队列，释放所有节点内存
void QueueDestroy(Queue *pq)
{
    assert(pq); // 确保pq不为空
    QNode *cur = pq->phead; // 从头节点开始遍历
    while (cur)
    {
        QNode *next = cur->next; // 保存下一个节点地址
        free(cur); // 释放当前节点
        cur = next; // 移动到下一个节点
    }
    // 重置队列状态
    pq->phead = pq->ptail = NULL;
    pq->size = 0;
}

// 入队操作，在队尾添加元素
void QueuePush(Queue *pq, QDataType x)
{
    assert(pq); // 确保pq不为空
    QNode *newnode = (QNode *) malloc(sizeof(QNode));
    if (newnode == NULL)
    {
        perror("malloc fail\n"); // 内存分配失败提示
        return;
    }
    newnode->data = x; // 设置新节点数据
    newnode->next = NULL; // 新节点next指针置空

    // 情况1：队列为空，新节点既是头节点也是尾节点
    if (pq->ptail == NULL)
    {
        assert(pq->phead == NULL); // 此时头节点也应该为空
        pq->phead = pq->ptail = newnode;
    }
    else // 情况2：队列非空，将新节点链接到尾节点后面
    {
        pq->ptail->next = newnode;
        pq->ptail = newnode; // 更新尾指针
    }
    pq->size++; // 队列大小加1
}

// 出队操作，移除队头元素
void QueuePop(Queue *pq)
{
    assert(pq); // 确保pq不为空
    assert(!QueueEmpty(pq)); // 确保队列非空

    // 情况1：队列只有一个节点
    if (pq->phead->next == NULL)
    {
        free(pq->phead); // 释放该节点
        pq->phead = pq->ptail = NULL; // 队列置空
    }
    else // 情况2：队列有多个节点，执行头删操作
    {
        QNode *next = pq->phead->next; // 保存第二个节点地址
        free(pq->phead); // 释放头节点
        pq->phead = next; // 更新头指针
    }
    pq->size--; // 队列大小减1
}

// 获取队头元素（不删除）
QDataType QueueFront(Queue *pq)
{
    assert(pq); // 确保pq不为空
    assert(!QueueEmpty(pq)); // 确保队列非空
    return pq->phead->data; // 返回头节点数据
}

// 获取队尾元素（不删除）
QDataType QueueBack(Queue *pq)
{
    assert(pq); // 确保pq不为空
    assert(!QueueEmpty(pq)); // 确保队列非空
    return pq->ptail->data; // 返回尾节点数据
}

// 获取队列当前元素个数
int QueueSize(Queue *pq)
{
    assert(pq); // 确保pq不为空
    return pq->size; // 返回队列大小
}

// 判断队列是否为空
bool QueueEmpty(Queue *pq)
{
    assert(pq); // 确保pq不为空
    return pq->size == 0; // 队列为空返回true，非空返回false
}