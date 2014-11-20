//suffix array  SA
//hdu 5030
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#define Rep(i,n) for(int i=0,_n=(n);i<_n;i++)
#define For(i,l,r) for(int i=(l),_r=(r);i<=_r;i++)
using namespace std;
typedef long long LL;
const int mSa=100000+100,oo=1e9;
int rank[mSa*2],tmp[mSa],sa[mSa],tax[mSa],het[mSa],tol[mSa];
char s[mSa];
int b[129];
int len,kq;
void sorts(int o)
{
    For(i,0,len)
        tax[i]=0;
    For(i,1,len)
        tax[rank[sa[i]+o]]++;
    For(i,1,len)
        tax[i]+=tax[i-1];
    for (int i=len;i>0;i--)
    {
        tmp[tax[rank[sa[i]+o]]]=sa[i];
        tax[rank[sa[i]+o]]--;
    }
    For(i,1,len)
        sa[i]=tmp[i];
}

LL pf[mSa],spf[mSa];

LL set_subs()
{
    spf[0]=0;
    For(i,1,len)
    {
        pf[i]=max(0,len-sa[i]+1-het[i]);
        spf[i]=spf[i-1]+pf[i];
    }
    return spf[len];
}

int gridy()
{
    if (tol[1]<0)
        return oo;
    int l,r=0,nr=1,lv=0;
    while (1)
    {
        lv++;
        l=r+1;r=nr;
        For(i,l,r)
            if (tol[i]>=0)
                nr=max(nr,i+tol[i]);
        if (r==nr)
            return oo;
        if (nr>len)
            return lv;
    }
}
bool tryit(LL w)
{
    For(i,1,len)
        tol[i]=-1;
    int nhet=0;
    For(i,1,len)
    {
        if (w>pf[i])
        {
            tol[sa[i]]=pf[i]+het[i];
            w-=pf[i];
        }
        else if (w>0)
        {
            tol[sa[i]]=w+het[i];
            nhet=w+het[i];
            w=0;
        }
        else
        {
            nhet=min(nhet,het[i]);
            if (nhet==0)
                break;
            tol[sa[i]]=nhet;
        }
    }
    for (int i=len-1;i>0;i--)
    {
        if (tol[i]>=0)
            tol[i]=min(tol[i],max(tol[i+1]+1,1));
    }
    return (gridy()<=kq);
}
void outans(LL w)
{
    For(i,1,len)
        if (w>pf[i])
        {
            w-=pf[i];
        }
        else
        {
            For(j,sa[i],sa[i]+het[i]+w-1)
                putchar(s[j]);
            putchar('\n');
            break;
        }
}
int main()
{
    while (scanf("%d",&kq),kq!=0)
    {
        char ch=getchar();
        while (!isalpha(ch))
            ch=getchar();
        len=0;
        while (isalpha(ch))
        {
            s[++len]=ch;
            ch=getchar();
        }
        For(i,0,len*2)//!!!!!!!!!!
            rank[i]=0;
        s[len+1]='#';//!!!!!!!!!!
        memset(b,0,sizeof(b));
        For(i,1,len)
            b[s[i]]=1;
        For(i,'a'+1,'z')
            b[i]+=b[i-1];
        For(i,1,len)
            rank[i]=b[s[i]];
        For(i,1,len)
            sa[i]=i;
        for (int z=1;z<len;z*=2)
        {
            sorts(z);
            sorts(0);
            For(i,1,len)
            {
                tmp[sa[i]]=tmp[sa[i-1]];
                if (rank[sa[i]]!=rank[sa[i-1]] || rank[sa[i]+z]!=rank[sa[i-1]+z])
                    tmp[sa[i]]++;
            }
            For(i,1,len)
                rank[i]=tmp[i];
        }
        het[len]=0;//!!!!!!!!!!
        For(i,1,len)
            if (rank[i]!=len)//!!!!!!!!!!
            {
                int z=max(0,het[rank[i-1]]-1);
                int next=sa[rank[i]+1];
                while (s[i+z]==s[next+z])
                    z++;
                het[rank[i]]=z;
            }
        for(int i=len;i>=2;i--)
            het[i]=het[i-1];
        het[1]=0;
        LL rb=set_subs(),lb=1;
        while (lb<rb)
        {
            LL mid=(lb+rb)/2;
            if (tryit(mid))
                rb=mid;
            else
                lb=mid+1;
        }
        outans(lb);
    }
    return 0;
}
