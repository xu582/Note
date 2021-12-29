#ifndef _Stack_h

#ifndef null
#define null 0
#endif  /* 0 */

#ifndef NULL
#define NULL 0
#endif  /* 0 */

struct StackRecord;
typedef int ElementType;
typedef struct StackRecord *Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

#endif  /* _Stack_h */

/* Place in implementation file */
/* Stack implementation is a dynamically allocated array */
#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};
