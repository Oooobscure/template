int lca(int u,int v)
{
    if (dep[u]>dep[v]) swap(u,v);
    int k=dep[v]-dep[u];
    for (int j=S-1;j>=0;j--)
        if (k&(1<<j)) v=fa[v][j];
    if (u==v) return u;
    for (int j=S-1;j>=0;j--)
        if (fa[u][j]!=fa[v][j])
        {
            u=fa[u][j]; v=fa[v][j];
        }
    return fa[u][0];
}
