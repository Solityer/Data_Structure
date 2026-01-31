#include "SList.h"
#include "List.h"

// ---------------------- 单链表测试 ----------------------

void TestSList1()
{
    printf("=== TestSList1 (Front Push) ===\n");
    SLTNode *plist = NULL;
    SLPushFront(&plist, 1);
    SLPushFront(&plist, 2);
    SLPushFront(&plist, 3);
    SLPushFront(&plist, 4);

    /*plist = SLPushFront(plist, 1);
    plist = SLPushFront(plist, 2);
    plist = SLPushFront(plist, 3);
    plist = SLPushFront(plist, 4);*/

    SLTPrint(plist);

    SLPushBack(&plist, 5);
    SLTPrint(plist);
}

void TestSList2()
{
    printf("=== TestSList2 (Back Push/Pop) ===\n");
    SLTNode *plist = NULL;
    SLPushBack(&plist, 1);
    SLPushBack(&plist, 2);
    SLPushBack(&plist, 3);
    SLPushBack(&plist, 4);
    SLTPrint(plist);

    SLPopBack(&plist);
    SLTPrint(plist);
    SLPopBack(&plist);
    SLTPrint(plist);
    SLPopBack(&plist);
    SLTPrint(plist);
    SLPopBack(&plist);
    SLTPrint(plist);

    //SLPopBack(&plist);
}

void TestSList3()
{
    printf("=== TestSList3 (Find & Modify) ===\n");
    SLTNode *plist = NULL;
    SLPushBack(&plist, 1);
    SLPushBack(&plist, 2);
    SLPushBack(&plist, 3);
    SLPushBack(&plist, 4);
    SLTPrint(plist);

    SLTNode *pos = STFind(plist, 3);
    if (pos)
        pos->data = 30;
    SLTPrint(plist);
}

void TestSList4()
{
    printf("=== TestSList4 (Insert & Erase) ===\n");
    SLTNode *plist = NULL;
    SLPushBack(&plist, 1);
    SLPushBack(&plist, 2);
    SLPushBack(&plist, 3);
    SLPushBack(&plist, 4);
    SLTPrint(plist);

    SLTNode *pos = STFind(plist, 3);
    if (pos)
    {
        SLInsert(&plist, pos, 30);
    }
    SLTPrint(plist);

    pos = STFind(plist, 2);
    if (pos)
    {
        SLInsertAfter(pos, 20);
    }
    SLTPrint(plist);

    pos = STFind(plist, 2);
    if (pos)
    {
        SLErase(&plist, pos);
    }
    SLTPrint(plist);
}

// ---------------------- 演示代码 ----------------------

// 形参的改变不影响实参
void func1(int *p)
{
    *p = 10;
}

void func2(int **pp)
{
    *pp = (int *) malloc(sizeof(int) * 10);
}

void func3(SLTNode *pnode)
{
    pnode->next = NULL;
}

void func4(SLTNode **ppnode)
{
    *ppnode = NULL;
}

void Swapi(int *p1, int *p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void Swappi(int **pp1, int **pp2)
{
    int *tmp = *pp1;
    *pp1 = *pp2;
    *pp2 = tmp;
}

// // 演示函数调用（在main中根据需要取消注释）
// void TestTeachingExamples()
// {
// 	//TestSList2();
// 	// 要改变int，传int的地址
// 	int a = 0;
// 	func1(&a);
//
// 	// 要改变int*，传int*的地址
// 	int* ptr = NULL;
// 	func2(&ptr);
//
// 	// 要改变结构体，传结构体的地址
// 	SLTNode node;
// 	func3(&node);
//
// 	// 要改变结构体指针，传结构体的指针的地址
// 	SLTNode* pnode;
// 	func3(&pnode);
//
// 	int x = 0, y = 1;
// 	Swapi(&x, &y);
//
// 	int* px = &x, * py = &y;
// 	Swappi(&px, &py);
// }

// ---------------------- LeetCode 习题部分 ----------------------
/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * struct ListNode *next;
 * };
 */
// 注意：为了防止与 List.h 中的 struct ListNode (双向链表) 冲突，
struct LCNode
{
    int val;
    struct LCNode *next;
};

struct LCNode *removeElements(struct LCNode *head, int val)
{
    struct LCNode *prev = NULL, *cur = head;
    while (cur)
    {
        if (cur->val == val)
        {
            if (prev == NULL)
            {
                // 头删情况，如果是第一个节点匹配，head需要后移，且prev保持NULL
                head = cur->next;
                free(cur);
                cur = head;
            }
            else
            {
                prev->next = cur->next;
                free(cur);
                cur = prev->next;
            }
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

    return head;
}

void TestLeetCode()
{
    printf("=== Test LeetCode removeElements ===\n");
    struct LCNode *n1 = (struct LCNode *) malloc(sizeof(struct LCNode));
    assert(n1);
    struct LCNode *n2 = (struct LCNode *) malloc(sizeof(struct LCNode));
    assert(n2);
    struct LCNode *n3 = (struct LCNode *) malloc(sizeof(struct LCNode));
    assert(n3);
    struct LCNode *n4 = (struct LCNode *) malloc(sizeof(struct LCNode));
    assert(n4);
    n1->val = 7;
    n2->val = 7;
    n3->val = 7;
    n4->val = 7;

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = NULL;

    n1 = removeElements(n1, 7);
    if (n1 == NULL)
        printf("All elements removed, list is NULL.\n");
}

// ---------------------- 双向链表测试 ----------------------

void TestList1()
{
    printf("=== TestList1 (Back Push/Pop) ===\n");
    LTNode *plist = LTInit();
    LTPushBack(plist, 1);
    LTPushBack(plist, 2);
    LTPushBack(plist, 3);
    LTPushBack(plist, 4);

    LTPrint(plist);

    LTPopBack(plist);
    LTPrint(plist);

    LTPopBack(plist);
    LTPrint(plist);

    LTPopBack(plist);
    LTPrint(plist);

    LTPopBack(plist);
    LTPrint(plist);

    //LTPopBack(plist);
    //LTPrint(plist);

    LTDestroy(plist);
    plist = NULL;
}

void TestList2()
{
    printf("=== TestList2 (Front Push/Pop) ===\n");
    LTNode *plist = LTInit();
    LTPushFront(plist, 1);
    LTPushFront(plist, 2);
    LTPushFront(plist, 3);
    LTPushFront(plist, 4);
    LTPrint(plist);

    LTPopFront(plist);
    LTPrint(plist);

    LTPopFront(plist);
    LTPrint(plist);

    LTPopFront(plist);
    LTPrint(plist);

    LTPopFront(plist);
    LTPrint(plist);

    /*LTPopFront(plist);
    LTPrint(plist);*/

    LTDestroy(plist);
    plist = NULL;
}

void TestList3()
{
    printf("=== TestList3 (Find & Insert) ===\n");
    LTNode *plist = LTInit();
    LTPushFront(plist, 1);
    LTPushFront(plist, 2);
    LTPushFront(plist, 3);
    LTPushFront(plist, 4);
    LTPrint(plist);

    LTNode *pos = LTFind(plist, 3);
    if (pos)
    {
        LTInsert(pos, 30);
    }
    LTPrint(plist);

    LTDestroy(plist);
    plist = NULL;
}


int main()
{
    // 单链表测试
    TestSList1();
    TestSList2();
    TestSList3();
    TestSList4();

    // 演示
    // TestTeachingExamples();

    // LeetCode 测试
    TestLeetCode();

    // 双向链表测试
    TestList1();
    TestList2();
    TestList3();

    return 0;
}