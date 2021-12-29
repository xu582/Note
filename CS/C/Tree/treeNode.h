#ifndef _TreeNode_h
#define _TreeNode_h

#ifndef NULL
#define NULL (0)
#endif /* NULL = 0 */

struct TreeNode;
typedef struct TreeNode* Position;
typedef struct TreeNode* SearchTree;

typedef int ElementType;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);

#endif /* _TreeNode_h */

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};
