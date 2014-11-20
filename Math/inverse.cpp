int x,y,xx,yy;
void gcd(int u,int v)
{
    if (u%v==0)
    {
        x=0; y=1; return;
    }
    gcd(v,u%v);
    xx=y; yy=x-1LL*u/v*y;
    x=xx; y=yy;
}

int inv(int u)
{
    if (u%mo==0) return 0;
    gcd(u,mo);
    while (x<0) x+=mo;
    return x;
}
