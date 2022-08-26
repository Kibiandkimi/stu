//
// Created by kibi on 22-8-22.
//
#include <bits/stdc++.h>
using namespace std;
int n, k;
int num[2005], s[2005];
int cnt;
long long d[15][2005][1005];

void f(int h, int sum, int node){
    if(node >= n){
        num[++cnt] = h;
        s[cnt] = sum;
        return ;
    }
    f(h, sum, node+1);
    f(h+(1<<node), sum+1, node+2);
}

int main(){
    scanf("%d %d", &n, &k);
    f(0, 0, 0);
    for(int i = 1; i <= cnt; i++){
        d[1][i][s[i]] = 1;
    }
    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= cnt; j++){
            for(int l = 1; l <= cnt; l++){
                if((num[j]&num[l])||((num[j]<<1)&num[l])||((num[l]<<1)&num[j])){
                    continue;
                }
                for(int u = k; u >= s[j]; u--){
                    d[i][j][u] += d[i-1][l][u-s[j]];
                }
            }
        }
    }
    long long ans = 0;
    for(int i = 1; i <= cnt; i++){
        ans += d[n][i][k];
    }
    printf("%lld", ans);
}