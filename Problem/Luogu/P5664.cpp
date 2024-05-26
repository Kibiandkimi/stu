//
// Created by kibi on 2022/8/17.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, mod = 998244353;
int a[105][2005], sum[105][2005];
long long f[105][205], g[105][105];

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &a[i][j]);
            sum[i][0] = (sum[i][0] + a[i][j])%mod;
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            sum[i][j] = (sum[i][0] - a[i][j]+mod)%mod;
        }
    }
    long long ans = 0;
    for(int i = 1; i <= m; i++){
        memset(f, 0, sizeof f);
        f[0][n] = 1;
        for(int j = 1; j <= n; j++){
            for(int k = n-j; k <= n+j; k++){
                f[j][k] = (f[j-1][k]+f[j-1][k-1]*a[j][i]%mod+f[j-1][k+1]*sum[j][i]%mod)%mod;
            }
        }
        for(int j = 1; j <= n; j++){
            ans = (ans+f[n][n+j])%mod;
        }
    }
    g[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= n; j++){
            g[i][j] = (g[i-1][j]+(j>0?g[i-1][j-1]*sum[i][0]%mod:0))%mod;
        }
    }
    for(int i = 1; i <= n; i++){
        ans = (ans - g[n][i] + mod) % mod;
    }
    printf("%lld", ans*(mod-1)%mod);

}