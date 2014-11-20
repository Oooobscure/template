//poj.org/showsource?solution_id=13458776>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
using namespace std;
#define Rep(i,n) for (int __n=(n),i=0;i<__n;i++)
#define For(i,b,n) for (int __n=(n),i=(b);i<=__n;i++)
typedef long long LL;
using namespace std;
const int msqN=100000+10,mlogN=10;
LL Ap[msqN];
int gcd(int a,int b)
{
	if (a%b==0)
		return b;
	else
		return gcd(b,a%b);
}
const int mD=6000011;
class Hashar
{
public:
	int hash[mD+10000],st[mD+10000],real[mD+10000],tst;
	Hashar()
	{
		memset(hash,-1,sizeof(hash));
		tst=0;
	}
	int getp(int h)
	{
		int x=(h*2+1)%mD;
		while (hash[x]!=-1 && hash[x]!=h)
			x++;
		return x;
	}
	void insert(int x,int y)
	{
		int p=getp(x);
		if (hash[p]==x)
			return;
		hash[p]=x;
		real[p]=y;
		st[++tst]=p;
	}
	int get(int x)
	{
		int p=getp(x);
		if (hash[p]==x)
			return real[p];
		else
			return -1;
	}
	void clear()
	{
		while (tst)
		{
			hash[st[tst--]]=-1;
		}
	}
} hashone;
void init()
{
	hashone.clear();
}
int bsgs(int A,int B,int C)
{
    init();
	LL tmp=1;
	B%=C;
	For(i,0,mlogN)//cnt+1
	{
		if (tmp==B)
			return i;
		tmp=(tmp*A)%C;
	}
	int cnt=0;
	int k;
	tmp=1;
	while ((k=gcd(A,C))!=1)
	{
		if (B%k!=0)
			return -1;
		C/=k;
		B/=k;
		cnt++;
		tmp=(tmp*A/k)%C;
	}
	if (gcd(B,C)>1)
		return -1;
	LL D=tmp;
	int sqrtn=ceil(sqrt(C))+1;
	Ap[0]=1;
	For(i,1,sqrtn)
		Ap[i]=(Ap[i-1]*A)%C;
	for (int i=sqrtn-1;i>=0;i--)
	{
		hashone.insert((Ap[i]*B)%C,i);
	}
	LL gs=Ap[sqrtn],now=Ap[sqrtn]*D%C;
	int gt;
	For(i,1,sqrtn-1)
	{
		if ((gt=hashone.get(now))!=-1)
			return i*sqrtn-gt+cnt;
		now=(now*gs)%C;
	}
	return -1;
}
int main()
{
	//freopen("bg.in","r",stdin);
	int a,b,c;
	for(;scanf("%d%d%d",&a,&c,&b),(a || b || c);)
	{
		int k=bsgs(a,b,c);
		if (k==-1)
		{
			printf("No Solution\n");
		}
		else
			printf("%d\n",k);
	}
	return 0;
}


