//
// Created by kibi on 2022/5/28.
//
//91pts
#include <bits/stdc++.h>
using namespace std;
long long n, p[25][25];
long long mx[25], ans;
bool vis[25];
void f(long long t, long long x){
    if(t > n){
        ans = max(ans, x);
        return;
    }
    long long s = 0;
    for(int i = t; i <= n; i++){
        s += mx[i];
    }
    if(x + s <= ans){
        return;
    }
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            vis[i] = true;
            f(t+1, x+p[t][i]);
            vis[i] = false;
        }
    }
}
int main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%lld", &p[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int t;
            scanf("%lld", &t);
            p[j][i] *= t;
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            mx[i] = max(mx[i], p[i][j]);
        }
    }

    f(1, 0);
    printf("%lld", ans);
    return 0;
}