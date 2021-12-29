/**
 * @file heap.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-16
 * 
 * @copyright Copyright (c) 2021
 */
#include<heap.h>

/* 堆序性质， 最小元总可以在根处找到。 因此，我们常数时间完成附加运算 FindMin */

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue H;

    if(MaxElements < MinPQSize)
        error();

    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if(H == NULL)
        FatalError();

    /* Allocate the array plus one extra for sentinel */
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));

    if(H->Elements == NULL)
        FatalError();

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}

/**
 * @brief Insert
 * 上滤
 * 为将一个元素 X 插入到堆中， 在下一个空闲位置创建一个空Node，否则该堆将不是完全数。
 * 如果 X 可以放在该Node而并不破坏堆的序，那么插入完成。
 * 否则，把Node的父节点上的元素移入该Node中，这样，Node就朝着根的方向上行一步。
 * 继续该过程直到 X 能被放入 空Node 中为止。
 */

/* H->Element[0] is a sentiner */
void Insert(ElementType X, PriorityQueue H)
{
    int i;

    if(isFull(H))
    {
        Error();
        return;
    }

    for(i = ++H->Size; H->Elements[i/2] >X; i /= 2)
        H->Elements[i] = H->Elements[i/2];
    H->Elements[i] = X;
}

/**
 * @brief Delete
 * 下滤
 * 
 */

ElementType DeleteMin(PriorityQueue H)
{
    int i, Child;
    ElementType MinElement, LastElement;

    if(isEmpty(H))
    {
        Error();
        return H->Elements[0];
    }

    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];

    //将最小的儿子节点一步步上移。最后将尾节点放入空的儿子节点上
    for(i=1; i*2 <= H->Size; i = Child)
    {
        Child = i * 2;
        if(Child != H->Size && H->Elements[Child +1] < H->Elements[Child])          //获取值小的儿子节点
            Child++;

        if(LastElement > H->Elements[Child])        //将儿子节点放入其父节点（空节点）上
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;       //再将尾节点放入空节点上
    return MinElement;
}