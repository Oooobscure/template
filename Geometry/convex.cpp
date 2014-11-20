// input vector (P), output convex hull (conv)
void find_convex(vector<Point> &P)
{
    sort(P.begin(),P.end());
    int n=P.size();
    conv.clear();
    Rep(i,n)
    {
        while (conv.size()>1&&(conv[conv.size()-1]-conv[conv.size()-2])*(P[i]-conv[conv.size()-1])<=0)
            conv.pop_back();
        conv.push_back(P[i]);
    }
    for (int i=n-2,tp=conv.size();i>=0;i--)
    {
        while (conv.size()>tp&&(conv[conv.size()-1]-conv[conv.size()-2])*(P[i]-conv[conv.size()-1])<=0)
            conv.pop_back();
        conv.push_back(P[i]);
    }
}
