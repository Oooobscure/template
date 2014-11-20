gets(s1); gets(s2);
l1=strlen(s1);
l2=strlen(s2);

pre[0]=-1;
j=-1;
for (i=1;i<l2;i++)
{
    while (j>=0&&s2[i]!=s2[j+1]) j=pre[j]; 
    if (s2[i]==s2[j+1]) j++;
    pre[i]=j;
}

j=-1;
for (i=0;i<l1;i++)
{
    while (j>=0&&s1[i]!=s2[j+1]) j=pre[j];    
    if (s1[i]==s2[j+1]) j++;
    if (j==l2-1)
    {
           cout<<i-j<<endl; 
           j=pre[j];   
           break;
    }
}
