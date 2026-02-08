#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "Heap.h"  // 引入堆的定义，用于后续的堆排序和TopK
#include "Queue.h" // 引入队列的定义，用于二叉树的层序遍历(BFS)

// ==========================================
// 第一部分: 二叉树 (Binary Tree) 的定义与算法
// ==========================================

// 定义树节点的数据类型，方便后续修改（例如改为 char 或 float）
typedef int BTDataType;

// 二叉树节点结构体定义
typedef struct BinaryTreeNode
{
    BTDataType data; // 节点存储的数据
    struct BinaryTreeNode *left; // 左孩子指针
    struct BinaryTreeNode *right; // 右孩子指针
} BTNode;

// 【辅助函数】创建新节点
// 逻辑：申请内存 -> 检查失败 -> 初始化指针 -> 返回地址
BTNode *BuyNode(BTDataType x)
{
    // 使用 malloc 在堆区(Heap)申请内存，生命周期由程序员控制，必须手动 free
    BTNode *node = (BTNode *) malloc(sizeof(BTNode));
    if (node == NULL)
    {
        perror("malloc fail"); // 申请失败通常是因为内存耗尽
        return NULL;
    }
    node->data = x;
    node->left = NULL; // 初始化为空，防止成为野指针
    node->right = NULL;
    return node;
}

// 【辅助函数】手动构建一个用于测试的二叉树
// 逻辑：手动模拟链接过程，构造一个非完全二叉树用于测试通用性
BTNode *CreatBinaryTree()
{
    BTNode *node1 = BuyNode(1);
    BTNode *node2 = BuyNode(2);
    BTNode *node3 = BuyNode(3);
    BTNode *node4 = BuyNode(4);
    BTNode *node5 = BuyNode(5);
    BTNode *node6 = BuyNode(6);
    BTNode *node7 = BuyNode(7);

    // 构建如下拓扑结构：
    //       1
    //     /   \
    //    2     4
    //   / \   / \
    //  3   7 5   6
    // 注意：这不是完全二叉树，也不是满二叉树

    node1->left = node2;
    node1->right = node4;
    node2->left = node3;
    node4->left = node5;
    node4->right = node6;
    node2->right = node7;

    return node1; // 返回根节点，通过根节点可以索引到整棵树
}

// 【DFS】前序遍历 (Pre-Order Traversal)
// 顺序：根 -> 左 -> 右
// 内部逻辑：递归调用栈。先访问当前节点，再将“左子树”作为子问题递归，最后“右子树”。
void PrevOrder(BTNode *root)
{
    // 1. 递归终止条件 (Base Case)
    if (root == NULL)
    {
        printf("N "); // N 代表 NULL，方便可视化树的结构
        return;
    }

    // 2. 处理当前节点 (根)
    printf("%d ", root->data);

    // 3. 递归处理子节点
    PrevOrder(root->left);
    PrevOrder(root->right);
}

// 【DFS】中序遍历 (In-Order Traversal)
// 顺序：左 -> 根 -> 右
void InOrder(BTNode *root)
{
    if (root == NULL)
    {
        printf("N ");
        return;
    }

    InOrder(root->left); // 先钻到最左边
    printf("%d ", root->data); // 再打印自己
    InOrder(root->right); // 最后处理右边
}

// 【分治算法】求树的节点个数
// 内部逻辑：不要使用全局变量计数（线程不安全）。
// 思想：整棵树大小 = 左子树大小 + 右子树大小 + 1（自己）
int BTreeSize(BTNode *root)
{
    return root == NULL ? 0 : BTreeSize(root->left) + BTreeSize(root->right) + 1;
}

// 【分治算法】求叶子节点个数
// 内部逻辑：叶子节点的定义是“左右孩子均为空”。
int BTreeLeafSize(BTNode *root)
{
    if (root == NULL)
        return 0;

    // 如果我是叶子，返回 1
    if (root->left == NULL && root->right == NULL)
        return 1;

    // 如果我不是叶子，返回 左子树叶子数 + 右子树叶子数
    return BTreeLeafSize(root->left) + BTreeLeafSize(root->right);
}

// 【分治算法】求树的高度
// 内部逻辑：高度 = max(左高, 右高) + 1。
// 重要性能点：必须用变量 (leftHeight/rightHeight) 缓存递归结果。
// 如果写成 return BTreeHeight(root->left) > BTreeHeight(root->right) ? ...
// 会导致严重的时间复杂度膨胀（接近 O(2^N)），因为重复计算了两次子树高度。
int BTreeHeight(BTNode *root)
{
    if (root == NULL)
        return 0;

    int leftHeight = BTreeHeight(root->left);
    int rightHeight = BTreeHeight(root->right);

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

// 【分治算法】求第 K 层节点个数
// 内部逻辑：相对论。
// 对于根节点是第 K 层；对于根的子节点来说，目标是第 K-1 层。
// 当 K==1 时，说明当前节点就是目标层的节点，返回 1。
int BTreeLevelKSize(BTNode *root, int k)
{
    assert(k > 0);
    if (root == NULL)
        return 0;

    if (k == 1)
        return 1; // 找到了目标层的一个节点

    // 继续向下找，目标层级减 1
    return BTreeLevelKSize(root->left, k - 1) + BTreeLevelKSize(root->right, k - 1);
}

// 【BFS】层序遍历 (Level Order Traversal)
// 内部逻辑：利用“队列”先进先出 (FIFO) 的性质。
// 1. 父节点出队时，顺手把左孩子和右孩子带入队列。
// 2. 这样上一层全部出队完，队列里剩下的就全是下一层的节点。
void LevelOrder(BTNode *root)
{
    Queue q;
    QueueInit(&q); // 初始化队列

    if (root)
    	QueuePush(&q, root); // 放入根节点启动循环

    while (!QueueEmpty(&q))
    {
        // 1. 取队头
        BTNode *front = QueueFront(&q);
        QueuePop(&q);

        // 2. 打印（访问）
        printf("%d ", front->data);

        // 3. 将下一层节点入队
        if (front->left)
            QueuePush(&q, front->left);
        if (front->right)
            QueuePush(&q, front->right);
    }
    printf("\n");
    QueueDestroy(&q); // 别忘了销毁队列内存
}

// 【BFS应用】判断完全二叉树 (Complete Binary Tree)
// 内部逻辑：完全二叉树要求节点必须连续，不能有空洞。
// 方法：层序遍历时，把 NULL 节点也当作有效节点入队。
// 一旦取出了一个 NULL 节点，队列中剩余的所有节点必须全是 NULL。
// 如果在 NULL 之后又出现了非 NULL 节点，说明树中间断开了，不是完全二叉树。
bool BTreeComplete(BTNode *root)
{
    Queue q;
    QueueInit(&q);
    if (root)
        QueuePush(&q, root);

    while (!QueueEmpty(&q))
    {
        BTNode *front = QueueFront(&q);
        QueuePop(&q);

        // 核心转折点：遇到了第一个空节点，停止入队，进入检查阶段
        if (front == NULL)
            break;

        // 不管孩子是不是 NULL，都入队
        QueuePush(&q, front->left);
        QueuePush(&q, front->right);
    }

    // 检查阶段：检查队列里剩下的是不是全是 NULL
    while (!QueueEmpty(&q))
    {
        BTNode *front = QueueFront(&q);
        QueuePop(&q);
        // 如果在空节点后面又发现了有效节点，说明不连续
        if (front)
        {
            QueueDestroy(&q);
            return false;
        }
    }
    QueueDestroy(&q);
    return true;
}

// 【后序遍历】二叉树销毁
// 内部逻辑：必须是后序（左右根）。
// 为什么？如果先 Free 了根节点（前序），就找不到左右孩子的地址了，造成内存泄漏。
void BTreeDestory(BTNode *root)
{
    if (root == NULL)
        return;

    BTreeDestory(root->left); // 删左
    BTreeDestory(root->right); // 删右
    free(root); // 删根
}

// ==========================================
// 第二部分: 堆排序与 TopK 问题
// ==========================================

// 【堆排序】Heap Sort
// 时间复杂度：O(N*logN)
// 空间复杂度：O(1) (原地排序，不需要额外开辟数组)
void HeapSortTest(int *a, int n)
{
    // 1. 建堆 (Heapify)
    // 使用“向下调整”建堆，复杂度是 O(N)，比一个一个插入的 O(NlogN) 更快。
    // i 从最后一个非叶子节点开始遍历：(n-1-1)/2 计算父节点公式
    for (int i = (n - 1 - 1) / 2; i >= 0; --i)
    {
        AdjustDown(a, n, i); // 建大堆还是小堆，取决于 AdjustDown 里的符号
    }

    // 2. 排序 (Selection via Heap)
    // 逻辑：堆顶肯定是最大值（大堆）或最小值（小堆）。
    // 将堆顶交换到数组末尾（视为已排序区域），然后对剩下的元素重新调整堆。
    int end = n - 1;
    while (end > 0)
    {
        Swap(&a[0], &a[end]); // 把最大的数挪到最后
        AdjustDown(a, end, 0); // 把剩下的数重新调整成堆，选出次大的
        --end; // 缩减堆的范围
    }
}

// 【辅助函数】生成海量测试数据
void CreateNDate()
{
    int n = 1000; // 模拟生成 1000 个数据
    srand((unsigned int) time(0)); // 随机数种子
    const char *file = "data.txt";
    FILE *fin = fopen(file, "w");
    if (fin == NULL)
    {
        perror("fopen error");
        return;
    }
    for (size_t i = 0; i < n; ++i)
    {
        int x = rand() % 10000;
        fprintf(fin, "%d\n", x); // 写入文件
    }
    fclose(fin);
}

// 【核心难点】TopK 问题
// 问题：如何在 N 个数中找到最大的 K 个数？（假设 N 很大，内存存不下）
// 解决方案：使用大小为 K 的小顶堆 (Min-Heap)。
// 逻辑：
// 1. 如果新来的数比堆顶（堆中最小的数）还要大，说明它有资格进入前 K 名。
// 2. 踢掉堆顶，新数入堆，然后向下调整。
// 3. 最终堆里留下的就是最大的 K 个数。
void PrintTopK(int k)
{
    const char *file = "data.txt";
    FILE *fout = fopen(file, "r");
    if (fout == NULL)
    {
        perror("fopen error");
        return;
    }

    // 1. 读取前 K 个数，填满数组
    int *kminheap = (int *) malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++)
    {
        fscanf(fout, "%d", &kminheap[i]);
    }

    // 2. 对这 K 个数建小堆
    // 为什么要小堆？因为我们要淘汰最小的那个，小堆的堆顶正是最小的。
    for (int i = (k - 1 - 1) / 2; i >= 0; i--)
    {
        AdjustDown(kminheap, k, i);
    }

    // 3. 读取剩余数据，与堆顶比较
    int val = 0;
    while (fscanf(fout, "%d", &val) != EOF)
    {
        // 核心贪心策略：如果文件里的数 > 堆顶（目前前K名里的门槛人员）
        if (val > kminheap[0])
        {
            kminheap[0] = val; // 替换堆顶
            AdjustDown(kminheap, k, 0); // 重新调整，维护小堆性质
        }
    }

    printf("Top %d Elements: ", k);
    for (int i = 0; i < k; i++)
    {
        printf("%d ", kminheap[i]);
    }
    printf("\n");
    free(kminheap);
    fclose(fout);
}

// ==========================================
// 第三部分: 主函数入口 (Main)
// ==========================================
int main()
{
    // --- 测试二叉树功能 ---
    printf("=== Test 1: Binary Tree Basic ===\n");
    BTNode *root = CreatBinaryTree(); // 建树

    printf("PreOrder: ");
    PrevOrder(root);
    printf("\n");
    printf("InOrder: ");
    InOrder(root);
    printf("\n");
    printf("LevelOrder: ");
    LevelOrder(root); // 层序遍历

    printf("Tree Size: %d\n", BTreeSize(root));
    printf("Tree Height: %d\n", BTreeHeight(root));
    // 检查是否为完全二叉树（示例树是不完全的，应该输出 No）
    printf("Is Complete Tree? %s\n", BTreeComplete(root) ? "Yes" : "No");

    BTreeDestory(root); // 别忘了销毁树，防止内存泄漏
    root = NULL; // 销毁后置空指针，好习惯

    // --- 测试堆的基本功能 ---
    printf("\n=== Test 2: Heap Functionality ===\n");
    HP hp;
    HeapInit(&hp);
    int testData[] = {4, 1, 7, 9, 2, 8};
    // 依次入堆，内部会自动 AdjustUp 保持堆序
    for (int x: testData)
        HeapPush(&hp, x);

    printf("Heap Top: %d\n", HeapTop(&hp)); // 小堆应该是最小值 1
    printf("Heap Pop...\n");
    HeapPop(&hp); // 删除堆顶
    printf("New Heap Top: %d\n", HeapTop(&hp)); // 应该是次小值 2
    HeapDestroy(&hp);

    // --- 测试堆排序 ---
    printf("\n=== Test 3: Heap Sort ===\n");
    int arr[] = {5, 3, 8, 1, 9, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    HeapSortTest(arr, n);

    // 如果 AdjustDown 实现的是小堆逻辑，排序结果是降序（因为每次把最小的换到最后）
    // 如果 AdjustDown 实现的是大堆逻辑，排序结果是升序
    printf("Sorted: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // --- 测试 TopK 问题 ---
    printf("\n=== Test 4: TopK Problem ===\n");
    CreateNDate(); // 随机生成数据文件
    PrintTopK(5); // 从文件中选出最大的 5 个数

    return 0;
}