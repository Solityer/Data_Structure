#include "List.h"

// 申请节点
LTNode *BuyLTNode(LTDataType x)
{
    LTNode *newnode = (LTNode *) malloc(sizeof(LTNode));
    if (newnode == NULL)
    {
        perror("malloc fail");
        return NULL;
    }

    newnode->data = x;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

// 初始化哨兵位
LTNode *LTInit()
{
    LTNode *phead = BuyLTNode(-1);
    phead->next = phead;
    phead->prev = phead;

    return phead;
}

// 打印
void LTPrint(LTNode *phead)
{
    assert(phead);

    printf("guard<==>");
    LTNode *cur = phead->next;
    while (cur != phead)
    {
        printf("%d<==>", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// 判空
bool LTEmpty(LTNode *phead)
{
    assert(phead);

    return phead->next == phead;
}

// 尾插
void LTPushBack(LTNode *phead, LTDataType x)
{
    assert(phead);

    // 复用 Insert
    LTInsert(phead, x);

    // 原生实现:
    //LTNode* tail = phead->prev;
    //LTNode* newnode = BuyLTNode(x);

    //tail->next = newnode;
    //newnode->prev = tail;
    //newnode->next = phead;
    //phead->prev = newnode;
}

// 头插
void LTPushFront(LTNode *phead, LTDataType x)
{
    // 原生实现:
    /*assert(phead);
    LTNode* newnode = BuyLTNode(x);
    LTNode* first = phead->next;

    phead->next = newnode;
    newnode->prev = phead;

    newnode->next = first;
    first->prev = newnode;*/

    // 复用 Insert (在第一个有效节点前插入)
    LTInsert(phead->next, x);
}

// 尾删
void LTPopBack(LTNode *phead)
{
    assert(phead);
    assert(!LTEmpty(phead));

    // 复用 Erase
    LTErase(phead->prev);

    // 原生实现:
    /*LTNode* tail = phead->prev;
    LTNode* tailPrev = tail->prev;

    free(tail);
    tailPrev->next = phead;
    phead->prev = tailPrev;*/
}

// 头删
void LTPopFront(LTNode *phead)
{
    assert(phead);
    assert(!LTEmpty(phead));

    // 复用 Erase
    LTErase(phead->next);

    // 原生实现:
    //LTNode* next = phead->next;
    //
    ///*phead->next = next->next;
    //phead->next->prev = phead;
    //free(next);*/
    //
    //phead->next = next->next;
    //next->next->prev = phead;
    //free(next);
}

// 查找
LTNode *LTFind(LTNode *phead, LTDataType x)
{
    assert(phead);

    LTNode *cur = phead->next;
    while (cur != phead)
    {
        if (cur->data == x)
        {
            return cur;
        }

        cur = cur->next;
    }

    return NULL;
}

// 在pos之前插入
void LTInsert(LTNode *pos, LTDataType x)
{
    assert(pos);

    LTNode *prev = pos->prev;
    LTNode *newnode = BuyLTNode(x);

    // prev newnode pos
    prev->next = newnode;
    newnode->prev = prev;
    newnode->next = pos;
    pos->prev = newnode;
}

// 删除pos位置的值
void LTErase(LTNode *pos)
{
    assert(pos);

    LTNode *posPrev = pos->prev;
    LTNode *posNext = pos->next;

    posPrev->next = posNext;
    posNext->prev = posPrev;
    free(pos);
}

// 销毁
void LTDestroy(LTNode *phead)
{
    assert(phead);

    LTNode *cur = phead->next;
    while (cur != phead)
    {
        LTNode *next = cur->next;
        free(cur);
        cur = next;
    }

    free(phead);
}