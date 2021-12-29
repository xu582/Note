#ifndef _Stack_h

#ifndef null
#define null 0
#endif  /* 0 */

#ifndef NULL
#define NULL 0
#endif  /* 0 */

struct Node;
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack(void);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);


#endif  /* _Stack_h */

/* Place in implementation file */
/* Stack implementation is a linked list with a header */
struct Node
{
    ElementType Element;
    PtrToNode Next;
};