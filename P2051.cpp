//
// Created by kibi on 2022/9/25.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main(){
    const long long mod = 9999973;
    int n, m;
    read(n), read(m);
    long long d[105][105][105] = {1};
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= m; j++){
            for(int k = 0; k <= m-j; k++){
                d[i][j][k] = d[i-1][j][k];
                if(k >= 1){
                    d[i][j][k] = (d[i][j][k] + d[i - 1][j + 1][k - 1] * (j + 1)) % mod;
                    d[i][j][k] = (d[i][j][k] + d[i - 1][j][k - 1] * j * (m - j - k + 1)) % mod;
                }
                if(k >= 2){
                    d[i][j][k] = (d[i][j][k] + d[i - 1][j + 2][k - 2] * (((j + 2) * (j + 1)) / 2)) % mod;
                }
                if(j >= 1){
                    d[i][j][k] = (d[i][j][k] + d[i - 1][j - 1][k] * (m - j - k + 1)) % mod;
                }
                if(j >= 2){
                    d[i][j][k] = (d[i][j][k] + d[i - 1][j - 2][k] * ((m - j - k + 2) * (m - j - k + 1)) / 2) % mod;
                    //                    d[i][j][k] = (d[i][j][k] + d[i - 1][j - 2][k] * ((((m - j - k + 2) * (m - j - k + 2 - 1)) / 2) % 9999973)) % mod;
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= m; j++){
            ans = (ans + d[n][i][j]) % mod;
        }
    }
    printf("%lld", (ans + mod) % mod);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}