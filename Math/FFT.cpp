//FFT
//f(n)=a*f(n-p)+b*(n-q)。求f(n)

typedef vector<int> Pol;
typedef complex<double> Comp;
const int size=(1<<16)+10;
const int mo=119;
const double pi=acos(-1);
Comp A[size],B[size];
int n,a,b,p,q,f[size];
Pol base,pol;

void FFT(Comp* P,int m,int oper)
{
    for (int i=1,j=0;i<m-1;i++)
    {
        for (int s=m;j^= s >>= 1,~j&s;);
        if (i<j) swap(P[i],P[j]);
    }
    for (int d=0;(1<<d)<m;d++)
    {
        int k=1<<d,k2=k*2;
        double p0=pi/k*oper;
        Comp unit_p0(cos(p0),sin(p0));
        for (int i=0;i<m;i+=k2)
        {
            Comp unit=1;
            Rep(j,k)
            {
                Comp &P1=P[i+j+k], &P2=P[i+j];
                Comp t=unit*P1;
                P1=P2-t; P2=P2+t;
                unit=unit*unit_p0;
            }
        }
    }
}

Pol operator *(const Pol &u,const Pol&v)
{
    int m=1;
    while (m<=q+q-2) m*=2;
    Rep(i,m) A[i]=(i<q?u[i]:0);
    Rep(i,m) B[i]=(i<q?v[i]:0);
    FFT(A,m,1); FFT(B,m,1);
    Rep(i,m) A[i]*=B[i];
    FFT(A,m,-1);
    Pol w(q+q-1);
    Rep(i,q+q-1) w[i]=(int)(A[i].real()/m+0.5)%mo;
    for (int i=q+q-2;i>=q;i--)
    {
        w[i-q]=(w[i-q]+b*w[i])%mo;
        w[i-p]=(w[i-p]+a*w[i])%mo;
    }
    while (w.size()>q) w.pop_back();
    return w;
}

void mut(int u)
{
    if (u==0)
    {
        pol[0]=1; return;
    }
    mut(u/2);
    pol=pol*pol;
    if (u%2==1) pol=pol*base;
}

int main()
{
    //freopen("1.in","r",stdin);
    while (scanf("%d%d%d%d%d",&n,&a,&b,&p,&q)==5)
    {
        a%=mo; b%=mo; f[0]=1;
        For(i,1,2*q-2) f[i]=(a*(i-p>0?f[i-p]:1)+b*(i-q>0?f[i-q]:1))%mo;
        if (n<=q-1)
        {
            printf("%d\n",f[n]); continue;
        }
        n-=q-1;
        pol=Pol(q); base=Pol(q);
        base[1]=1;
        mut(n);

        int ans=0;
        For(i,1,q) ans=(ans+pol[q-i]*f[2*q-2-i+1])%mo;
        printf("%d\n",ans);
    }

    return 0;
}
