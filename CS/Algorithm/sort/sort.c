#include<stdio.h>

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");

}

void shellSort(int arr[], int n)
{
    int step;
    int i, tmp;

    for (step = n / 2; step > 0; step /= 2)
    {
        /*step = 4 2 1*/
        for (i = step; i < n; i++)
        {
            int j = i;
            tmp = arr[j];
            while (j - step >= 0 && arr[j - step] > tmp)
            {
                arr[j] = arr[j - step];
                j = j - step;
            }
            arr[j] = tmp;
        }
        pr_arr(arr, n);
    }
}

void bubbleSort(int a[], int n)
{
    int i, j, temp;

    for (i = 1; i <= n - 1; i++)
    {
        for (j = 0; j < n - i; j++)
        {
            if (a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printArr(a, 10);
}

int main()
{
    int a[10] = { 88, 66, 22, 11, 44, 77, 99, 55, 33, };
    printArr(a, 10);
    //shellSort(a, 10);
    bubbleSort(a, 10);

    return 0;
}
