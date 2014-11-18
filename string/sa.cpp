
const int mSa=100000+100;
int rank[mSa*2],tmp[mSa],sa[mSa],tax[mSa],het[mSa];
char s[mSa];
int b[129];
int len;
void sorts(int o)
{
    For(i,0,len)
        tax[i]=0;
    For(i,1,len)
        tax[rank[sa[i]+o]]++;
    For(i,1,len)
        tax[i]+=tax[i-1];
    for (int i=len;i>0;i--)
    {
        tmp[tax[rank[sa[i]+o]]]=sa[i];
        tax[rank[sa[i]+o]]--;
    }
    For(i,1,len)
        sa[i]=tmp[i];
}

int main()
{
    char ch=getchar();
    while (!isalpha(ch))
        ch=getchar();
    len=0;
    while (isalpha(ch))
    {
        s[++len]=ch;
        ch=getchar();
    }
    For(i,0,len*2)//!!!!!!!!!!
        rank[i]=0;
    s[len+1]='#';//!!!!!!!!!!
    memset(b,0,sizeof(b));
    For(i,1,len)
        b[s[i]]=1;
    For(i,'a'+1,'z')
        b[i]+=b[i-1];
    For(i,1,len)
        rank[i]=b[s[i]];
    For(i,1,len)
        sa[i]=i;
    for (int z=1;z<len;z*=2)
    {
        sorts(z);
        sorts(0);
        For(i,1,len)
        {
            tmp[sa[i]]=tmp[sa[i-1]];
            if (rank[sa[i]]!=rank[sa[i-1]] || rank[sa[i]+z]!=rank[sa[i-1]+z])
                tmp[sa[i]]++;
        }
        For(i,1,len)
            rank[i]=tmp[i];
    }
    het[len]=0;//!!!!!!!!!!
    For(i,1,len)
        if (rank[i]!=len)//!!!!!!!!!!
        {
            int z=max(0,het[rank[i-1]]-1);
            int next=sa[rank[i]+1];
            while (s[i+z]==s[next+z])
                z++;
            het[rank[i]]=z;
        }
    return 0;
}
