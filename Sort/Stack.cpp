#include "Stack.h"
#include <stdlib.h> // 需要包含，用于 malloc/realloc/free
#include <assert.h> // 需要包含，用于 assert 断言
#include <stdio.h>  // 需要包含，用于 perror

// ==========================================================
// 栈的初始化
// ==========================================================
void STInit(ST *pst)
{
    // 断言结构体指针不为空，防止传入 NULL 指针导致程序崩溃
    assert(pst);

    // 初始化数组指针为空，此时未分配内存
    pst->a = NULL;

    // [关键定义]
    // top = 0 表示栈为空。
    // 这意味着 top 指向的是"栈顶元素的下一个位置" (Next Free Slot)。
    // 如果 top 初始化为 -1，则 top 指向的就是"当前栈顶元素"。
    // 本代码采用 top = 0 的定义。
    pst->top = 0;

    // capacity 表示当前动态数组申请的总空间大小
    pst->capacity = 0;
}

// ==========================================================
// 栈的销毁
// ==========================================================
void STDestroy(ST *pst)
{
    assert(pst);

    // 释放动态申请的内存，防止内存泄漏
    // 即使 pst->a 是 NULL，free(NULL) 也是安全的，不做操作
    free(pst->a);

    // 将指针置空，防止产生野指针 (Dangling Pointer)
    pst->a = NULL;

    // 归零状态
    pst->top = pst->capacity = 0;
}

// ==========================================================
// 入栈操作 (Push)
// 核心逻辑：检查容量 -> 扩容(如果需要) -> 插入数据 -> 更新 top
// ==========================================================
void STPush(ST *pst, STDataType x)
{
    assert(pst);

    // 1. 检查是否需要扩容
    // 因为 top 指向下一个空位，所以当 top == capacity 时，说明数组已满
    if (pst->top == pst->capacity)
    {
        // 扩容策略：
        // 如果 capacity 为 0 (第一次插入)，则给 4 个空间；
        // 否则，按当前容量的 2 倍进行扩容 (Growth Factor = 2)。
        // 这种策略可以分摊扩容带来的性能损耗 (Amortized Cost)。
        int newCapacity = pst->capacity == 0 ? 4 : pst->capacity * 2;

        // realloc 函数详解：
        // 1. 如果 pst->a 为 NULL，realloc 等同于 malloc。
        // 2. 如果 pst->a 不为 NULL，尝试原地扩容；如果原地空间不足，则开辟新空间、拷贝数据、释放旧空间。
        STDataType *tmp = (STDataType *) realloc(pst->a, newCapacity * sizeof(STDataType));

        // 内存申请失败检查
        if (tmp == NULL)
        {
            perror("realloc fail");
            return; // 或者 exit(-1) 终止程序
        }

        // 更新结构体成员
        pst->a = tmp;
        pst->capacity = newCapacity;
    }

    // 2. 插入数据
    // 先赋值，再让 top 后移
    pst->a[pst->top] = x;
    pst->top++;
}

// ==========================================================
// 出栈操作 (Pop)
// ==========================================================
void STPop(ST *pst)
{
    assert(pst);
    // 必须确保栈不为空，否则 top 减成负数会导致越界访问
    assert(!STEmpty(pst));

    // 逻辑删除：
    // 我们不需要真的去擦除内存中的数据，只需要将栈顶指针 top 向下移动一位。
    // 下次 Push 时，新数据会直接覆盖这个位置的旧数据。
    pst->top--;
}

// ==========================================================
// 获取栈顶元素 (Top)
// ==========================================================
STDataType STTop(ST *pst)
{
    assert(pst);
    // 空栈无法获取元素
    assert(!STEmpty(pst));

    // 因为 top 指向的是下一个空位 (index)，
    // 所以实际有效的栈顶元素下标是 top - 1
    return pst->a[pst->top - 1];
}

// ==========================================================
// 判空 (Empty)
// ==========================================================
bool STEmpty(ST *pst)
{
    assert(pst);
    // 如果 top 为 0，说明没有任何元素入栈，即为空
    return pst->top == 0;
}

// ==========================================================
// 获取元素个数 (Size)
// ==========================================================
int STSize(ST *pst)
{
    assert(pst);
    // 因为 top 是从 0 开始计数的，且指向下一个位置，
    // 所以 top 的值刚好等于栈中元素的个数。
    // 例如：入栈 1 个元素，top 变为 1，Size 就是 1。
    return pst->top;
}