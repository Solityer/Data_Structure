#include"Heap.h"

// 初始化堆
void HeapInit(HP *php)
{
    assert(php); // 防止传入空指针
    php->a = NULL;      // 数组指针初始化为空
    php->size = 0;      // 当前堆元素个数为0
    php->capacity = 0;  // 堆容量为0
}

// 销毁堆，释放动态分配的内存
void HeapDestroy(HP *php)
{
    assert(php);
    free(php->a); // 释放动态申请的内存
    php->a = NULL;                 // 置空指针，防止野指针
    php->size = php->capacity = 0; // 重置大小和容量
}

// 交换两个元素的值
void Swap(HPDataType *p1, HPDataType *p2)
{
    HPDataType tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// 【向上调整算法】（小堆为例）
// 场景：用于 HeapPush。新元素插入数组末尾，如果不满足堆性质（如小堆中子节点比父节点小），需要上浮
// 参数：a - 堆数组指针，child - 需要进行向上调整的节点下标
void AdjustUp(HPDataType *a, int child)
{
    int parent = (child - 1) / 2; // 根据子节点下标计算父节点下标

    // 循环直到到达根节点（下标为0）
    while (child > 0)
    {
        // 小堆逻辑：如果子节点值小于父节点值，则交换
        // 若要改为大堆，只需修改此处为 if (a[child] > a[parent])
        if (a[child] < a[parent])
        {
            Swap(&a[child], &a[parent]);
            // 继续向上调整：当前节点移动到父节点位置
            child = parent;
            parent = (child - 1) / 2;
        }
        else
        {
            break; // 已经满足堆性质，停止调整
        }
    }
}

// 【向下调整算法】（小堆为例）
// 场景：HeapPop（删除堆顶）和 HeapSort（线性建堆）
// 参数：a - 堆数组指针
//		n - 堆中元素个数
// 		parent - 需要进行向下调整的节点下标
void AdjustDown(int *a, int n, int parent)
{
    // 初始左孩子下标
    int child = parent * 2 + 1;

    // 只要左孩子存在（下标小于n），就继续调整
    while (child < n)
    {
        // 1. 选出左右孩子中较小的一个（小堆逻辑）
        // 条件说明：child+1 < n 确保右孩子存在；如果右孩子更小，选择右孩子
        if (child + 1 < n && a[child + 1] < a[child])
        {
            ++child; // child切换到右孩子
        }

        // 2. 比较孩子与父亲的大小（小堆逻辑）
        if (a[child] < a[parent])
        {
            Swap(&a[parent], &a[child]);
            // 继续向下调整：父亲下沉到孩子位置
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break; // 已满足堆性质，停止调整
        }
    }
}

// 堆插入操作
// 步骤：1.将元素插入到数组末尾
// 		2.执行向上调整算法
void HeapPush(HP *php, HPDataType x)
{
    assert(php);

    // 容量检查与扩容
    if (php->size == php->capacity)
    {
        // 新容量：如果当前容量为0，初始化为4；否则扩大为2倍
        int newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;

        // 使用realloc进行动态内存扩容
        // realloc 支持原地扩容或异地扩容，这是C语言内存管理的经典模式
        HPDataType *tmp = (HPDataType *) realloc(php->a,
                             newCapacity * sizeof(HPDataType));
        if (tmp == NULL)
        {
            perror("realloc fail"); // 内存分配失败提示
            return;
        }
        php->a = tmp;
        php->capacity = newCapacity;
    }

    // 插入新元素到数组末尾
    php->a[php->size] = x;
    php->size++;

    // 对插入的元素执行向上调整，恢复堆性质
    AdjustUp(php->a, php->size - 1);
}

// 堆删除操作（删除堆顶元素）
// 步骤：1.交换堆顶和堆底元素 2.删除堆底元素 3.对堆顶元素执行向下调整
void HeapPop(HP *php)
{
    assert(php);
    assert(!HeapEmpty(php)); // 确保堆非空

    // 1. 交换堆顶和堆底元素（避免破坏整个堆结构导致O(N)重新建堆）
    Swap(&php->a[0], &php->a[php->size - 1]);

    // 2. 删除堆底元素（实际上是堆顶元素交换后的位置）
    php->size--;

    // 3. 对堆顶元素执行向下调整，恢复堆性质
    AdjustDown(php->a, php->size, 0);
}

// 获取堆顶元素（不删除）
HPDataType HeapTop(HP *php)
{
    assert(php);
    assert(!HeapEmpty(php)); // 确保堆非空
    return php->a[0]; // 返回堆顶元素
}

// 判断堆是否为空
bool HeapEmpty(HP *php)
{
    assert(php);
    return php->size == 0; // 如果大小为0，堆为空
}

// 获取堆中元素个数
int HeapSize(HP *php)
{
    assert(php);
    return php->size;
}