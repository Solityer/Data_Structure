#include "SeqList.h"

// 初始化顺序表
void SLInit(SL* psl)
{
    // 断言指针有效性，防止传入NULL指针
    assert(psl);
    // 初始分配 4 个元素的空间
    psl->data = (SLDatatype*)malloc(sizeof(SLDatatype) * 4);
    if (psl->data == NULL)
    {
        perror("SLInit malloc fail");
        return;
    }
    psl->capacity = 4; // 初始容量
    psl->size = 0;     // 初始有效数据量
}

// 销毁顺序表
void SLDestroy(SL* psl)
{
    assert(psl);
    if (psl->data != NULL)
    {
        free(psl->data);
        psl->data = NULL; // 避免野指针
    }
    psl->size = 0;
    psl->capacity = 0;
}

// 打印顺序表内容
void SLPrint(SL* psl)
{
    assert(psl);
    for (int i = 0; i < psl->size; i++)
    {
        printf("%d ", psl->data[i]);
    }
    printf("\n");
}

// 检查容量，如果满了则扩容
void SLCheckCapacity(SL* psl)
{
    assert(psl);
    // 如果有效数据个数等于容量，说明满了，需要扩容
    if (psl->size == psl->capacity)
    {
        // 扩容为原来的 2 倍
        int newCapacity = psl->capacity * 2;
        SLDatatype* tmp = (SLDatatype*)realloc(psl->data, sizeof(SLDatatype) * newCapacity);
        if (tmp == NULL)
        {
            perror("SLCheckCapacity realloc fail");
            return;
        }
        psl->data = tmp;       // 更新数据指针
        psl->capacity = newCapacity; // 更新容量
    }
}

// 尾插：在顺序表末尾插入数据
void SLPushBack(SL* psl, SLDatatype x)
{
    assert(psl);
    // 复用 SLInsert，在 size 位置（即末尾）插入
    SLInsert(psl, psl->size, x);
}

// 头插：在顺序表头部插入数据
void SLPushFront(SL* psl, SLDatatype x)
{
    assert(psl);
    // 复用 SLInsert，在 0 位置（即头部）插入
    SLInsert(psl, 0, x);
}

// 尾删：删除顺序表末尾的数据
void SLPopBack(SL* psl)
{
    assert(psl);
    // 复用 SLErase，删除 size-1 位置（即末尾）的数据
    // 注意：SLErase 内部会检查 pos 的合法性，也就间接检查了 size > 0
    SLErase(psl, psl->size - 1);
}

// 头删：删除顺序表头部的数据
void SLPopFront(SL* psl)
{
    assert(psl);
    // 复用 SLErase，删除 0 位置（即头部）的数据
    SLErase(psl, 0);
}

// 在指定位置 pos 插入数据 x
void SLInsert(SL* psl, int pos, SLDatatype x)
{
    assert(psl);
    // 检查插入位置的合法性：0 <= pos <= size
    // pos == size 时相当于尾插
    assert(0 <= pos && pos <= psl->size);
    // 插入前先检查容量，不够则扩容
    SLCheckCapacity(psl);
    // 将 pos 位置及之后的数据整体向后挪动一位
    // end 指向最后一个有效元素
    int end = psl->size - 1;
    while (end >= pos)
    {
        psl->data[end + 1] = psl->data[end];
        --end;
    }
    // 在腾出的 pos 位置放入新数据
    psl->data[pos] = x;
    psl->size++;
}

// 删除指定位置 pos 的数据
void SLErase(SL* psl, int pos)
{
    assert(psl);
    // 检查删除位置的合法性：0 <= pos < size
    // 这也隐含了 psl->size 必须大于 0
    assert(0 <= pos && pos < psl->size);
    // 将 pos 之后的数据整体向前挪动一位
    // start 指向 pos 的后一个元素
    int start = pos + 1;
    while (start < psl->size)
    {
        psl->data[start - 1] = psl->data[start];
        ++start;
    }
    psl->size--;
}

// 查找数据 x，返回下标，未找到返回 -1
int SLFind(SL* psl, SLDatatype x)
{
    assert(psl);
    for (int i = 0; i < psl->size; i++)
    {
        if (psl->data[i] == x)
        {
            return i;
        }
    }
    return -1;
}

// 修改指定位置 pos 的数据
void SLModify(SL* psl, int pos, SLDatatype x)
{
    assert(psl);
    // 检查位置合法性
    assert(0 <= pos && pos < psl->size);
    psl->data[pos] = x;
}