#include <iostream>
//#include <stdio.h>
#include "Tree/treeNode.h"

SearchTree Insert(ElementType X, SearchTree T);
void displayTree(SearchTree T)
{
    if (T != NULL)
    {
        //printf("%d--", T->Element);
        std::cout << T->Element << "--";
        displayTree(T->Left);
        displayTree(T->Right);
    }
    
}

int main()
{
    //ElementType x = 5;
    int a[] = { 7,3,4,8,1,2,4,5,6,9,10,0 };
    SearchTree treeA;
    treeA = (SearchTree)malloc(sizeof(struct TreeNode));

    treeA->Element = 5;
    treeA->Left = NULL;
    treeA->Right = NULL;

    std::cout << "Hello World!\n";
    displayTree(treeA);
    for (int  i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        Insert(a[i], treeA);
    }
    std::cout << "\n";
    Insert(4, treeA);
    displayTree(treeA);
    return 0;
}

