/*
【题目大意】
	给定一组数(n<=100000)，有m(m<=100000)个操作：
	1.ADD.给区间[l,r]的数都加上d；
	2.REVERSE.翻转一个区间[l,r]；
	3.REVOLVE.把一个区间[l,r]转动k次（每转动一次最右边的数来到最左边）；
	4.INSERT.在某个位置x后插入一个数；
	5.DELETE.删除某个位置x上的数；
	6.MIN.求区间[l,r]的最小值。

【分析】
	这题中涉及的操作十分强大，线段树只能完成操作1和6，Treap只能完成操作4和5，只有伸展树splay能解决所有问题。
	由于这题是模板题，除编写外就没有什么好注意的了。于是我们来看程序和注释（该程序经缩行后在poj中是最短的，其中的伸展树模板比较简洁，大家可以学习一下）：
*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int size=500000;
const int oo=1<<30;
struct Tree
{
    int fa,ch[2],dir,data,size,min,mark;
    bool rev;//子树是否被翻转。
} node[size];
int n,m,tot,i,l,r,x,d,k,tp,w,nt;
char str[10];

void link(int fa,int u,int dir)//把节点fa的dir儿子设为u。
{
    node[fa].ch[dir]=u;
    node[u].fa=fa;    
    node[u].dir=dir;
}

void down(int u)
{
    if (node[u].rev) //如果该子树需要翻转。
    {
        swap(node[u].ch[0],node[u].ch[1]);  //交换左右儿子（下两句也是必须的）。
        link(u,node[u].ch[0],0);
        link(u,node[u].ch[1],1);
        node[u].rev=false;
        if (node[u].ch[0]!=0) node[node[u].ch[0]].rev^=true;
        if (node[u].ch[1]!=0) node[node[u].ch[1]].rev^=true;
    }    
    if (node[u].mark!=0)   //如果该子树都被加上的一个数。
    {
        node[u].data+=node[u].mark;
        node[u].min+=node[u].mark;   //该子树的最小值也加上这个数。
        if (node[u].ch[0]!=0) node[node[u].ch[0]].mark+=node[u].mark;
        if (node[u].ch[1]!=0) node[node[u].ch[1]].mark+=node[u].mark;
        node[u].mark=0;
    }
}

void updata(int u) //维护u的信息。
{
    if (node[u].ch[0]!=0) down(node[u].ch[0]);
    if (node[u].ch[1]!=0) down(node[u].ch[1]);
    node[u].size=node[node[u].ch[0]].size+node[node[u].ch[1]].size+1;
    node[u].min=min(node[u].data,min(node[node[u].ch[0]].min,node[node[u].ch[1]].min));
}

void rotate(int u) //旋转操作，把节点u往上旋转。
{
    int fa=node[u].fa;    
    down(fa); 
    down(u);
    int dir=node[u].dir;
    link(node[fa].fa,u,node[fa].dir);
    link(fa,node[u].ch[!dir],dir);
    link(u,fa,!dir);
    updata(fa);
}

void splay(int u,int gfa) //伸展节点u使其父亲为gfa（想使u为根时gfa=0）。
{
    down(u); 
    while (node[u].fa!=gfa)
    {
        int fa=node[u].fa;
        if ((node[fa].fa)!=gfa) //判断旋转方式。
        {
            if (node[u].dir==node[fa].dir) rotate(fa);
                else rotate(u);   
        }
        rotate(u);
    }
    updata(u);
}

int rank(int u,int k) //寻找以u为根的树中第k个位置的节点。
{
    while (1)
    {
        down(u);    //记得要传递标记，因为它可能使左右儿子互换。
        int tmp=node[node[u].ch[0]].size+1;
        if (k==tmp) break;
        if (k<tmp) u=node[u].ch[0];
        else 
        {
            k-=tmp;    
            u=node[u].ch[1];
        }
    }    
    return u;
}

int draw(int l,int r) //把区间(l,r)的元素集中在一棵子树上（注意是开区间）：
{
    splay(1,0);    
    int root=rank(1,l),u=rank(1,r);
    splay(root,0); 
    splay(u,root);
    return u;
}

int main()
{
    tot=2;//虚拟出两个节点，点1一定在第一个位值，点2一定在第二个位置。如果我们需要用draw操作集中区间[l,r]，就要用到点l-1和点r+1。虚构出点1点2使得l=1或r=n时draw操作无需特判。
    node[1].size=1; node[2].size=1;
    node[0].min=oo; node[1].min=oo; node[2].min=oo;
    node[0].data=oo; node[1].data=oo; node[2].data=oo; 
    scanf("%d",&n);
    for (i=1;i<=n;i++) //读入时把它们从左上到右下连起来，最后splay一下叶子以维护信息。
    {
        node[++tot].size=1;
        scanf("%d",&node[tot].data);    
        if (i==1) link(1,tot,1);
        else link(tot-1,tot,1);   
    }
    link(tot,2,1);
    splay(2,0);
    
    scanf("%d",&m);
    while (m--)
    {
        scanf("%s",str);    
        if (str[0]=='A')
        {
            scanf("%d%d%d",&l,&r,&d);    
            tp=node[draw(l,r+2)].ch[0]; //提取出区间[l,r]。由于点1的存在于最左边，使得该区间应右移一位变成[l+1,r+1]=(l,r+2)，下同不解释
            node[tp].mark+=d;
            splay(tp,0);//把信息改变过的点伸展一下一维护整棵树的信息。下同不解释。
        } else
        if (str[0]=='R'&&str[3]=='E')
        {
            scanf("%d%d",&l,&r);    
            tp=node[draw(l,r+2)].ch[0];
            node[tp].rev^=true;
            splay(tp,0);
        } else 
        if (str[0]=='R'&&str[3]=='O')
        {
            scanf("%d%d%d",&l,&r,&k);
            w=r-l+1;
            k=(k%w+w)%w;    
            if (k==0) continue;
            tp=draw(r-k+1,r+2),nt=node[tp].ch[0];
            link(tp,0,0);
            splay(tp,0);
            tp=draw(l,l+1);
            link(tp,nt,0);
            splay(nt,0);
        } else
        if (str[0]=='I') 
        {
            node[++tot].size=1;
            scanf("%d%d",&x,&node[tot].data);
            tp=draw(x+1,x+2);//此时根是该数字前的节点，u是它后面的节点。
            link(tp,tot,0);
            splay(tot,0);   
        } else 
        if (str[0]=='D')
        {
            scanf("%d",&x);    
            tp=draw(x,x+2);
            link(tp,0,0);
            splay(tp,0);
        } else
        if (str[0]=='M')
        {
            scanf("%d%d",&l,&r);    
            tp=node[draw(l,r+2)].ch[0];
            printf("%d\n",node[tp].min);
        }
    }
    cin>>n;
    return 0;
}
