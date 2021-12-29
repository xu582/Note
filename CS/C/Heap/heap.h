#ifndef _BinHeap_H
#define _BinHeap_H

#define NULL 0

struct HeapStruct;
typedef int ElementType;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
int isEmpty(PriorityQueue H);
int isFull(PriorityQueue H);

#endif /* _BinHeap_H */

struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};


