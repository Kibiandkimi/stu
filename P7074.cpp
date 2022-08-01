//
// Created by kibi on 2021/8/15.
//
#include <bits/stdc++.h>
using namespace std;
long long n,m,a[2005][2005],f[3][2005][2005];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%lld", &a[i][j]);
        }
    }
    for(int i = 0; i <= n+1; i++){
        for(int j = 0; j <= m+1; j++){
            f[0][i][j] = f[1][i][j] = f[2][i][j] = -1e9;
        }
    }
    f[0][1][1] = f[1][1][1] = f[2][1][1] = a[1][1];
    for(int i = 2; i <= n; i++){
        f[0][i][1] = f[0][i-1][1] + a[i][1];
    }
    for(int i = 2; i <= m; i++){
        for(int j = 1; j <= n; j++){
            f[0][j][i] = max(f[0][j-1][i], f[1][j-1][i])+a[j][i];
            f[1][j][i] = max(max(f[0][j][i-1], f[1][j][i-1]), f[2][j][i-1]) + a[j][i];
        }
        for(int j = n; j >= 1; j--){
            f[2][j][i] = max(f[1][j+1][i], f[2][j+1][i]) + a[j][i];
        }
    }
    printf("%lld", max(f[0][n][m], f[1][n][m]));
}