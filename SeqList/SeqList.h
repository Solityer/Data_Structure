#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 定义数据类型，方便后续修改（例如改为 double 或结构体）
typedef int SLDatatype;

// 动态顺序表结构定义
typedef struct SeqList
{
    SLDatatype* data; // 指向动态开辟的数组
    int size;         // 存储的有效数据的个数
    int capacity;     // 当前空间容量（能存储的最大个数）
} SL;

// 基础管理接口
void SLInit(SL* psl);    // 初始化
void SLDestroy(SL* psl); // 销毁
void SLPrint(SL* psl);   // 打印
void SLCheckCapacity(SL* psl); // 容量检查

// 插入/删除接口
void SLPushBack(SL* psl, SLDatatype x);  // 尾插
void SLPushFront(SL* psl, SLDatatype x); // 头插
void SLPopBack(SL* psl);                 // 尾删
void SLPopFront(SL* psl);                // 头删

// 随机访问接口
// 在 pos 位置插入 x
void SLInsert(SL* psl, int pos, SLDatatype x);
// 删除 pos 位置的数据
void SLErase(SL* psl, int pos);

// 查找与修改
// 找到返回下标，没有找到返回 -1
int SLFind(SL* psl, SLDatatype x);
// 修改 pos 位置的值
void SLModify(SL* psl, int pos, SLDatatype x);