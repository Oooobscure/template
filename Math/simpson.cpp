double f(double u)
{
    //return 2*sqrt(sqr(b)-sqr(b)*sqr(u)/sqr(a));
}

double F(double l,double r)
{
    if (fabs(r-l)<eps) return 0;
    return (f(l)+f(r)+3*f(l+(r-l)*1/3)+3*f(l+(r-l)*2/3))*(r-l)/8;
    //or F=(f(l)+f(r)+4*f((l+r)/2))*(r-l)/6;
}

double simpson(double l,double r)
{
    double simp=F(l,r),mid=(l+r)/2;
    if (fabs(F(l,mid)+F(mid,r)-simp)<eps) return simp;
    return simpson(l,mid)+simpson(mid,r);
}
