//最大流sap
void add(int xx,int yy,int ww)
{
    y[++tot]=yy; w[tot]=ww;
    Next[tot]=head[xx]; head[xx]=tot;
    y[++tot]=xx; w[tot]=0;
    Next[tot]=head[yy]; head[yy]=tot;
}
int dfs(int u,int flow)
{
    if (u==ed) return flow;
    int sig=now[u];//,min_d=Ntot;
    do
    {
        if (w[now[u]])
        {
            if (d[y[now[u]]]+1==d[u])
            {
                int tp=dfs(y[now[u]],min(flow,w[now[u]]));
                if (tp)
                {
                    w[now[u]]-=tp;
                    w[now[u]^1]+=tp;
                    return tp;
                }
            }
           // min_d=min(min_d,d[y[now[u]]]+1);
          //  if (d[st]>Ntot-1) return 0;
        }
        now[u]=Next[now[u]];
        if (now[u]==0) now[u]=head[u];
    } while (sig!=now[u]);
    if (--sd[d[u]]==0) flag=false; // if (sd[d[u]]--==0) d[st]=Ntot;
    sd[++d[u]]++; //sd[d[u]=min_d]++;
    return 0;
}

void Maxflow()
{
    Ntot=n+m+2;
    memset(d,0,sizeof(d)); memset(sd,0,sizeof(sd));
    for (int i=1;i<=Ntot;i++) now[i]=head[i];
    sd[0]=Ntot; ans=0; flag=true;
    while (flag) ans+=dfs(st,k+1); // while (d[st]<Ntot) ans+=dfs(st,k+1);
}
