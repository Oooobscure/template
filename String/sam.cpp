//suffix automaton
//Problem: 2774	User: 137466930
//Memory: 15408K	Time: 125MS
//Language: G++	Result: Accepted
//	 Source Code
	#include <iostream>
#include <cstdio>
#include <cstring>
#define Rep(i,n) for (int i=0;i<(n);i++)
#define For(i,b,n) for (int i=b;i<=(n);i++)
	using namespace std;
const int mCH=26,mN=250000+100;
struct node
{
    int l;
    node *p;
    node *trs[mCH];
    node(){}
    node(int _l,node *_p):l(_l),p(_p)
    {
        memset(trs,0,sizeof(trs));
    }
} sdata[mN*2],*top;
node *root,*curn;
//#define ms(x) cout<<x<<endl;
void outtree(node *p,node *fa)
{
//    ms(p->l<<"fais"<<fa->l);
    for (int i=0;i<mCH;i++)
        if (p->trs[i])
            outtree(p->trs[i],p);
}
void build(int n,char a[])
{
    top=sdata;
    root=curn=top++;root[0]=node(0,NULL);
    Rep(i,n)
    {
        int x=a[i]-'a';
        node *p=curn;
        curn=top++;curn[0]=node(i+1,NULL);
        for(;p && p->trs[x]==NULL;p=p->p)
            p->trs[x]=curn;
        if (!p)
            curn->p=root;
        else
        {
            node *tp=p->trs[x];
            if (tp->l==p->l+1)
            {
                curn->p=tp;
	}
            else
            {
                node *r=top++;
                r[0]=tp[0];
                r->l=p->l+1;
                tp->p=r;
                curn->p=r;
                for(;p && p->trs[x]==tp;p=p->p)
                    p->trs[x]=r;
            }
        }
        outtree(root,root);
    }
}
char A[mN],B[mN];
	int main()
{
    scanf("%s%s",A,B);
    int na=strlen(A),nb=strlen(B);
    build(na,A);
    node *p=root;
    int ans=0,ml=0;
    Rep(i,nb)
    {
        int x=B[i]-'a';
        if (p->trs[x])
        {
            p=p->trs[x];
	ml++;
        }
        else
        {
            while (p && p->trs[x]==NULL)
            {
                p=p->p;
            }
            if (!p)
            {
                p=root;
                ml=0;
            }
            else
            {
                ml=p->l+1;
                p=p->trs[x];
            }
        }
        ans=max(ans,ml);
    }
	printf("%d\n",ans);
    return 0;
}
