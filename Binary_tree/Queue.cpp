#include "Queue.h"
#include <stdio.h> // 补充引入，防止 perror 报错

void QueueInit(Queue *pq)
{
    assert(pq);
    pq->phead = NULL;
    pq->ptail = NULL;
    pq->size = 0;
}

void QueueDestroy(Queue *pq)
{
    assert(pq);
    QNode *cur = pq->phead;
    while (cur)
    {
        QNode *next = cur->next;
        free(cur); // 释放链表节点
        cur = next;
    }
    pq->phead = pq->ptail = NULL;
    pq->size = 0;
}

void QueuePush(Queue *pq, QDataType x)
{
    assert(pq);
    QNode *newnode = (QNode *) malloc(sizeof(QNode));
    if (newnode == NULL)
    {
        perror("malloc fail\n");
        return;
    }
    newnode->data = x;
    newnode->next = NULL;

    // 边界情况：队列为空
    if (pq->ptail == NULL)
    {
        assert(pq->phead == NULL);
        pq->phead = pq->ptail = newnode;
    }
    else
    {
        pq->ptail->next = newnode;
        pq->ptail = newnode;
    }
    pq->size++;
}

void QueuePop(Queue *pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));

    // 边界情况：只剩一个节点
    if (pq->phead->next == NULL)
    {
        free(pq->phead);
        pq->phead = pq->ptail = NULL;
    }
    else
    {
        // 正常头删
        QNode *next = pq->phead->next;
        free(pq->phead);
        pq->phead = next;
    }
    pq->size--;
}

QDataType QueueFront(Queue *pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));
    return pq->phead->data;
}

QDataType QueueBack(Queue *pq)
{
    assert(pq);
    assert(!QueueEmpty(pq));
    return pq->ptail->data;
}

int QueueSize(Queue *pq)
{
    assert(pq);
    return pq->size;
}

bool QueueEmpty(Queue *pq)
{
    assert(pq);
    return pq->size == 0;
}
