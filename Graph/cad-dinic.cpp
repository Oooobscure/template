//View Code
//Problem :4975 ( A simple Gaussian elimination problem. )Judge Status :Accepted
//RunId : 11513833 Language : G++ Author :Ample
//Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
#define Rep(i,n) for (int n__=(n),i=0;i<(n__);i++)
#define For(i,b,n) for (int n__=(n),i=(b);i<=n__;i++)
const int oo=1e9,mE=250000+1000+100,mN=1100;
int S,T,tote;
struct edge
{
    int y,c,n;
}e[mE*2];
int fir[mN],fir2[mN],d[mN];
bool hv[mN];
bool bfs()
{
    queue<int> q;
    q.push(S);
    memset(d,0,sizeof(d));
    d[S]=1;
    For(i,1,T)
        fir2[i]=fir[i];
    while (!q.empty() && d[T]==0)
    {
        int x=q.front();
        q.pop();
        for (int xe=fir[x];xe;xe=e[xe].n)
        {
            int y=e[xe].y;
            if (e[xe].c>0 && d[y]==0)
            {
                d[y]=d[x]+1;
                q.push(y);
                if (y==T)
                    break;
            }
        }
    }
    return d[T]!=0;
}
int dfs(int x,int mflow)
{
    if (x==T)
        return mflow;
    int nowf=0;
    for (int xe=fir2[x];xe && nowf<mflow;xe=e[xe].n)
    {
        int y=e[xe].y;
        if (e[xe].c>0 && d[x]+1==d[y])
        {
            int can=min(e[xe].c,mflow-nowf);
            int flow=dfs(y,can);
            if (flow>0)
            {
                nowf+=flow;
                e[xe].c-=flow;
                e[xe^1].c+=flow;
            }
            else
                fir2[x]=e[xe].n;
        }
        else if (e[xe].c==0)
            fir2[x]=e[xe].n;
    }
    return nowf;
}
int dinic(int iS,int iT)
{
    S=iS;
    T=iT;
    int totf=0,flow;
    while (bfs())
    {
        while ((flow=dfs(S,oo)))
            totf+=flow;
    }
    return totf;
}
void adde(int x,int y,int c,int yc=0)
{
    tote++;
    e[tote].y=y;e[tote].c=c;e[tote].n=fir[x];fir[x]=tote;
    tote++;
    e[tote].y=x;e[tote].c=yc;e[tote].n=fir[y];fir[y]=tote;
}
void init(int n)
{
    For(i,1,n)
    {
        fir[i]=0;
        hv[i]=0;
    }
    tote=1;
}
int noww;
bool dfs1(int x,int fa)
{
    hv[x]=noww;
    for (int xe=fir[x];xe;xe=e[xe].n)
    {
        int y=e[xe].y;
        if (e[xe].c>0 && e[xe].y!=fa)
        {
            if (hv[y]==noww)
            {
                return true;
            }
            else if (hv[y])
                continue;
            if ( dfs1(y,x) )
            {
                return true;
            }
        }
    }
    return false;
}
int pd(int s,int t)
{
    dinic(s, t);
    for (int xe = fir[s]; xe; xe = e[xe].n)
    {
        if (e[xe].c!=0)
            return 0;
    }
    For(i,1,t)
    if (!hv[i])
        {
            noww=i;
            if (dfs1(i,0))
                return 2;
        }
    return 1;
}
int main()
{
//    freopen("e.in","r",stdin);
    int tz;
    scanf("%d",&tz);
    For(i,1,tz)
    {
        int n,m;
        printf("Case #%d: ",i);
        scanf("%d%d",&n,&m);
        int s=n+m+1,t=n+m+2;
        init(n+m+2);
        int rt=0;
        For(i,1,n)
        {
            int tot;
            scanf("%d",&tot);
            rt+=tot;
            adde(s,i,tot);
        }
        For(i,n+1,n+m)
        {
            int tot;
            scanf("%d",&tot);
            rt-=tot;
            adde(i,t,tot);
        }
        For(i,1,n)
            For(j,1,m)
                adde(i,j+n,9);
        if (rt!=0)
        {
            printf("So naive!\n");
        } else
        {
            int k=pd(s,t);
            if (k==0)
                printf("So naive!\n");
            else if (k==1)
                printf("So simple!\n");
            else
                printf("So young!\n");
        }
    }
    return 0;
}
