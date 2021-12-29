#include<stdio.h>
#include<stdlib.h>
//#include<malloc.h>
#include "treeNode.h"


SearchTree MakeEmpty(SearchTree T)
{
	if (T!=NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X, SearchTree T)
{
	if (T == NULL)
	{
		return NULL;
	}

	if (X < T->Element)
	{
		return Find(X, T->Left);
	}
	else if (X > T->Element)
	{
		return Find(X, T->Right);
	}
	else
	{
		return T;
	}
}

/* 对二叉查找树的 FindMin 的递归实现 */
Position FindMin(SearchTree T)
{
	if (T == NULL)
	{
		return NULL;
	}
	else if (T->Left == NULL)
	{
		return T;
	}
	else
	{
		return FindMin(T->Left);
	}
}

/* 对二叉查找树的 FindMax 的非递归实现 */
Position FindMax(SearchTree T)
{
	if (T != NULL)
	{
		while (T->Right != NULL)
		{
			T = T->Right;
		}
	}
	return T;
}

/* 插入元素到二叉树的例程 */
SearchTree Insert(ElementType X, SearchTree T)
{
	if (T == NULL)
	{
		/* Create and return a one-node tree */
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if (T == NULL)
		{
			printf("Out of space!!!");
		}
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}	
	}
	else if(X < T->Element)
	{
		T->Left = Insert(X, T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = Insert(X, T->Right);
	}

	return T;
}

/* 二插查找树的删除例程 */
/****
*	1. 如果节点是一片树叶，那么它可以被立即删除
*	2. 如果节点有一个儿子，则该节点可以在其父节点调整指针绕过该节点后被删除
*	   注意：所删除的节点现在已不再引用，而该节点只有在指向它的指针已被省去的
*	   情况下才能够被去掉
*	3. 如果节点有两个儿子，一般删除策略是用其右子树的最小数据代替该节点的数据并
*	   递归地删除那个节点。
*/
SearchTree Delete(ElementType X, SearchTree T)
{
	Position TmpCell;

	if (T == NULL)
	{
		printf("Error: Element not found");
	}
	else if (X < T->Element)
	{
		T->Left = Delete(X, T->Left);
	}
	else if (X > T->Element)
	{
		T->Right = Delete(X, T->Right);
	}
	else if (T->Left && T->Right)		/* Two children*/
	{
		/* replace with smallest in right subtree */
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
	}
	else								/* one or zero children */
	{
		TmpCell = T;
		if (T->Left == NULL)
		{
			T = T->Right;
		}
		else if (T->Right == NULL)
		{
			T = T->Left;
		}
		free(TmpCell);
	}

	return T;
}
ElementType Retrieve(Position P)
{
	return 0;
}