#include "SList.h"

// 打印链表
void SLTPrint(SLTNode *phead)
{
    SLTNode *cur = phead;
    while (cur != NULL)
    {
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// 申请新节点 (为了避免和双向链表冲突，这里命名改为 BuySLTNode)
SLTNode *BuySLTNode(SLTDataType x)
{
    SLTNode *newnode = (SLTNode *) malloc(sizeof(SLTNode));
    if (newnode == NULL)
    {
        perror("malloc fail");
        return NULL;
    }
    newnode->data = x;
    newnode->next = NULL;

    return newnode;
}

// 头插
void SLPushFront(SLTNode **pphead, SLTDataType x)
{
    assert(pphead); // 链表为空，pphead也不为空，因为他是头指针plist的地址
    //assert(*pphead); // 不能断言，链表为空，也需要能插入

    SLTNode *newnode = BuySLTNode(x);

    newnode->next = *pphead;
    *pphead = newnode;
}

// 尾插
//void SLPushBack(SLTNode* phead, SLTDataType x)
//{
//	SLTNode* tail = phead;
//	while (tail != NULL)
//	{
//		tail = tail->next;
//	}
//
//	SLTNode* newnode = BuySLTNode(x);
//	tail = newnode;
//}

void SLPushBack(SLTNode **pphead, SLTDataType x)
{
    assert(pphead); // 链表为空，pphead也不为空，因为他是头指针plist的地址
    //assert(*pphead); // 链表为空，可以尾插

    SLTNode *newnode = BuySLTNode(x);

    // 1、空链表
    // 2、非空链表
    if (*pphead == NULL)
    {
        *pphead = newnode;
    }
    else
    {
        SLTNode *tail = *pphead;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }

        tail->next = newnode;
    }
}

// 头删
void SLPopFront(SLTNode **pphead)
{
    assert(pphead); // 链表为空，pphead也不为空，因为他是头指针plist的地址
    assert(*pphead); // 链表为空，不能头删。（当然你还可以用温柔的检查）

    // 一个节点
    // 多个节点
    //if ((*pphead)->next == NULL)
    //{
    //	free(*pphead);
    //	*pphead = NULL;
    //}
    //else
    //{
    //	SLTNode* del = *pphead;
    //	//*pphead = del->next;
    //	*pphead = (*pphead)->next;
    //	free(del);
    //}

    SLTNode *del = *pphead;
    *pphead = (*pphead)->next;
    free(del);
}

// 尾删
void SLPopBack(SLTNode **pphead)
{
    assert(pphead); // 链表为空，pphead也不为空，因为他是头指针plist的地址
    assert(*pphead); // 链表为空，不能尾删。（当然你还可以用温柔的检查）

    // 没有节点(空链表)

    // 暴力检查
    //assert(*pphead);

    // 温柔的检查
    /*if (*pphead == NULL)
    {
        return;
    }*/

    // 一个节点
    // 多个节点
    if ((*pphead)->next == NULL)
    {
        free(*pphead);
        *pphead = NULL;
    }
    else
    {
        //SLTNode* prev = NULL;
        //SLTNode* tail = *pphead;
        //// 找尾
        //while (tail->next)
        //{
        //	prev = tail;
        //	tail = tail->next;
        //}

        //free(tail);
        //prev->next = NULL;

        SLTNode *tail = *pphead;
        // 找尾
        while (tail->next->next)
        {
            tail = tail->next;
        }

        free(tail->next);
        tail->next = NULL;
    }
}

// 查找
SLTNode *STFind(SLTNode *phead, SLTDataType x)
{
    //assert(phead);

    SLTNode *cur = phead;
    while (cur)
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
void SLInsert(SLTNode **pphead, SLTNode *pos, SLTDataType x)
{
    assert(pphead);
    assert(pos);
    //assert(*pphead);

    if (*pphead == pos)
    {
        SLPushFront(pphead, x);
    }
    else
    {
        SLTNode *prev = *pphead;
        while (prev->next != pos)
        {
            prev = prev->next;
        }

        SLTNode *newnode = BuySLTNode(x);
        prev->next = newnode;
        newnode->next = pos;
    }
}

// 在pos之后插入
void SLInsertAfter(SLTNode *pos, SLTDataType x)
{
    assert(pos);

    SLTNode *newnode = BuySLTNode(x);
    newnode->next = pos->next;
    pos->next = newnode;
}

// 删除pos位置的值
void SLErase(SLTNode **pphead, SLTNode *pos)
{
    assert(pphead);
    assert(pos);

    if (pos == *pphead)
    {
        SLPopFront(pphead);
    }
    else
    {
        SLTNode *prev = *pphead;
        while (prev->next != pos)
        {
            prev = prev->next;
        }

        prev->next = pos->next;
        free(pos);
    }
}

// 删除pos位置后面的值
void SLEraseAfter(SLTNode *pos)
{
    assert(pos);
    assert(pos->next);

    SLTNode *next = pos->next;
    pos->next = next->next;
    free(next);
}