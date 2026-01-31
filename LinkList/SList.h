#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

// 定义单链表节点结构
typedef int SLTDataType;

typedef struct SListNode
{
    SLTDataType data;
    struct SListNode *next;
} SLTNode;

// 打印链表
void SLTPrint(SLTNode *phead);

// 头部插入 / 尾部插入
void SLPushFront(SLTNode **pphead, SLTDataType x);

void SLPushBack(SLTNode **pphead, SLTDataType x);

// 头部删除 / 尾部删除
void SLPopFront(SLTNode **pphead);

void SLPopBack(SLTNode **pphead);

// 单链表查找
SLTNode *STFind(SLTNode *phead, SLTDataType x);

// 在pos之前插入
void SLInsert(SLTNode **pphead, SLTNode *pos, SLTDataType x);

// 在pos之后插入
void SLInsertAfter(SLTNode *pos, SLTDataType x);

// 删除pos位置的值
void SLErase(SLTNode **pphead, SLTNode *pos);

// 删除pos位置后面的值
void SLEraseAfter(SLTNode *pos);