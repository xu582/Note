#include "sort.h"

/**
 * @brief 插入排序 O(n^2)
 * 由于嵌套循环的每一个都花费 N 次迭代，因此插入排序为 O(n^2)，
 * 另一方面，如果输入数据已预先，排序，那么运行时间为 O(n)，
 * 因为内层for循环的检测总是立即判定不成立
 * 逆序
 */
void InsertionSort(ElementType A[], int N)
{
    int j, P;

    ElementType Tmp;
    for (P = 1; P < N; P++) //第1趟(P = 1),最多 P = N-1
    {
        Tmp = A[P];
        for (j = P; j > 0 && A[j - 1] > Tmp; j--) //逆序
        {
            A[j] = A[j - 1];
        }
        A[j] = Tmp;
    }
}

/**
 * @brief 希尔排序
 * 增量排序（Sedgewick）
 * 
 * @param A 
 * @param N 
 */
void ShellSort(ElementType A[], int N)
{
    int i, j, Increment;
    ElementType Tmp;

    for (Increment = N / 2; Increment > 0; Increment /= 2)
    {
        for (i = Increment; i < N; i++)
        {
            Tmp = A[i];
            for (j = i; j >= Increment; j -= Increment)
            {
                if (Tmp < A[j - Increment])
                    A[j] = A[j - Increment];
                else
                    break;
            }
        }
    }
}

/**
 * @brief 创建 大顶堆Heap，最大的值在父节点，
 * 
 * @param A 
 * @param i 
 * @param N 
 */
void PercDown(ElementType A[], int i, int N)
{
    int Child;
    ElementType Tmp;

    for (Tmp = A[i]; LeftChild(i) < N; i = Child)
    {
        Child = LeftChild(i);
        if (Child != N - 1 && A[Child + 1] > A[Child])
            Child++;
        if (Tmp < A[Child])
            A[i] = A[Child];
        else
            break;
    }
    A[i] = Tmp;
}

/**
 * @brief 堆排序， O(N(log N))
 * 
 * @param A 
 * @param N 
 */
void HeapSort(ElementType A[], int N)
{
    int i;

    for (i = N / 2; i >= 0; i--) /* BuildHeap */
        PercDown(A, i, N);

    for (i = N - 1; i > 0; i--)
    {
        Swap(&A[0], &A[i]); /* DeleteMax */
        PercDown(A, 0, i);
    }
}

/**
 * @brief 递归归并，该算法是经典的分治（divide-and-conquer）策略
 * 将问题分成一些小问题然后递归求解，而治的阶段则将分的阶段解的各个答案修补在一起。
 * 
 * @param A 
 * @param TmpArray 
 * @param Left 
 * @param Right 
 */

void MSort(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
    int Center;

    if (Left < Right)
    {
        Center = (Left + Right) / 2;
        MSort(A, TmpArray, Left, Center);
        MSort(A, TmpArray, Center + 1, Right);
        Merge(A, TmpArray, Left, Center + 1, Right);
    }
}

/**
 * @brief 归并排序 O(NlogN)
 * 
 * @param A 
 * @param N 
 */
void MergeSort(ElementType A[], int N)
{
    ElementType *TmpArray;

    TmpArray = malloc(N * sizeof(ElementType));
    if (TmpArray != NULL)
    {
        MSort(A, TmpArray, 0, N - 1);
        free(TmpArray);
    }
    else
        FatalError();
}

/**
 * @brief Lpos ： start of left half,Rpos : start of right half
 * 
 * @param A 
 * @param TmpArray 
 * @param Lpos 
 * @param Rpos 
 * @param RightEnd 
 */
void Merge(ElementType A[], ElementType TmpArray[], int Lpos, int Rpos, int RightEnd)
{
    int i, LeftEnd, NumElements, TmpPos;
    LeftEnd = Rpos - 1;
    TmpPos = Lpos;
    NumElements = RightEnd - Lpos + 1;

    /* main loop */
    while (Lpos <= LeftEnd && Rpos <= RightEnd)
    {
        if (A[Lpos] <= A[Rpos])
            TmpArray[TmpPos++] = A[Lpos++];
        else
            TmpArray[TmpPos++] = A[Rpos++];
    }

    /* Copy rest of loop */
    while (Lpos < LeftEnd)
    {
        TmpArray[TmpPos++] = A[Lpos++];
    }
    while (Rpos < RightEnd)
    {
        TmpArray[TmpPos++] = A[Rpos++];
    }

    /* Copy TmpArray back */
    for (i = 0; i < NumElements; i++, RightEnd--)
    {
        A[RightEnd] = TmpArray[RightEnd];
    }
}

/**
 * @brief 快排（QuickSort）
 * 驱动程序
 * 
 * @param A 
 * @param N 
 */
void QuickSort(ElementType A[], int N)
{
    Qsort(A, 0, N - 1);
}

/**
 * @brief 实现三数中值分割方法程序
 * return median of Left,Center,and Right
 * Order these and hide the pivot
 * 
 * @param A 
 * @param Left 
 * @param Right 
 * @return ElementType 
 */
ElementType Median3(ElementType A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;

    if (A[Left] > A[Center])
        Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])
        Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right])
        Swap(&A[Center], &A[Right]);

    /* Invariant: A[Left] <= A[Center] <= A[Right] */
    Swap(&A[Center], &A[Right - 1]); /*Hide pivot*/
    return A[Right - 1];
}

/**
 * @brief 快速排序主例程
 * 
 * @param A 
 * @param Left 
 * @param Right 
 */
void Qsort(ElementType A[], int Left, int Right)
{
    int i, j;
    ElementType Pivot;

    if(Left + Cutoff <= Right)
    {
        Pivot = Median3(A, Left, Right);
        i = Left; j = Right - 1;

        for(;;)
        {
            while(A[++i] < Pivot){}
            while(A[--j] > Pivot){}
            if(i < j)
                Swap(&A[i],&A[j]);
            else
                break;
        }
        Swap(&A[i], &A[Right - 1]);     /*Restore pivot*/

        Qsort(A,Left,i-1);
        Qsort(A,i+1,Right);
    }
    else    /* Do an insertion sort on the subarray */
        InsertionSort(A+Left,Right - Left + 1);
}

void quickSort2(int a[], int left, int right)
{
    int i, j, t, pivot;

    i = left+1; j = right;
    pivot = a[left];
    if (left < right)
    {
        for (;;)
        {
            while (a[i] <= pivot) { i++; }
            while (a[j] > pivot) { j--; }
            if (i > j)
                break;
            else
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }

        }

        
        t = a[j];
        a[j] = a[left];
        a[left] = t;
        

        quickSort2(a, left, j-1);
        quickSort2(a, i, right);
    }
    else
    {
        return;
    }
    

}
