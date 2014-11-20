void manacher(char *s,int len)
{
    s[0]='#';s[len+1]='&';
    mnl[1]=0;
    int ml=1,mi=1;
    For(i,2,len)
    {
        int j=0;
        if (i<=ml)
        {
            int dc=mi*2-i;
            if (mnl[dc]==ml-i)
                j=ml-i;
            else
            {
                mnl[i]=min(mnl[dc],ml-i);
                continue;
            }
        }
        while (s[i+j+1]==s[i-j-1])
            j++;
        mnl[i]=j;
        ml=i+j;
        mi=i;
    }
}
int main()
{
    while (scanf("%s",ss)!=-1)
    {
        int n=strlen(ss);
        For(i,1,n*2+1)
        {
            if (i%2==1)
                s[i]='*';
            else s[i]=ss[i/2-1];
           // cout<<s[i]<<endl;
        }
        manacher(s,n*2+1);
        int ans=0;
        For(i,1,n*2+1)
            if (mnl[i]>ans)
                    ans=mnl[i];
        printf("%d\n",ans);
    }
}
