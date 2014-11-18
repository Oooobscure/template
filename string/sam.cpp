//the longest common substring
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
                curn->p=tp;
            else
            {
                node *r=top++;
                r[0]=tp[0];
                r->l=p->l+1;
                //r->p=tp->p;
                tp->p=r;
                curn->p=r;
                for(;p && p->trs[x]==tp;p=p->p)
                    p->trs[x]=r;
            }
        }
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
                p=p->p;
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
