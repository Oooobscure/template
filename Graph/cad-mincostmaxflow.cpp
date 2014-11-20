//http://codevs.cn/problem/1803/
//mincostmaxflow && spfa
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
#include <queue>
#include <cassert>
using namespace std;
#define Rep(i,n) for (int __n=(n),i=0;i<__n;i++)
#define For(i,b,n) for (int __n=(n),i=(b);i<=__n;i++)
typedef long long LL;
using namespace std;
const int mN=1000+100,mM=2*((10000+mN)+mN)+100;//2*(ce+mN)
const LL ooc=1e18;
LL dis[mN],inf[mN];
LL mcmf;
bool ha[mN];
int fir[mN],pre[mN];
int S,T,te=1;
queue<int> q;
struct Edge
{
    int x,y,n;
    LL c,f;
} e[mM];
void addre(int from,int to,LL f,LL c)
{
         te++;
    e[te].x=from;
    e[te].y=to;e[te].f=f;e[te].c=c;
    e[te].n=fir[from];fir[from]=te;
}
void addce(int from,int to,LL lb,LL ub,LL c)
{
    addre(from,to,ub-lb,c);
    addre(to,from,0,-c);
    mcmf+=c*lb;
    inf[to]+=lb;
    inf[from]-=lb;
}
bool spfa()
{
    For(i,1,T)
        dis[i]=ooc;
    dis[S]=0;
    q.push(S);
    while (!q.empty())
    {
        int x=q.front();q.pop();ha[x]=false;
        for(int eg=fir[x];eg;eg=e[eg].n)
            if (e[eg].f>0)
            {
                int y=e[eg].y;
                if (dis[y]>dis[x]+e[eg].c)
                {
                                            dis[y]=dis[x]+e[eg].c;
                    assert(dis[x]>=0);
                    pre[y]=eg;
                    if (!ha[y])
                    {
                        q.push(y);
                        ha[y]=true;
                    }
                }
            }
    }
    return dis[T]<ooc;
}
LL mincostmaxflow(int n)
{
    S=n+1,T=n+2;
    For(i,1,n)
        if (inf[i]>0)
        {
            addre(S,i,inf[i],0);
            addre(i,S,0,0);
        }
        else if (inf[i]<0)
        {
            addre(i,T,-inf[i],0);
            addre(T,i,0,0);
        }

    mcmf=0;
    while (spfa())
    {
        int now=T;
        LL mF=ooc;
        while (now!=S)
        {
            mF=min(mF,e[pre[now]].f);
            now=e[pre[now]].x;
        }
        mcmf+=dis[T]*mF;
        now=T;
        while (now!=S)
        {
            e[pre[now]].f-=mF;
            e[pre[now]^1].f+=mF;
            now=e[pre[now]].x;
        }
    }
    return mcmf;
}
void init()
{
    te=1;
}
void clear()
{
    For(i,1,T)
    {
        inf[i]=0;
        fir[i]=0;
    }
}
int main()
{
    int n,m;
    while (scanf("%d%d",&n,&m)==2)
    {
        init();
        int tv=n+1;//tot vertex
        For(i,1,n)
        {
            int x;
            scanf("%d",&x);
            addce(i,i+1,x,ooc,0);
        }
        For(i,1,m)
        {
            int lrg,rrg;
            LL c;
            scanf("%d%d%lld",&lrg,&rrg,&c);
            addce(rrg+1,lrg,0,ooc,c);
        }
        printf("%lld\n",mincostmaxflow(tv));
        clear();
    }
	return 0;
}
