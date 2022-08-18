//
// Created by kibi on 2022/8/18.
//
//我咋没看出状压
#include <bits/stdc++.h>
using namespace std;
int n, m, tot, ans, res;
int a[25];
bool f[2210], vis[2210];

void d(){
    memset(f, 0, sizeof f);
    f[0] = true;
    ans = 0, tot = 0;
    for(int i = 1; i <= n; i++){
        if(vis[i]){
            continue;
        }
        for(int j = tot; j >= 0; j--){
            if(f[j]&&!f[j+a[i]]){
                f[j+a[i]] = true;
                ans++;
            }
        }
        tot += a[i];
    }
    res = max(res, ans);
}

void dfs(int u, int now){
    if(now > m){
        return ;
    }
    if(u == n){
        if(now == m){
            d();
        }
        return ;
    }
    dfs(u+1, now);
    vis[u] = true;
    dfs(u+1, now+1);
    vis[u] = false;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    dfs(1, 0);
    printf("%d", res);
}