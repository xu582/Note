#include<stdio.h>
#include "queue.h"

/* 测试队列是否为空的例程 ---- 数组实现 */
int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

/* 构造空队列的例程 ---- 数组实现 */
void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

/* 入队的例程 ---- 数组实现 */
static int Succ(int Value, Queue Q)
{
    if( ++Value == Q->Capacity)
    {
        Value = 0;
    }
    return Value;
}

void Enqueue(ElementType X, Queue Q)
{
    if(IsFull(Q))
    {
        printf("Error: Full queue");
    }
    else
    {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);
