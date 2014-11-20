void ST()
{
    Rep(i,n) g[i][0]=a[i];
    For(j,1,S)
    Rep(i,n)
    if (i+(1<<j)-1<n)
        g[i][j]=gcd(g[i][j-1],g[i+(1<<(j-1))][j-1]);
}

int Gcd(int l,int r)
{
    int tp=floor(log2(r-l+1));
    return gcd(g[l][tp],g[r-(1<<tp)+1][tp]);
}
