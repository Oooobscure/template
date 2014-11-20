struct Cir
{
    double x,y,r;
    Cir(double xx=0,double yy=0,double rr=0)
    {
        x=xx; y=yy; r=rr;
    }
} C[5];
vector<Cir> cir;

struct Ang
{
    double l,r;
}ang[100];
bool cover[10];

bool operator <(Ang u,Ang v)
{
    return u.r<v.r;
}

double Dis(double X1,double X2,double Y1,double Y2)
{
    return sqrt(sqr(X1-X2)+sqr(Y1-Y2));
}

double circle_union(const vector<Cir> &cir)
{
    double res=0;
    int n=cir.size();
    memset(cover,false,sizeof(cover));
    Rep(i,n)
    {
        int tot=0;
        Rep(j,n)
        if (i!=j&&!cover[j])
        {
            double dis=Dis(cir[i].x,cir[j].x,cir[i].y,cir[j].y);
            if (dis+cir[i].r<cir[j].r+eps) cover[i]=true; else
            if (dis+cir[j].r<cir[i].r+eps) continue; else
            if (dis<cir[i].r+cir[j].r-eps)
            {
                tot++;
                double mid=atan2(cir[j].y-cir[i].y,cir[j].x-cir[i].x);
                double dx=(sqr(cir[i].r)-sqr(cir[j].r)+sqr(dis))/2.0/dis;
                double dy=sqrt(sqr(cir[i].r)-dx*dx);
                ang[tot].l=mid+atan2(dy,dx);
                ang[tot].r=mid-atan2(dy,dx);
                if (ang[tot].r<0)
                {
                    ang[tot].r+=2*pi; ang[tot].l+=2*pi;
                }
            }
        }
        if (tot==0&&!cover[i]) res+=sqr(cir[i].r)*pi;
        if (tot==0||cover[i]) continue;
        sort(ang+1,ang+tot+1);
        int tt=0,ss=1;
        For(j,1,tot)
        {
            if ((tt==0)||(ang[j].r>ang[tt].l+eps))
            {
                tt++; ang[tt].l=ang[j].l; ang[tt].r=ang[j].r;
            } else
            if (ang[tt].l<ang[j].l) ang[tt].l=ang[j].l;
        }

        while ((ss<=tt)&&(ang[tt].l-2*pi>ang[ss].r-eps))
        {
            if (ang[tt].l-2*pi<ang[ss].l) ang[tt].l=ang[ss].l+2*pi;
            ss++;
        }

        For(j,ss,tt)
        {
            int k;
            if (j!=tt) k=j+1; else
            {
                k=ss;
                while (ang[k].r<ang[j].l-eps) ang[k].r+=2*pi;
            }
            double dx=ang[k].r-ang[j].l;
            if (dx<0) dx+=2*pi;
            res+=sqr(cir[i].r)/2*(dx-sin(dx));
            double X1,X2,Y1,Y2;
            X1=cir[i].x+cir[i].r*cos(ang[j].l);
            Y1=cir[i].y+cir[i].r*sin(ang[j].l);
            X2=cir[i].x+cir[i].r*cos(ang[k].r);
            Y2=cir[i].y+cir[i].r*sin(ang[k].r);
            res+=(X1*Y2-X2*Y1)/2;
        }
    }
    return res;
}
