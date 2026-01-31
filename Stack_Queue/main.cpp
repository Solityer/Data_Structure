#include <stdio.h>
#include "Stack.h"
#include "Queue.h"

void TestStack()
{
    printf("=========================\n");
    printf("开始测试栈 (Stack)...\n");

    ST st;
    // 1. 测试初始化
    STInit(&st);
    printf("栈初始化完成。\n");

    // 2. 测试入栈 (Push)
    // 压入 1, 2, 3, 4
    STPush(&st, 1);
    STPush(&st, 2);
    STPush(&st, 3);
    STPush(&st, 4);
    printf("入栈数据: 1, 2, 3, 4\n");

    // 3. 测试获取栈大小 (Size)
    printf("当前栈的大小: %d\n", STSize(&st));

    // 4. 测试获取栈顶元素 (Top) 和修改栈顶
    printf("当前栈顶元素: %d\n", STTop(&st));

    // 5. 测试出栈 (Pop)
    printf("执行一次出栈操作...\n");
    STPop(&st);
    printf("出栈后新的栈顶元素: %d\n", STTop(&st));

    // 6. 测试判空 (Empty) 与遍历
    printf("剩余元素依次出栈: ");
    while (!STEmpty(&st))
    {
        printf("%d ", STTop(&st));
        STPop(&st);
    }
    printf("\n");

    // 验证判空
    if (STEmpty(&st))
    {
        printf("栈目前为空。\n");
    }

    // 7. 测试销毁
    STDestroy(&st);
    printf("栈已销毁。\n");
    printf("=========================\n\n");
}


void TestQueue()
{
    printf("=========================\n");
    printf("开始测试队列 (Queue)...\n");

    Queue q;
    // 1. 测试初始化
    QueueInit(&q);
    printf("队列初始化完成。\n");

    // 2. 测试入队 (Push)
    // 入队 10, 20, 30, 40
    QueuePush(&q, 10);
    QueuePush(&q, 20);
    QueuePush(&q, 30);
    QueuePush(&q, 40);
    printf("入队数据: 10, 20, 30, 40\n");

    // 3. 测试获取队列大小 (Size)
    printf("当前队列大小: %d\n", QueueSize(&q));

    // 4. 测试队头 (Front) 和 队尾 (Back) 数据
    printf("当前队头元素: %d\n", QueueFront(&q));
    printf("当前队尾元素: %d\n", QueueBack(&q));

    // 5. 测试出队 (Pop)
    printf("执行一次出队操作 (头删)...\n");
    QueuePop(&q);

    // 再次查看队头
    printf("出队后新的队头元素: %d\n", QueueFront(&q));

    // 6. 测试判空 (Empty) 与遍历
    printf("剩余元素依次出队: ");
    while (!QueueEmpty(&q))
    {
        // 打印队头
        printf("%d ", QueueFront(&q));
        // 出队
        QueuePop(&q);
    }
    printf("\n");

    // 验证判空
    if (QueueEmpty(&q))
    {
        printf("队列目前为空。\n");
    }

    // 7. 测试销毁
    QueueDestroy(&q);
    printf("队列已销毁。\n");
    printf("=========================\n");
}

int main()
{
    // 测试栈逻辑
    TestStack();

    // 测试队列逻辑
    TestQueue();

    return 0;
}