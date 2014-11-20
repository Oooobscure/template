void add(int xx,int yy,int zz,int ww)
{
    y[++tot]=yy; z[tot]=zz; w[tot]=ww;
    Next[tot]=head[xx]; head[xx]=tot;
    y[++tot]=xx; z[tot]=-zz; w[tot]=0;
    Next[tot]=head[yy]; head[yy]=tot;
}

inline bool relax(int u,int go)
{
    if (dis[u]+z[go]<dis[y[go]])
    {
        dis[y[go]]=dis[u]+z[go];
        pre[y[go]]=go;
        return true;
    }
    return false;
}

bool spfa()
{
    For(i,1,ed)
    {
        dis[i]=oo;
        flag[i]=false;
    }
    dis[st]=0;
    Q.push(st);
    while (!Q.empty())
    {
        int tp=Q.front();
        Q.pop();
        flag[tp]=false;
        for (int go=head[tp];go;go=Next[go])
        {
            if (w[go]>0&&relax(tp,go)&&!flag[y[go]])
            {
                flag[y[go]]=true;
                Q.push(y[go]);
            }
        }
    }
    if (dis[ed]!=oo) return true;
    return false;
}

void change(int &res)
{
    int flow=oo;
    for (int k=ed;k!=st;k=y[pre[k]^1])
        flow=min(flow,w[pre[k]]);
    for (int k=ed;k!=st;k=y[pre[k]^1])
    {
        w[pre[k]]-=flow;
        w[pre[k]^1]+=flow;
        res+=flow*z[pre[k]];
    }
}

int Minflow()
{
    int res=0;
    while (spfa()) change(res);
    return res;
}

//若求有上下界无源无汇可行流
void add2(int xx,int yy,int zz,int w0,int w1)
{
    M[yy]+=w0; M[xx]-=w0;
    add(xx,yy,zz,w1-w0);
}
    For(i,1,n+1)
        if (M[i]>0) add(st,i,0,M[i]);
        else add(i,ed,0,-M[i]);
//如果所有从源点流出的弧和流入汇点的弧都满载，那么该网络存在一个可行流

