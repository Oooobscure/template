//高斯消元
//输入M[1..tot][1..tot+1]，M[i][tot+1]为解
void normal_Gauss()
{
    int row=1;
    For(col,1,tot)
    {
        int i;
        for (i=row;i<=tot;i++) if (fabs(M[i][col])>eps) break;
        //if (i>tot) continue;
        For (j,col,tot+1) swap(M[i][j],M[row][j]);
        for (int j=tot+1;j>=col;j--) M[row][j]/=M[row][col];
        For (i,1,tot)
        if (i!=row)
            if(fabs(M[row][col])>eps)
            for (int j=tot+1;j>=col;j--) M[i][j]-=M[i][col]*M[row][j];

        row++;
    }
}


void hasEmptyLine_Gauss()
{
    For(i,1,tot)
    {
        int k;
        for (k=i;k<=tot;k++) if (fabs(M[k][i])>eps) break;
        For(j,i,tot+1) swap(M[i][j],M[k][j]);
        for (int j=tot+1;j>=i;j--) M[i][j]/=M[i][i];
        For(k,1,tot)
        if (k!=i)
        if (fabs(M[k][i])>eps)
            for (int j=tot+1;j>=i;j--) M[k][j]-=M[k][i]*M[i][j];
    }
}
