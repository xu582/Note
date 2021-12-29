# Graph

## BFS

```C
bool visited[Max_VERTEX_NUM];   //访问标记数组

void BFSTraverse(Graph G)       //对图G进行广度优先遍历
{
    for(i=0;i<G.vexnum;i++)
        visited[i] = FALSE;     //初始化标记数组
    InitQueue(Q);               //初始化Q
    for(i=0;i<G.vexnum;i++)     //从顶点v开始遍历
        if(!visited[i])         //对每个连通分量调用一次BFS
            BFS(G,i);
}

//广度优先遍历
void BFS(Graph G, int v)        //从定点v出发，广度优先遍历图G
{
    visit(v);
    visited[v] = TRUE;          //对访问初始顶点v标记
    Enqueue(Q,v);               //顶点v入队列Q
    while(!isEmpty(Q))
    {
        DeQueue(Q,v);           //顶点v出队
        for(w=FirstNeighbor(G,v);w>=0;w=NextNrighbor(G,v,w))
        {
            //检测v所有邻接点
            if(!visited[w])     //w为v未访问的邻接顶点
            {
                visit(w);
                visited[w]=TRUE;
                EnQueue(Q,w);
            }//if
        }
    }//while
}
```

## DFS

```C
//树的先根遍历
void PreOrder(TreeNode *R)
{
    if(R!=NULL)
    {
        visit(R);   //访问根节点
        while(R还有下一个子树T)
            PreOrder(T);    //先根遍历下一课子树
    }
}

bool visited[MAX_VERTEX_NUM];           //访问标记数组

void DFSTraverse(Graph G)               //对图G进行深度优先遍历
{
    for(v=0; v < G.vexnum; v++)
        visited[v]=FALSE;               //初始化已访问标记数据
    for(v=0; v < G.vexnum; v++)
        if(!visited[v])
            DFS(G,v);
}

void DFS(Graph G,int v)                 //从顶点v出发，深度优先遍历图G
{
    visit(v);                           //访问顶点v
    visited[v] = TRUE;                  //设已访问标记
    for(w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))
        if(!visited[w])                 //w为u的尚未访问的邻接顶点
        {
            DFS(G,w);
        }//if
}
```
