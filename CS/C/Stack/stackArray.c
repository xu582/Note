#include<stdio.h>
#include "stackArray.h"

/* 创建栈-----数组实现 */
Stack CreateStack(int MaxElements)
{
    Stack S;
    if(MaxElements < MinStackSize)
    {
        printf("Error: Stack Size is too small");
    }

    S = malloc(sizeof(struct StackRecord));
    if(S == NULL)
    {
        printf("Error: Out Of space!!!");
    }

    S->Array = malloc(sizeof(ElementType) * MaxElements);
    if(S->Array == NULL)
    {
        printf("Error: Out of space");
    }
    S->Capacity = MaxElements;
    MakeEmpty(S);

    return S;
}

/* 释放栈 ----- 数组实现 */
void DisposeStack(Stack S)
{
    if(S != NULL)
    {
        free(S->Array);
        free(S);
    }
}

/* 检查一个栈是否为空 ----- 数组实现 */
int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

/* 创建一个空栈的例程 ----- 数组实现 */
void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}

/* 进栈的例程 ----- 数组实现 */
void Push(ElementType X, Stack S)
{
    if(IsFull(S))
    {
        printf("Full Stack");
    }
    else
    {
        S->Array[++ S->TopOfStack] = X;
    }
}

/* 将栈顶返回的例程 ----- 数组实现 */
ElementType Top(Stack S)
{
    if(!IsEmpty(S))
    {
        return S->Array[S->TopOfStack];
    }

    printf("Error: Empty stack");
    return 0;   /* Return value used to avoid warning */
}

/* 从栈弹出元素的例程 ----- 数组实现 */
void Pop(Stack S)
{
    if(IsEmpty(S))
    {
        printf("Error: Empty stack");
    }
    else
    {
        S->TopOfStack--;
    }
}

/* 给出栈顶元素并从栈弹出的例程 ----- 数组实现 */
ElementType TopAndPop(Stack S)
{
    if(!IsEmpty(S))
    {
        return S->Array[S->TopOfStack--];
    }
    printf("Error: Empty stack");
    return 0;   /* Return value used to avoid warning */
}