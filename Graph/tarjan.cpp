void tarjan(int u)
{
    stk[++top]=u;
    dfn[u]=++tme; low[u]=dfn[u];
    for (int go=head[u];go;go=next[go])
    {
        if (dfn[y[go]]==0) tarjan(y[go]);
        if (fa[y[go]]==0) low[u]=min(low[u],low[y[go]]);
    }
    if (dfn[u]==low[u])
    {
        while (stk[top]!=u) fa[stk[top--]]=u;
        fa[u]=u; top--;
    }
}

void shink()
{
    memset(dfn,0,sizeof(dfn));
    memset(fa,0,sizeof(fa));
    tme=0; top=0;
    for (i=1;i<=2*n;i++) if (dfn[i]==0) tarjan(i);
    for (i=1;i<=top;i++) fa[stk[i]]=stk[i];
}
/*
求桥和割点的Tarjan算法
dfn[u]定义和前面类似，但是low[u]定义为u或者u的子树中能够通过非父子边追溯到的最早的节点的DFS开始时间
一个顶点u是割点，当且仅当满足(1)或(2)
(1) u为树根，且u有多于一个子树。
(2) u不为树根，且满足存在(u,v)为树枝边(或称父子边，即u为v在搜索树中的父亲)，使得dfn(u)<=low(v)。
一条边(u,v)是桥，当且仅当(u,v)为树枝边，且满足dfn(u)<low(v)（前提是其没有重边）。
*/
