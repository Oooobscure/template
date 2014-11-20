void build_dfa()
{
    memset(trie,0,sizeof(trie));
    memset(fail,0,sizeof(fail));
    int tt=1;
    Rep(i,n)
    if (w[i]>0)
    {
        int p=1;
        Rep(j,strlen(s[i]))
        {
            if (trie[p][s[i][j]-'a']==0) trie[p][s[i][j]-'a']=++tt;
            p=trie[p][s[i][j]-'a'];
        }
    }
 
    Rep(i,size) edge[i].clear();
    Rep(i,26) trie[0][i]=1; fail[1]=0;
    D.push(1);
    while (!D.empty())
    {
        int tp=D.front(); D.pop();
        Rep(i,26) if (trie[tp][i])
        {
            int now=trie[tp][i];
            int p=fail[tp];
            while (trie[p][i]==0) p=fail[p];
            fail[now]=trie[p][i];
            edge[fail[now]].push_back(now);
            D.push(now);
        }
    }
}
