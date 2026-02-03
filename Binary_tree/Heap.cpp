#include"Heap.h"

void HeapInit(HP *php)
{
    assert(php); // 防止传入空指针
    php->a = NULL;
    php->size = 0;
    php->capacity = 0;
}

void HeapDestroy(HP *php)
{
    assert(php);
    free(php->a); // 释放动态申请的内存
    php->a = NULL;
    php->size = php->capacity = 0;
}

void Swap(HPDataType *p1, HPDataType *p2)
{
    HPDataType tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// 【向上调整算法】
// 时间复杂度：O(logN)
// 场景：用于 HeapPush。新元素插入数组末尾，如果不满足堆性质（如小堆中子节点比父节点小），需要上浮。
void AdjustUp(HPDataType *a, int child)
{
    int parent = (child - 1) / 2; // 父节点下标计算公式
    while (child > 0)
    {
        // 小堆逻辑：子节点 < 父节点，则交换
        // 若要改为大堆，只需修改此处为 if (a[child] > a[parent])
        if (a[child] < a[parent])
        {
            Swap(&a[child], &a[parent]);
            // 迭代：当前位置变为父节点，继续向上比较
            child = parent;
            parent = (child - 1) / 2;
        }
        else
        {
            break; // 满足堆性质，停止调整
        }
    }
}

// 【向下调整算法】
// 时间复杂度：O(logN)
// 场景：HeapPop（删除堆顶）和 HeapSort（线性建堆）。
// 核心逻辑：将堆顶元素与较小（或较大）的子节点交换，使其下沉。
void AdjustDown(int *a, int n, int parent)
{
    // 左孩子下标
    int child = parent * 2 + 1;

    while (child < n) // 只要左孩子存在，就继续
    {
        // 1. 选出左右孩子中较小的一个（小堆逻辑）
        // child+1 < n 保证右孩子存在
        if (child + 1 < n && a[child + 1] < a[child])
        {
            ++child; // 如果右孩子更小，child切换到右孩子
        }

        // 2. 比较孩子与父亲
        if (a[child] < a[parent])
        {
            Swap(&a[parent], &a[child]);
            // 迭代：父亲下沉到孩子位置，继续向下
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void HeapPush(HP *php, HPDataType x)
{
    assert(php);

    // 扩容逻辑：2倍扩容
    if (php->size == php->capacity)
    {
        int newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
        // realloc 支持原地扩容或异地扩容，这是C语言内存管理的经典模式
        HPDataType *tmp = (HPDataType *) realloc(php->a, newCapacity * sizeof(HPDataType));
        if (tmp == NULL)
        {
            perror("realloc fail");
            return;
        }
        php->a = tmp;
        php->capacity = newCapacity;
    }

    php->a[php->size] = x; // 插入队尾
    php->size++;

    AdjustUp(php->a, php->size - 1); // 向上调整恢复堆性质
}

void HeapPop(HP *php)
{
    assert(php);
    assert(!HeapEmpty(php));

    // 删除堆顶的标准做法：
    // 1. 交换堆顶和堆底（避免破坏整个堆结构导致O(N)重新建堆）
    Swap(&php->a[0], &php->a[php->size - 1]);
    // 2. 删除堆底
    php->size--;
    // 3. 向下调整堆顶
    AdjustDown(php->a, php->size, 0);
}

HPDataType HeapTop(HP *php)
{
    assert(php);
    assert(!HeapEmpty(php));
    return php->a[0];
}

bool HeapEmpty(HP *php)
{
    assert(php);
    return php->size == 0;
}

int HeapSize(HP *php)
{
    assert(php);
    return php->size;
}
