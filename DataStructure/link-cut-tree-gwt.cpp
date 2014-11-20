#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#define X cout<<'x'<<endl;
using namespace std;


const int N=2e5+4,LGN=30;
int n,maxjump;

struct tnode
{
    int d,sum,tag,no,linkhead,fa[LGN];
    vector<int> edge;
    void clear()
    {
        no=0;
        sum=0;
        tag=0;
        edge.clear();
    }
}t[N];

struct segnode
{
    int count,l,r;
    bool mark,reverse;
}seg[4*N];


void dfs(int u, int d)
{
    t[u].d=d;
    t[u].sum++;
    for (int i=0;i<t[u].edge.size();i++)
    {
        int v=t[u].edge[i];
        if (v==t[u].fa[0]) continue;
        t[v].fa[0]=u;
        dfs(v,d+1);
        if (t[v].sum>t[t[u].tag].sum)
            t[u].tag=v;
        t[u].sum+=t[v].sum;
    }
}

void link_cut()
{
    dfs(1,1);
    int no=0;
    for (int i=1;i<=n;i++)
        if (t[i].no==0)
        {
            t[i].no=++no;
            t[i].linkhead=i;
            int x=i;
            while (t[x].tag!=0)
            {
                x=t[x].tag;
                t[x].no=++no;
                t[x].linkhead=i;
            }
        }
}

void make_fa()
{
    for (int j=1;j<=maxjump;j++)
        for (int i=1;i<=n;i++)
            t[i].fa[j]=t[t[i].fa[j-1]].fa[j-1];
}

void deliver(int p)
{
    if (seg[p].reverse)
    {
//        seg[p].count=(seg[p].r-seg[p].l+1)-seg[p].count;
        if (seg[p].l!=seg[p].r)
        {
            seg[p*2].reverse ^= true;
            seg[p*2].count=seg[p*2].r-seg[p*2].l+1-seg[p*2].count;
            seg[p*2+1].reverse ^= true;
            seg[p*2+1].count=seg[p*2+1].r-seg[p*2+1].l+1-seg[p*2+1].count;
        }
        seg[p].reverse=false;
    }
    if (seg[p].mark)
        if (seg[p].l!=seg[p].r)
        {
            seg[p*2].mark ^= true;
            seg[p*2+1].mark ^=true;
            seg[p].mark=false;
        }
}

void seg_reverse(int p,int l,int r)
{
    //cout<< p << ' ' << l << ' ' << r<<endl;
    if (seg[p].l==l && seg[p].r==r)
    {
        seg[p].reverse ^= true;
        seg[p].count=seg[p].r-seg[p].l+1-seg[p].count;
        return;
    }
    deliver(p);
    int mid=(seg[p].l+seg[p].r) >> 1;
    if (l<=mid) seg_reverse(p*2,l,min(r,mid));
    if (mid<r) seg_reverse(p*2+1,max(l,mid+1),r);
    seg[p].count = seg[p*2].count + seg[p*2+1].count;
}

void seg_mark(int p,int l,int r)
{
    if (seg[p].l==l && seg[p].r==r)
    {
        seg[p].mark ^= true;
        return;
    }
    deliver(p);
    int mid=(seg[p].l+seg[p].r) >> 1;
    if (l<=mid) seg_mark(p*2,l,min(r,mid));
    if (mid<r) seg_mark(p*2+1,max(l,mid+1),r);
}

int seg_count(int p, int l, int r)
{
    //cout << seg[p].l << ' ' << seg[p].r << ' ' << l << ' ' << r << ' ' << seg[p].count << endl;
    if (seg[p].l==l && seg[p].r==r)
        return seg[p].count;
    deliver(p);
    int mid=(seg[p].l+seg[p].r)>>1;
    int ans=0;
    if (l<=mid) ans+=seg_count(p*2,l,min(r,mid));
    if (mid<r) ans+=seg_count(p*2+1,max(l,mid+1),r);
    return ans;
}

bool seg_marked(int p,int x)
{
    deliver(p);
    if (seg[p].l==seg[p].r)
        return seg[p].mark;
    int mid=(seg[p].l+seg[p].r) >> 1;
    if (x<=mid) return seg_marked(p*2,x);
    return seg_marked(p*2+1,x);
}

void seg_build(int p, int l, int r)
{
    seg[p].l=l;
    seg[p].r=r;
    seg[p].count=0;
    seg[p].mark=false;
    seg[p].reverse=false;
    if (l==r) return;
    int mid=(l+r) >> 1;
    seg_build(p*2,l,mid);
    seg_build(p*2+1,mid+1,r);
}

void tree_reverse(int fu,int u)
{
    while (t[t[u].linkhead].d>t[fu].d)
    {
        seg_reverse(1,t[t[u].linkhead].no,t[u].no);
        u=t[t[u].linkhead].fa[0];
    }
    seg_reverse(1,t[fu].no,t[u].no);
}

void tree_mark(int fu,int u)
{
    while (t[t[u].linkhead].d>t[fu].d)
    {
        if (t[u].tag>0)
            seg_reverse(1,t[t[u].tag].no,t[t[u].tag].no);
        seg_mark(1,t[t[u].linkhead].no,t[u].no);
        seg_reverse(1,t[t[u].linkhead].no,t[t[u].linkhead].no);
        u=t[t[u].linkhead].fa[0];
    }
    if (t[u].tag>0)
        seg_reverse(1,t[t[u].tag].no,t[t[u].tag].no);
    seg_mark(1,t[fu].no,t[u].no);
    seg_reverse(1,t[fu].no,t[fu].no);
}

int tree_count(int fu, int u)
{
    int ans=0;
    while (t[t[u].linkhead].d>t[fu].d)
    {
        ans+=seg_count(1,t[t[u].linkhead].no,t[u].no);
        if (seg_marked(1,t[t[t[u].linkhead].fa[0]].no))
            ans += (seg_count(1,t[t[u].linkhead].no,t[t[u].linkhead].no)==0?1:-1);
        u=t[t[u].linkhead].fa[0];
    }
//    cout << t[fu].no << '|'  << t[u].no << endl;
    ans+=seg_count(1,t[fu].no,t[u].no);
//    cout << "ygggg" << ans << endl;
    if (t[fu].linkhead==fu && seg_marked(1,t[t[fu].fa[0]].no))
        ans+= (seg_count(1,t[fu].no,t[fu].no)==0?1:-1);
//    cout << 'y' << ans << endl;
    return ans;
}

void work(int a,int b,int cmd)
{
    if (a==b)
    {
        if (cmd==3) cout << 0 << endl;
        if (cmd==2) tree_mark(a,a);
        return;
    }
    if (t[a].d>t[b].d) swap(a,b);
    int aa=a,bb=b;
    for (int i=maxjump;i>=0;i--)
        if (t[t[bb].fa[i]].d>=t[aa].d)
            bb=t[bb].fa[i];
    for (int i=maxjump;i>=0;i--)
        if (t[bb].fa[i]!=t[aa].fa[i])
        {
            aa=t[aa].fa[i];
            bb=t[bb].fa[i];
        }
//    cout << a <<  ' ' << aa << ' ' << b << ' ' << bb << endl;
    if (cmd == 1)
    {
//        cout << 'x' << a << ' ' << aa << ' ' << b << ' ' << bb << endl;
        if (aa!=bb) tree_reverse(aa,a);
        tree_reverse(bb,b);
        if (aa==bb) tree_reverse(bb,bb);
    }
    if (cmd == 2)
        if (aa!=bb)
        {
            tree_mark(aa,a);
            tree_mark(t[bb].fa[0],b);
        }
        else tree_mark(bb,b);
    if (cmd == 3)
    {
        int ans=0;
        if (aa!=bb) ans+=tree_count(aa,a);
//        cout << aa <<' ' << a;
//        cout << 'x' <<ans << endl;
        ans+=tree_count(bb,b);
//        cout << 'x' << ans << endl;
        if (aa==bb) ans-=tree_count(aa,a);
        cout << ans << endl;
    }
}


void ps()
{
    for (int i=1;i<=n;i++)
    {
        cout << i << ' ' <<  seg_marked(1,t[i].no) << ' ' << seg_count(1,t[i].no,t[i].no) << endl;
    }
}

int main()
{
//    freopen("1.in","r",stdin);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        cin >> n;
        maxjump=log2(n);
        for (int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            t[u].edge.push_back(v);
            t[v].edge.push_back(u);
        }
        link_cut();
        make_fa();
        seg_build(1,1,n);
        int Q;
        cin >> Q;
        while (Q--)
        {
            int cmd,a,b;
            scanf("%d%d%d",&cmd,&a,&b);
//            cin >> cmd >> a >> b;
            work(a,b,cmd);
//            for (int i=1;i<=25;i++)
//                cout <<seg[i].count <<' ';
//            cout << endl;
//            cout << "---" << endl;
//            ps();
//            cout << "---" << endl;
//            cout << Q << ' ';
//            work(8,10,3);
        }
//        work(8,10,3);
        for (int i=1;i<=n;i++)
            t[i].clear();
        memset(t,0,sizeof(t));
    }
    return 0;
}
