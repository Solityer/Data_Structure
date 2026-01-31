#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

// 定义双向链表数据类型
typedef int LTDataType;

typedef struct ListNode
{
    struct ListNode *next;
    struct ListNode *prev;
    LTDataType data;
} LTNode;

// 初始化
LTNode *LTInit();

// 打印
void LTPrint(LTNode *phead);

// 判空
bool LTEmpty(LTNode *phead);

// 尾插 / 头插
void LTPushBack(LTNode *phead, LTDataType x);

void LTPushFront(LTNode *phead, LTDataType x);

// 尾删 / 头删
void LTPopBack(LTNode *phead);

void LTPopFront(LTNode *phead);

// 查找
LTNode *LTFind(LTNode *phead, LTDataType x);

// 在pos之前插入
void LTInsert(LTNode *pos, LTDataType x);

// 删除pos位置的值
void LTErase(LTNode *pos);

// 销毁链表
void LTDestroy(LTNode *phead);