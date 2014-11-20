int dfs(int u,int flow)
{
    if (u==ed) return flow;
    int tp,lft=flow;
    for (int go=head[u];go;go=next[go])
    if (w[go]&&d[y[go]]<d[u])    
    {
        tp=dfs(y[go],min(w[go],lft));
        lft-=tp;
        w[go]-=tp;
        w[go^1]+=tp;
        if (lft==0) return flow;
    }
    sd[d[u]]--;
    if (sd[d[u]]==0) flag=false;
    d[u]++; 
    sd[d[u]]++;
    return flow-lft;
}

void Maxflow()
{
    st=1; ed=n;
    memset(d,0,sizeof(d));
    memset(sd,0,sizeof(sd));
    sd[0]=n;//总点数
    flag=true; ans=0;
    while (flag) ans+=dfs(st,oo);
    cout<<ans<<endl;  
}
