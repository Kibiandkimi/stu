//
// Created by kibi on 2021/10/3.
//
//^
#include <bits/stdc++.h>
using namespace std;
int T,n,m,lines[25][25],st[1<<19],dp[1<<19];
double eps = 1e-8,x[25],y[25];
void eq(double &a, double &b, int i, int j){
    a= -(y[i]*x[j]-y[j]*x[i])/(x[j]*x[j]*x[i]-x[i]*x[i]*x[j]);
    b= (y[i]*x[j]*x[j]-y[j]*x[i]*x[i])/(x[i]*x[j]*x[j]-x[j]*x[i]*x[i]);
}
int main(){
    scanf("%d", &T);
    for(int i = 0; i < (1<<18); i++){
        int j = 1;
        for(;j<=18&&i&1<<(j-1);j++);
        st[i]=j;
    }
    while(T--){
        memset(lines, 0, sizeof(lines));
        memset(dp, 1, sizeof(dp));
        dp[0] = 0;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++){
            scanf("%lf %lf", &x[i], &y[i]);
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(fabs(x[i]-x[j])<eps){
                    continue;
                }
                double a,b;
                eq(a,b,i,j);
                if(a>-eps){
                    continue;
                }
                for(int k = 1; k <= n; k++){
                    if(fabs(a*x[k]*x[k]+b*x[k]-y[k])<eps){
                        lines[i][j]|=(1<<(k-1));
                    }
                }
            }
        }
        for(int i = 0; i < (1<<n); i++){
            int j = st[i];
            dp[i|1<<(j-1)] = min(dp[i|1<<(j-1)],dp[i]+1);
            for(int k = 1; k <= n; k++){
                dp[i|lines[j][k]] = min(dp[i|lines[j][k]],dp[i]+1);
            }
        }
        printf("%d\n", dp[(1<<n)-1]);
    }
}