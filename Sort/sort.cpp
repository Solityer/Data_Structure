#include "Sort.h"
#include "Stack.h" // 非递归快排需要用到栈，模拟函数调用栈的行为

// 辅助函数：打印数组
void PrintArray(int *a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// 辅助函数：交换两个整数的值
void Swap(int *p1, int *p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// ==========================================================
// 1. 插入排序类 (Insertion Sorts)
// 核心思想：维护一个有序区间，将后面的元素逐个插入到前面已排序的区间中。
// ==========================================================

// [直接插入排序]
// 时间复杂度：最坏 O(N^2)，最好 O(N)（接近有序时效率极高）
void InsertSort(int *a, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int temp = a[i]; // 保存当前要插入的元素
        int j = i - 1; // 从当前元素的前一个开始比较
        while (j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = temp;
    }
}

// [希尔排序] (Shell Sort)
// 核心思想：预排序。通过 gap 分组进行插入排序，让大的数快速跑到后面，小的数快速跑到前面。
// 当 gap > 1 时是预排序，gap == 1 时就是直接插入排序。
// 时间复杂度：平均约 O(N^1.3)
void ShellSort(int *a, int n)
{
    int gap = n;
    while (gap > 1)
    {
        // gap 的缩小策略：通常是 /3 + 1 或者 /2。
        // +1 是为了保证最后一次 gap 一定为 1。
        gap = gap / 3 + 1;

        // 对每一组进行插入排序。注意这里 i++ 而不是 i+=gap，
        // 这意味着我们是交替对多组进行处理，而不是处理完一组再下一组，逻辑更简洁。
        for (int i = 0; i < n - gap; ++i)
        {
            int end = i;
            int tmp = a[end + gap]; // 待插入元素是当前位置 + gap

            // 这里的逻辑和直接插入排序完全一致，只是步长从 1 变成了 gap
            while (end >= 0 && a[end] > tmp)
            {
                a[end + gap] = a[end]; // 元素后移 gap 位
                end -= gap; // 向前跨 gap 位比较
            }
            a[end + gap] = tmp;
        }
    }
}

// ==========================================================
// 2. 选择排序类 (Selection Sorts)
// 核心思想：每次从待排序元素中选出最大（或最小）的一个元素，存放在序列的起始（或末尾）。
// ==========================================================

// [冒泡排序]
// 核心思想：两两交换，每一轮将最大的元素"浮"到最后。
// 时间复杂度：O(N^2)
void BubbleSort(int *a, int n)
{
    // j 控制的是每一轮需要比较的次数，每轮确定一个最大值
    for (int j = 0; j < n; ++j)
    {
        bool flag = false; // 优化标志位：记录本轮是否发生过交换

        // 每一轮比较到 n - j 即可，因为后面 j 个已经排好序了
        for (int i = 1; i < n - j; i++)
        {
            if (a[i - 1] > a[i])
            {
                Swap(&a[i - 1], &a[i]);
                flag = true;
            }
        }
        // 如果一轮比较下来没有发生任何交换，说明数组已经有序，提前结束
        if (flag == false)
        {
            break;
        }
    }
}

// [选择排序] (优化版)
// 核心思想：一次遍历同时选出最大值和最小值，分别放到两端。
// 时间复杂度：O(N^2)
void SelectSort(int *a, int n)
{
    int begin = 0, end = n - 1; // 待排序区间的左右边界
    while (begin < end)
    {
        int maxi = begin, mini = begin; // 记录最大值和最小值的下标

        // 遍历当前区间，寻找最大和最小值的下标
        for (int i = begin; i <= end; i++)
        {
            if (a[i] > a[maxi])
                maxi = i;
            if (a[i] < a[mini])
                mini = i;
        }

        // 1. 将最小值交换到区间的起始位置
        Swap(&a[begin], &a[mini]);

        // 如果最大值 maxi 刚好就在 begin 位置，
        // 上一步 Swap(&a[begin], &a[mini]) 会把最大值换到 mini 的位置。
        // 所以需要修正 maxi 的下标指向新的位置。
        if (begin == maxi)
            maxi = mini;

        // 2. 将最大值交换到区间的末尾位置
        Swap(&a[end], &a[maxi]);

        // 缩小区间
        ++begin;
        --end;
    }
}

// 堆的核心操作：向下调整算法 (AdjustDown)
// 前提：左右子树必须已经是堆
// 作用：将 parent 位置的元素下沉到合适位置，保持大顶堆性质。
void AdjustDown(int *a, int n, int parent)
{
    int child = parent * 2 + 1; // 默认先找左孩子
    while (child < n)
    {
        // 如果右孩子存在，且右孩子比左孩子大，则 child 指向右孩子
        // 这一步是为了选出左右孩子中较大的那个
        if (child + 1 < n && a[child + 1] > a[child])
        {
            ++child;
        }

        // 如果孩子比父亲大，则交换，并继续向下调整
        if (a[child] > a[parent])
        {
            Swap(&a[child], &a[parent]);
            parent = child; // 父亲坐标下移
            child = parent * 2 + 1; // 获取新的左孩子
        }
        else
        {
            // 如果孩子不比父亲大，说明已经是堆了，停止
            break;
        }
    }
}

// [堆排序] (Heap Sort)
// 核心思想：利用堆结构（大顶堆）进行排序。
// 时间复杂度：O(N*logN)
void HeapSort(int *a, int n)
{
    // 1. 建堆 (Build Heap)
    // 从最后一个非叶子节点 ((n-1-1)/2) 开始，依次向前进行向下调整。
    // 这样能保证整棵树变成大顶堆。
    for (int i = (n - 1 - 1) / 2; i >= 0; --i)
    {
        AdjustDown(a, n, i);
    }

    // 2. 排序 (Sort)
    // 每次将堆顶（最大值）与堆尾交换，然后缩小堆的范围（--end），
    // 再对新的堆顶进行向下调整。
    int end = n - 1;
    while (end > 0)
    {
        Swap(&a[0], &a[end]); // 最大值放到最后
        AdjustDown(a, end, 0); // 恢复堆性质，注意范围是 n-1, n-2...
        --end;
    }
}

// ==========================================================
// 3. 快速排序类 (Quick Sort)
// 核心思想：分治法。选一个基准值 (Pivot)，将比它小的放左边，比它大的放右边。
// ==========================================================

// 优化：三数取中法
// 目的：防止数组有序或逆序时快排退化为 O(N^2)。
// 在 left, mid, right 三个位置中选出值处于中间的那个下标。
int GetMidIndex(int *a, int left, int right)
{
    int mid = (left + right) / 2;
    if (a[left] < a[mid])
    {
        if (a[mid] < a[right])
            return mid;
        else if (a[left] < a[right])
            return right;
        else
            return left;
    }
    else // a[left] >= a[mid]
    {
        if (a[mid] > a[right])
            return mid;
        else if (a[left] > a[right])
            return right;
        else
            return left;
    }
}

// 分区方法：前后指针法 (Partition)
// prev 指向"小于基准值区域"的最后一个元素。
// cur 负责遍历查找小于基准值的元素。
int PartSort3(int *a, int left, int right)
{
    // 1. 选基准值并交换到最左边
    int midi = GetMidIndex(a, left, right);
    Swap(&a[left], &a[midi]);

    int prev = left;
    int cur = left + 1;
    int keyi = left; // 基准值下标现在是 left

    while (cur <= right)
    {
        // 如果 cur 指向的值比 key 小，prev 先向前走一步
        // 如果 prev != cur，说明中间夹着比 key 大的数，需要交换
        // && 的短路特性保证了只有找到小的数才会增加 prev
        if (a[cur] < a[keyi] && ++prev != cur)
        {
            Swap(&a[prev], &a[cur]);
        }
        ++cur;
    }

    // 最后，prev 停留在小于 key 的最后一个位置，交换 key 和 prev
    // 这样 prev 左边全是小的，右边（包括当前位置）全是大的
    Swap(&a[prev], &a[keyi]);
    return prev; // 返回基准值最终所在的下标
}

// [递归快排]
void QuickSort(int *a, int begin, int end)
{
    if (begin >= end)
        return; // 区间不存在或只有一个元素，递归结束

    int keyi = PartSort3(a, begin, end); // 分区，获取基准值位置

    // [begin, keyi-1] keyi [keyi+1, end]
    // 递归处理左右两个子区间
    QuickSort(a, begin, keyi - 1);
    QuickSort(a, keyi + 1, end);
}

// [非递归快排]
// 核心思想：利用显式的栈 (Stack) 来模拟递归过程中的函数栈帧，
// 保存待处理区间的左右边界。
void QuickSortNonR(int *a, int begin, int end)
{
    ST st;
    STInit(&st); // 初始化栈

    // 先入栈整个区间（注意栈是后进先出，所以先入 end 后入 begin，方便出来时先取左后取右）
    STPush(&st, end);
    STPush(&st, begin);

    while (!STEmpty(&st))
    {
        // 弹出当前要处理的区间 [left, right]
        int left = STTop(&st);
        STPop(&st);
        int right = STTop(&st);
        STPop(&st);

        // 进行一次分区，找到基准值位置
        int keyi = PartSort3(a, left, right);

        // 此时区间被分为：[left, keyi-1] keyi [keyi+1, right]

        // 如果右区间有效（多于1个元素），入栈右区间
        if (keyi + 1 < right)
        {
            STPush(&st, right);
            STPush(&st, keyi + 1);
        }

        // 如果左区间有效，入栈左区间
        if (left < keyi - 1)
        {
            STPush(&st, keyi - 1);
            STPush(&st, left);
        }
    }
    STDestroy(&st); // 销毁栈，释放内存
}

// ==========================================================
// 4. 归并排序类 (Merge Sort)
// 核心思想：分治法。将数组对半拆分，直到只剩一个元素（有序），
// 然后将两个有序数组合并 (Merge) 成一个大的有序数组。
// 时间复杂度：O(N*logN)，空间复杂度：O(N)
// ==========================================================

// 归并核心逻辑：合并两个有序区间 [begin, mid] 和 [mid+1, end]
void _MergeSort(int *a, int begin, int end, int *tmp)
{
    if (begin == end)
        return; // 递归截止条件：区间只有一个元素

    int mid = (begin + end) / 2;
    // 递归拆分左半部分和右半部分
    _MergeSort(a, begin, mid, tmp);
    _MergeSort(a, mid + 1, end, tmp);

    // 开始归并
    int begin1 = begin, end1 = mid;
    int begin2 = mid + 1, end2 = end;
    int i = begin; // tmp 数组的索引

    // 谁小就把谁尾插到 tmp 数组中
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (a[begin1] <= a[begin2])
            tmp[i++] = a[begin1++];
        else
            tmp[i++] = a[begin2++];
    }
    // 处理剩余元素（两个循环只会执行其中一个）
    while (begin1 <= end1)
        tmp[i++] = a[begin1++];
    while (begin2 <= end2)
        tmp[i++] = a[begin2++];

    // 将归并好的数据从 tmp 拷贝回原数组 a
    // 注意长度是 end - begin + 1
    memcpy(a + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}

// [递归归并]
void MergeSort(int *a, int n)
{
    int *tmp = (int *) malloc(sizeof(int) * n); // 需要 O(N) 的辅助空间
    _MergeSort(a, 0, n - 1, tmp);
    free(tmp);
}

// [非递归归并]
// 核心思想：直接模拟归并过程。从 gap=1 开始（两两归并），gap=2（四四归并）...
// 难点：边界修正。非递归版本极易出现数组越界。
void MergeSortNonR(int *a, int n)
{
    int *tmp = (int *) malloc(sizeof(int) * n);
    int gap = 1; // gap 代表每组归并数据的个数

    while (gap < n)
    {
        int j = 0; // 此变量未被使用逻辑（代码中的拷贝用的是 i），可能是笔误或冗余，实际拷贝逻辑在 memcpy

        // 每次处理两个组，每组 gap 个元素
        // 第一组：[i, i+gap-1]
        // 第二组：[i+gap, i+2*gap-1]
        for (int i = 0; i < n; i += 2 * gap)
        {
            int begin1 = i, end1 = i + gap - 1;
            int begin2 = i + gap, end2 = i + 2 * gap - 1;

            // --- 边界修正开始 ---
            // 1. 如果第一组的结尾 end1 或者 第二组的开头 begin2 越界
            // 说明这轮只剩下一组数据（甚至第一组都不全），不需要归并了，直接跳出本轮循环
            if (end1 >= n || begin2 >= n)
                break;

            // 2. 如果第二组的结尾 end2 越界
            // 说明第二组数据存在，但是不满 gap 个，需要修正 end2 为 n-1
            if (end2 >= n)
                end2 = n - 1;
            // --- 边界修正结束 ---

            // 开始归并两个区间
            int idx = i; // 使用局部变量 idx 代替 i 进行 tmp 的下标控制
            int b1 = begin1, e1 = end1;
            int b2 = begin2, e2 = end2;

            while (b1 <= e1 && b2 <= e2)
            {
                if (a[b1] <= a[b2])
                    tmp[idx++] = a[b1++];
                else
                    tmp[idx++] = a[b2++];
            }
            while (b1 <= e1)
                tmp[idx++] = a[b1++];
            while (b2 <= e2)
                tmp[idx++] = a[b2++];

            // 归并完一组，立刻拷贝回原数组
            // 注意：不能等整轮循环结束再拷贝，因为如果上面 break 了，tmp 后面的数据可能是旧的
            memcpy(a + i, tmp + i, sizeof(int) * (end2 - i + 1));
        }
        gap *= 2; // 下一轮归并每组数据量翻倍
    }
    free(tmp);
}

// ==========================================================
// 5. 计数排序 (Counting Sort)
// 核心思想：非比较排序。利用哈希映射思想，统计每个数出现的次数。
// 适用场景：数据范围集中（range 不大）的整数排序。
// 时间复杂度：O(N + Range)，空间复杂度 O(Range)
// ==========================================================
void CountSort(int *a, int n)
{
    // 1. 找出最大最小值，确定映射范围 Range
    int min = a[0], max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
    }

    int range = max - min + 1;
    // 申请统计数组，用来记录每个数字出现的次数
    int *countA = (int *) malloc(sizeof(int) * range);
    // 必须初始化为 0
    memset(countA, 0, sizeof(int) * range);

    // 2. 统计次数
    // 采用相对映射：数值 - min = 下标
    for (int i = 0; i < n; i++)
        countA[a[i] - min]++;

    // 3. 反向写回原数组
    int k = 0;
    for (int j = 0; j < range; j++)
    {
        // 如果 countA[j] 不为 0，说明 min + j 这个数存在，且出现了 countA[j] 次
        while (countA[j]--)
            a[k++] = j + min;
    }
    free(countA);
}
