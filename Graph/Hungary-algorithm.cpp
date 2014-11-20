bool dfs(int u)
{
    for (int go=head[u];go;go=next[go])
    if (!vis[y[go]])
    {
        vis[y[go]]=true;
        if (match[y[go]]==0||dfs(match[y[go]]))
        {
            match[y[go]]=u;
            return true;    
        }
    }
    return false;
}

void Match()
{
    ans=0; 
    memset(match,0,sizeof(match));
    for (i=1;i<=q;i++)
    {
        memset(vis,false,sizeof(vis));  
        if (dfs(i)) ans++;
    }    
}
