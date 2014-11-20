queue<int> Q;
void add(int xx,int yy,int ww)
{
    y[++tot]=yy; x[tot]=xx; w[tot]=ww;
    Next[tot]=head[xx]; head[xx]=tot;
    y[++tot]=xx; x[tot]=yy; w[tot]=0;
    Next[tot]=head[yy]; head[yy]=tot;
}

void bfs()
{
    memset(d,-1,sizeof(d));
    memset(sd,0,sizeof(sd));
    sd[0]=1; d[ed]=0;
    Q.push(ed);
    while (!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for (int go=head[u];go;go=Next[go])
        {
            if (w[go]!=0||d[y[go]]!=-1) continue;
            Q.push(y[go]);
            sd[d[y[go]]=d[u]+1]++;
        }
    }
}

int Dinic()
{
    bfs();
    For(i,1,n) now[i]=head[i];
    int res=0,top=0,u=st;
    while (d[st]<n)
    {
        if (u==ed)
        {
            int tp=oo,inser=n;
            for (int i=0;i!=top;i++)
            if (tp>w[stk[i]])
            {
                tp=w[stk[i]]; inser=i;
            }
            for (int i=0;i!=top;i++)
            {
                w[stk[i]]-=tp; w[stk[i]^1]+=tp;
            }
            res+=tp; top=inser;
            u=x[stk[top]];
        }
        if (u!=ed&&sd[d[u]-1]==0) break;
        int go;
        for (go=now[u];go;go=Next[go])
            if (w[go]!=0&&d[u]==d[y[go]]+1) break;
        if (go)
        {
            now[u]=go; stk[top++]=go; u=y[go];
        } else
        {
            int mi=n;
            for (go=head[u];go;go=Next[go])
            {
                if (w[go]==0) continue;
                if (mi>d[y[go]])
                {
                    mi=d[y[go]]; now[u]=go;
                }
            }
            sd[d[u]]--;
            sd[d[u]=mi+1]++;
            if (u!=st) u=x[stk[--top]];
        }
    }
    return res;
}
