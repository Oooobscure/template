#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <stack>
#define Rep(i,n) for(int i=0,_n=(n);i<_n;i++)
#define For(i,l,r) for(int i=(l),_r=(r);i<=_r;i++)
using namespace std;

int n,m,printnum;
struct sp_node
{
    int value,size;
    sp_node *ch[2],*p;
    bool flipflag;
    void setc(sp_node *c,int o)
    {
        ch[o]=c;
        c->p=this;
    }
    int lr()
    {
        return this==p->ch[1];
    }
    sp_node(int);
    void passmark()
    {
        if (flipflag)
        {
            sp_node *tmp = ch[0];
            setc(ch[1],0);
            setc(tmp,1);
            ch[0]->flipflag ^= true;
            ch[1]->flipflag ^= true;
            flipflag=false;
        }
    }
    void update()
    {
        size=ch[0]->size+ch[1]->size+1;
    }
    void rotate()
    {
        sp_node *tmp=p;
        int o = lr();
        tmp->p->setc(this,tmp->lr());
        tmp->setc(ch[!o],o);
        setc(tmp,!o);
        tmp->update();
    }
    sp_node *splay(sp_node *root)
    {
        while (p != root)
        {
            if (p->p != root)
                if (lr() == p->lr()) p->rotate();
                else rotate();
            rotate();
        }
        update();
        return this;
    }
    void insert(int);
    void build()
    {
        insert(-1);
        insert(n+1);
    }
    sp_node *find_inorder(int o)
    {
        passmark();
        if (ch[0]->size == o) return this;
        if (ch[0]->size > o) return ch[0]->find_inorder(o);
        return ch[1]->find_inorder(o-1-ch[0]->size);
    }
    sp_node *target(int l, int r)
    {
        l--,r++;
        sp_node *pl = this->ch[1]->find_inorder(l)->splay(this);
        sp_node *pr = this->ch[1]->find_inorder(r)->splay(pl);
        return pr->ch[0];
    }
    sp_node *divide(int,int);
    void insert(sp_node *root,int posi)
    {
        this->ch[1]->find_inorder(posi)->splay(this);
        this->ch[1]->find_inorder(posi+1)->splay(this->ch[1]);
        this->ch[1]->ch[1]->setc(root,0);
        root->p->update();
        this->ch[1]->update();
    }
    void flip()
    {
        flipflag ^= true;
    }
    void inorder();
};

sp_node *nil;

sp_node::sp_node(int _value=0):value(_value)
{
    ch[0] = ch[1] = p = nil;
    size = 1;
    flipflag=false;
}
void sp_node::insert(int v)
{
    sp_node *now = this;
    while (now->ch[v > now->value] != nil)
    {
        now = now->ch[v > now->value];
        now->passmark();
    }
    sp_node *tmp = new sp_node(v);
    now->setc(tmp,v > now->value);
    tmp->splay(this);
}
sp_node *sp_node::divide(int l, int r)
{
    sp_node *tmp = target(l,r);
    sp_node *fa = tmp->p;
    fa->ch[tmp->lr()] = nil;
    tmp->p = nil;
    fa->update();
    fa->p->update();
    return tmp;
}
void sp_node::inorder()
{
    if (this == nil) return;
    passmark();
    ch[0]->inorder();
    printf("%d%c",value,++printnum == n?'\n':' ');
    ch[1]->inorder();
}

void sp_init_nil()
{
    nil = new sp_node;
    nil->p = nil->ch[0] = nil->ch[1] = nil;
    nil->size = 0;
}

int main()
{
    //freopen("1.in","r",stdin);
    sp_init_nil();
    while (cin >> n >> m , n>-1)
    {
        sp_node *root = new sp_node(-2);
        root->build();
        For(i,1,n)
            root->insert(i);
        printnum=0;
        Rep(_i,m)
        {
            char s[10];
            int l,r,p;
            scanf("%s",s);
            if (s[0]=='C')
            {
                scanf("%d%d%d",&l,&r,&p);
                root->insert(root->divide(l,r),p);
            }
            else
            {
                scanf("%d%d",&l,&r);
                root->target(l,r)->flip();
            }
        }
        printnum=0;
        root->target(1,n)->inorder();
    }
    return 0;
}
