node operator - (node u,node v)
{
node w;
w.x=u.x-v.x; w.y=u.y-v.y;
return w;     
}

double operator * (node u,node v)
{
      return u.x*v.y-u.y*v.x;       
}

bool operator < (Line u,Line v)
{
     if (fabs(u.ang-v.ang)<eps) 
         return (v.ed-u.st)*(u.ed-u.st)<eps; 
     return u.ang<v.ang;
}

void init()
{
scanf("%d",&n);
for (i=0;i<n;i++) scanf("%lf%lf",&p[i].x,&p[i].y);     
p[n]=p[0];
for (i=1;i<=n;i++)
{
    ln[i].st=p[i-1];
    ln[i].ed=p[i];
    ln[i].ang=atan2(ln[i].ed.y-ln[i].st.y,ln[i].ed.x-ln[i].st.x);    
}
}

node cross(Line u,Line v)
{
     node w;
     double s1=(u.ed-u.st)*(v.st-u.st),s2=(v.ed-u.st)*(u.ed-u.st);
     w.x=(v.ed.x*s1+v.st.x*s2)/(s1+s2);
     w.y=(v.ed.y*s1+v.st.y*s2)/(s1+s2);
     return w;
}

bool isout(node u,Line v)
{
     return (u-v.st)*(v.ed-v.st)<eps;
}

bool px(Line u,Line v)
{
     return fabs(u.ang-v.ang)<eps; 
}

void solve()
{
ans=0.0;
sort(ln+1,ln+n+1);

tot=1;
for (i=2;i<=n;i++) 
    if (fabs(ln[i].ang-ln[i-1].ang)>eps) ln[++tot]=ln[i];
n=tot;
tou=0; wei=1;
d[tou]=1; d[wei]=2;
for (i=3;i<=n;i++)
{
    if (px(ln[d[wei]],ln[d[wei-1]])||px(ln[d[tou]],ln[d[tou+1]])) return;
    while (tou<wei&&isout(cross(ln[d[wei]],ln[d[wei-1]]),ln[i])) wei--;
    while (tou<wei&&isout(cross(ln[d[tou]],ln[d[tou+1]]),ln[i])) tou++;    
    d[++wei]=i;
}     

while (tou<wei&&isout(cross(ln[d[wei]],ln[d[wei-1]]),ln[d[tou]])) wei--;
while (tou<wei&&isout(cross(ln[d[tou]],ln[d[tou+1]]),ln[d[wei]])) tou++; 

if (wei<=tou+1) return;

d[++wei]=d[tou];
for (i=tou;i<wei;i++)
    pp[i-tou]=cross(ln[d[i]],ln[d[i+1]]);    
pp[wei-tou]=pp[0];
for (i=0;i<wei-tou;i++) ans+=pp[i]*pp[i+1];
ans/=2;   
}
