int lowbit(int u)
{
    return u&(-u);
}

void change(int u,int v)
{
    while (u<=n)
    {
        c[u]+=v;
        u+=lowbit(u);
    }
}

long long sum(int u)
{
    long long tp=0;
    while (u)
    {
        tp+=c[u];
        u-=lowbit(u);
    }
    return tp;
}
