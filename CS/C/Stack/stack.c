#include<stdio.h>
#include "stack.h"


/* 测试栈是否位空栈的例程----链表实现 */
int IsEmpty(Stack S)
{
    return S->Next == NULL;    
}

/* 创建一个空栈例程----链表实现 */
Stack CreateStack( void )
{
    Stack S;

    S = malloc(sizeof(struct Node));
    if(S == NULL)
    {
        printf("Error: Out of space!!!");
    }
    S->Next == NULL;
    MakeEmpty(S);
    return S;
}

void MakeEmpty(Stack S)
{
    if(S == NULL)
    {
        printf("Error: Must use CreateStack first");
    }
    else
    {
        while (!IsEmpty(S))
        {
            Pop(S);
        }
        
    }
}

/* Push进栈的例程----链表实现 */
void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;

    TmpCell = malloc(sizeof(struct Node));
    if(TmpCell == NULL)
    {
       printf("Error: Out of space!!!");
    }
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    } 
}

/* 返回栈顶元素例程----链表实现 */
ElementType Top(Stack S)
{
    if(!IsEmpty(S))
    {
        return S->Next->Element;
    }
    printf("Error: Empty stack");
    return 0;   /* Return value used to avoid warning */
}

/* 从栈弹出元素的例程----链表实现 */
void Pop(Stack S)
{
    PtrToNode FirstCell;

    if(IsEmpty(S))
    {
        printf("Error: Empty stack");
    }
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free(FirstCell);
    }
}