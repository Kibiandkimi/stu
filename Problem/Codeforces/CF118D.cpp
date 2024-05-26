//
// Created by kibi on 2021/9/5.
//
#include <bits/stdc++.h>
using namespace std;
long long n1,n2,k1,k2,sn,mo = 100000000;
long long d[3005][3005][2]={};
int main(){
    scanf("%lld %lld %lld %lld", &n1, &n2, &k1, &k2);
    sn = n1+n2;
    d[0][0][1] = 1;
    d[0][0][0] = 1;
    for(long long i = 1; i <= sn; i++){
        for(long long j = 0; j <= i; j++){
            for(long long k = 1; k<=k2&&i-k>=j;k++){
                d[i][j][1] = (d[i][j][1]+d[i-k][j][0])%mo;
            }
            long long t = min(k1, i);
            for(long long k = 1; k <= min(k1, max(i,j)); k++){
                d[i][j][0] = (d[i][j][0]+d[i-k][j-k][1])%mo;
            }
        }
    }
    long long t = d[sn][n1][0]%mo+d[sn][n1][1]%mo;
    printf("%lld", t%mo);
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
int n,m,k1,k2;
long long f[3000][3000][2];//前tot个兵，有first个步兵(tot-first个骑兵)最后一个是步兵0、骑兵1；
int main()
{
    scanf("%d%d%d%d", &n, &m, &k1, &k2);
    memset(f,0,sizeof(f));
    f[0][0][1] = 1;
    f[0][0][0] = 1;
    for (int i=1;i<=n+m;i++)
        for (int j=0;j<=i;j++)
        {
            for(int k=1;k<=k2&&i-k>=j;k++)//往后插入骑兵1
            {
                f[i][j][1]=(f[i][j][1]+f[i-k][j][0])%100000000;
            }
            for(int k=1;k<=min(k1,max(i,j));k++)//往后插入步兵0
            {
                f[i][j][0]=(f[i][j][0]+f[i-k][j-k][1])%100000000;
            }
        }
    long long sum=f[n+m][n][0]%100000000+f[n+m][n][1]%100000000;
    cout<<sum%100000000;
}
#include <bits/stdc++.h>
using namespace std;
int n,m,k1,k2,mo = 1e8;
long long d[205][205][2];
int main(){
    cin >> n >> m >> k1 >> k2;
    d[0][0][0] = d[0][0][1] = 1;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            int t = min(i, k1);
            for(int k = 1; k <= t; k++){
                d[i][j][0] = (d[i][j][0] + d[i-k][j][1])%mo;
            }
            t = min(j, k2);
            for(int k = 1; k <= t; k++){
                d[i][j][1] = (d[i][j][1] + d[i][j-k][0])%mo;
            }
        }
    }
    cout << (long long)(d[n][m][0] + d[n][m][1])%mo;
    return 0;
}