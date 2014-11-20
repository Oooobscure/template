/*
	题意：给出m种不同重量的石子, 每一种石子的个数无穷多。从中选出N个石子，排成一个环，使得环上的石子重量的最大公约数为1. 旋转同构视为相同方案。
*/
#include <iostream>
#include <map>
#include <cstdio>
#include <vector>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
#define Rep(i,n) for (long long n__=(n),i=0;i<n__;i++)
#define For(i,l,r) for (long long r__=(r),i=(l);i<=r__;i++)
 
long long gcd(long long a,long long b)
{
    if (b==0) return a;
    return gcd(b,a%b);
}
 
map<long long,long long> f;
 
long long mo;
 
inline long long power(long long a,int x)
{
    if (a==0) return 0;
    long long ans=1;
    while (x>0)
    {
        if ((x&1)==1)
            ans=ans*a%mo;
        a=a*a%mo;
        x >>= 1;
    }
    return ans;
}
 
vector<pair<long long,long long> >c;
 
long long calc(long long x)
{
    if (f.find(x)!=f.end())
        return f[x];
    long long ans=0;
    Rep(i,c.size())
        ans=(ans+c[i].second*power(x,c[i].first)) % mo;
    f[x]=ans;
    return ans;
}
 
long long ny(long long x)
{
    For(i,1,mo-1)
        if ((i*x % mo) == 1) return i;
}
 
const long long lmt=10005;
vector<long long> ys[lmt];
long long u[lmt],num[lmt];
map<long long,long long>p;
 
int main()
{
    //freopen("1.in","r",stdin);
    For(i,1,lmt-1)
        for (long long j=i;j<lmt;j+=i)
            ys[j].push_back(i);
    u[1]=1;
    For(i,2,lmt-1)
        if (i % (ys[i][1]*ys[i][1]) == 0) u[i]=0;
        else u[i]=-u[i/ys[i][1]];
    long long _t;
    scanf("%lld",&_t);
    while (_t--)
    {
        long long ma=0;
        long long m,n;
        scanf("%lld%lld",&m,&n);
        Rep(i,m)
        {
            long long x;
            scanf("%lld",&x);
            Rep(j,ys[x].size())
                num[ys[x][j]]++;
            if (x>ma) ma=x;
        }
        p.clear();
        For(i,1,n)
            p[gcd(i,n)]++;
        c.clear();
        for (map<long long ,long long>::iterator x=p.begin();x!=p.end();x++)
            c.push_back(*x);
        mo=n*10007;
//        Rep(i,c.size())
//            cout << i <<' '<<c[i].first << ' ' << c[i].second<< endl;
        long long ans=0;
        f.clear();
        For(i,1,ma)
        {
            if (u[i]==1)
                ans=(ans+calc(num[i])) % mo;
            else if (u[i]==-1)
                ans=(ans-calc(num[i])+mo)%mo;
            //cout << i << ' ' << ans << endl;
        }
        ans=ans / n;
        cout << ans << endl;
        for (int i=1;i<=ma;i++)
            num[i]=0;
    }
    return 0;
}
 
