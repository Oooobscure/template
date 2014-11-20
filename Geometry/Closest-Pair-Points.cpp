// sort x before Find
struct Node
{
    long long x,y;
} p[size];
int i,n,tp,a[size];
long long ans;

bool cp(int u,int v)
{
    return p[u].y<p[v].y;
}

long long dis(Node u,Node v)
{
    return 1LL*(u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y);// sqr dis
}
long long Find(int l,int r)
{
     if(r==l+1) return dis(p[l],p[r]);
     if(l+2==r) return min(dis(p[l],p[r]),min(dis(p[l],p[l+1]),dis(p[l+1],p[r])));
     int mid,i,j,tot;
     mid=(l+r)>>1; tot=0;
     long long tp=min(Find(l,mid),Find(mid+1,r));
     for(i=l;i<=r;i++)
        if(((p[i].x-p[mid].x)*(p[i].x-p[mid].x)<=tp)) a[++tot]=i; // sqr dis
     sort(a+1,a+tot+1,cp);
     for(i=1;i<=tot;i++)
     for(j=i+1;j<=tot;j++)
     {
         if((p[a[j]].y-p[a[i]].y)*(p[a[j]].y-p[a[i]].y)>=tp) break; //sqr dis
         tp=min(tp,dis(p[a[i]],p[a[j]]));
     }
     return tp;
}
