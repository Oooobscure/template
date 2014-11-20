//Problem : 4966 ( GGS-DDU )     Judge Status : Accepted
//RunId : 11507235    Language : G++    Author : Ample
//Code Render Status : Rendered By HDOJ G++ Code Render Version 0.01 Beta
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;
#define Rep(i,n) for (int n__=(n),i=0;i<n__;i++)
#define For(i,l,r) for (int r__=(r),i=(l);i<=r__;i++)
const int oo=1e9;
struct edge
{
    int from,to,cost;
    edge(){}
    edge(int x,int y,int c):from(x),to(y),cost(c){}
    int next;
};
const int mM=2500+100,mN=500+100;
struct GRAPH
{
    edge e[mM];
    int fir[mN];
    int te;
    void init(int nV)
    {
        te=1;
        For(i,1,nV)
            fir[i]=-1;
    }
    void add(int x,int y,int c)
    {
        te++;
        e[te]=edge(x,y,c);
        e[te].next=fir[x];fir[x]=te;
    }
} g;
int in[mN],pre[mN],hv[mN],ha[mN],s[mN],a[mN];
int Directed_MST(int root,int nV)
{
    int ret=0;
    while (1)
    {
        For(i,1,nV)
            in[i]=oo;
        For(i,2,g.te)
        {
            int to=g.e[i].to;
            if (to==g.e[i].from)
                continue;
            if (g.e[i].cost<in[to])
            {
                in[to]=g.e[i].cost;
                pre[to]=g.e[i].from;
}
        }
        in[root]=0;
        For(i,1,nV)
        {
            if (i!=root && in[i]==oo)
                return -1;
            hv[i]=0;
            ret+=in[i];
            ha[i]=0;
        }
        int cntn=0;
        For(i,1,nV)
            if (i!=root && !hv[i])
            {
                int v=i;
                do
                {
                    hv[v]=i;
                    v=pre[v];
                }
                while (v!=root && hv[v]==0);
if (v!=root && hv[v]==i)
                {
                    ++cntn;
                    int k=v;
                    do
                    {
                        ha[k]=cntn;
                        k=pre[k];
                    }
                    while (v!=k);
                }
            }
        if (cntn==0)
            return ret;
        For(i,1,nV)
            if (!ha[i])
                ha[i]=++cntn;
        For(i,2,g.te)
        {
#define idit__(x) x=ha[(x)]
            if (g.e[i].from!=g.e[i].to)
                g.e[i].cost-=in[g.e[i].to];
            idit__(g.e[i].from);
            idit__(g.e[i].to);
}
        root=ha[root];
        nV=cntn;
    }
}
int ndof(int x,int y)
{
    return s[x-1]+y+1;
}
int main()
{
    int n,m;
    int tz=0;
    while (scanf("%d%d",&n,&m),n!=0 || m!=0)
    {
        s[0]=0;
        For(i,1,n)
        {
            scanf("%d",&a[i]);
            s[i]=s[i-1]+a[i]+1;
        }
        g.init(s[n]+1);
        int root=s[n]+1;
        For(i,1,m)
        {
            int a1,l1,a2,l2,c;
            scanf("%d%d%d%d%d",&a1,&l1,&a2,&l2,&c);
            g.add(ndof(a1,l1),ndof(a2,l2),c);
        }
        For(i,1,n)
        {
            g.add(root,ndof(i,0),0);
            For(j,1,a[i])
                g.add(ndof(i,j),ndof(i,j-1),0);
        }
        printf("%d\n",Directed_MST(root,s[n]+1));
    }
    return 0;
}



