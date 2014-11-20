//Dance link 精确覆盖 似乎能跑出1000*100的数据
void add_link(int i,int j)
{
    tot++;
    if (Head[i]==0) Head[i]=L[tot]=R[tot]=tot;
    else
    {
        L[tot]=L[Head[i]]; R[tot]=Head[i];
        R[L[Head[i]]]=tot; L[Head[i]]=tot;
    }
    U[tot]=U[j]; D[tot]=j;
    D[U[j]]=tot; U[j]=tot;
    Col[tot]=j; Sum[j]++;
}

void remove(int u)
{
    R[L[u]]=R[u]; L[R[u]]=L[u];
    for (int i=D[u];i!=u;i=D[i])
    {
        for (int j=R[i];j!=i;j=R[j])
        {
            D[U[j]]=D[j]; U[D[j]]=U[j];
            Sum[Col[j]]--;
        }
    }
}

void resume(int u)
{
    L[R[u]]=u; R[L[u]]=u;
    for (int i=U[u];i!=u;i=U[i])
    {
        for (int j=L[i];j!=i;j=L[j])
        {
            D[U[j]]=j; U[D[j]]=j;
            Sum[Col[j]]++;
        }
    }
}

bool dance()
{
    if (R[0]==0) return true;
    int k=0;
    for (int j=R[0];j!=0;j=R[j]) if (Sum[j]<Sum[k]) k=j;
    remove(k);
    for (int i=D[k];i!=k;i=D[i])
    {
        for (int j=R[i];j!=i;j=R[j]) remove(Col[j]);
        if (dance()) return true;
        for (int j=L[i];j!=i;j=L[j]) resume(Col[j]);
    }
    resume(k);
    return false;
}

int main()
{
    while (scanf("%d%d",&n,&m)==2)
    {
        For(j,0,m)
        {
            L[j]=j-1; R[j]=j+1;
            U[j]=j; D[j]=j;
        }
        R[m]=0; L[0]=m;
        tot=m;
        memset(Head,0,sizeof(Head));
        memset(Sum,0,sizeof(Sum));
        Sum[0]=n+1;
        For(i,1,n) For(j,1,m)
        {
            scanf("%d",&xx);
            if (xx) add_link(i,j);
        }
        printf(dance()?"Yes, I found it\n":"It is impossible\n");
    }
    return 0;
}

//Dance Link 重复覆盖
//A*，h是估价函数
void add_link(int i,int j)
{
    tot++;
    if (Head[i]==0) Head[i]=L[tot]=R[tot]=tot;
    else
    {
        L[tot]=L[Head[i]]; R[tot]=Head[i];
        R[L[Head[i]]]=tot; L[Head[i]]=tot;
    }
    U[tot]=U[j]; D[tot]=j;
    D[U[j]]=tot; U[j]=tot;
    Col[tot]=j; Sum[j]++;
}

void remove(int u)
{
    for (int i=D[u];i!=u;i=D[i])
    {
        L[R[i]]=L[i]; R[L[i]]=R[i];
        Sum[Col[i]]--;
    }
}

void resume(int u)
{
    for (int i=U[u];i!=u;i=U[i])
    {
        L[R[i]]=i; R[L[i]]=i;
        Sum[Col[i]]++;
    }
}

int h()
{
    int tp=0;
    for (int k=R[0];k!=0;k=R[k]) flag[k]=false;
    for (int k=R[0];k!=0;k=R[k]) if (!flag[k])
    {
        tp++;
        for (int i=D[k];i!=k;i=D[i])
        for (int j=R[i];j!=i;j=R[j]) flag[Col[j]]=true;
    }
    return tp;
}

bool dance(int u)
{
    if (R[0]==0) return true;
    if (u+h()>t) return false;
    int k=0;
    for (int j=R[0];j!=0;j=R[j]) if (Sum[j]<Sum[k]) k=j;
    for (int i=D[k];i!=k;i=D[i])
    {
        remove(i);
        for (int j=R[i];j!=i;j=R[j]) remove(j);
        if (dance(u+1)) return true;
        for (int j=L[i];j!=i;j=L[j]) resume(j);
        resume(i);
    }
    return false;
}

bool ok()
{
    For(j,0,n)
    {
        L[j]=j-1; R[j]=j+1;
        U[j]=j; D[j]=j;
    }
    R[n]=0; L[0]=n;
    tot=n;
    memset(Head,0,sizeof(Head));
    memset(Sum,0,sizeof(Sum));
    Sum[0]=n+1;
    For(i,1,n) For(j,1,n) if (dis(p[i],p[j])<=mid) add_link(i,j);
    if (dance(0)) return true;
    return false;
}
