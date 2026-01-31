#include "SeqList.h"

// 测试顺序表功能的 Main 函数
int main()
{
    SL s;

    // 1. 初始化
    SLInit(&s);

    // 2. 测试尾插
    printf("Testing PushBack:\n");
    SLPushBack(&s, 1);
    SLPushBack(&s, 2);
    SLPushBack(&s, 3);
    SLPushBack(&s, 4);
    SLPrint(&s); // 预期: 1 2 3 4

    // 3. 测试头插
    printf("Testing PushFront:\n");
    SLPushFront(&s, 0);
    SLPrint(&s); // 预期: 0 1 2 3 4

    // 4. 测试插入到中间位置
    printf("Testing Insert at pos 2:\n");
    SLInsert(&s, 2, 99);
    SLPrint(&s); // 预期: 0 1 99 2 3 4

    // 5. 测试头删
    printf("Testing PopFront:\n");
    SLPopFront(&s);
    SLPrint(&s); // 预期: 1 99 2 3 4

    // 6. 测试尾删
    printf("Testing PopBack:\n");
    SLPopBack(&s);
    SLPrint(&s); // 预期: 1 99 2 3

    // 7. 测试查找与修改
    printf("Testing Find and Modify:\n");
    int pos = SLFind(&s, 99);
    if (pos != -1)
    {
        SLModify(&s, pos, 100);
        printf("Modified 99 to 100 at pos %d\n", pos);
    }
    SLPrint(&s); // 预期: 1 100 2 3

    // 8. 销毁，释放内存
    SLDestroy(&s);

    return 0;
}