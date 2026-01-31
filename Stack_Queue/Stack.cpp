#include "Stack.h"

void STInit(ST* pst)
{
    assert(pst);
    pst->a = NULL;

    //pst->top = -1;   // top 指向栈顶数据
    pst->top = 0;   // top 指向栈顶数据的下一个位置

    pst->capacity = 0;
}

void STDestroy(ST* pst)
{
    assert(pst);

    free(pst->a);
    pst->a = NULL;
    pst->top = pst->capacity = 0;
}

void STPush(ST* pst, STDataType x)
{
    if (pst->top == pst->capacity)
    {
        int newCapacity = pst->capacity == 0 ? 4 : pst->capacity * 2;
        STDataType* tmp = (STDataType*)realloc(pst->a, newCapacity * sizeof(STDataType));
        if (tmp == NULL)
        {
            perror("realloc fail");
            return;
        }

        pst->a = tmp;
        pst->capacity = newCapacity;
    }

    pst->a[pst->top] = x;
    pst->top++;
}

void STPop(ST* pst)
{
    assert(pst);
    assert(!STEmpty(pst));

    pst->top--;
}

STDataType STTop(ST* pst)
{
    assert(pst);
    assert(!STEmpty(pst));

    return pst->a[pst->top - 1];
}

bool STEmpty(ST* pst)
{
    assert(pst);

    /*if (pst->top == 0)
    {
        return true;
    }
    else
    {
        return false;
    }*/

    return pst->top == 0;
}

int STSize(ST* pst)
{
    assert(pst);

    return pst->top;
}