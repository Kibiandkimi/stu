//
// Created by kibi on 22-8-24.
//
//40pts
#include <bits/stdc++.h>
using namespace std;
int n, m, k, f;
int s_b, s_g;
int mn = 1e9;
bool vis[505];
bool vis2[505];
vector<int> g[505];

void dfs(int u){
    vis[u] = true;
    if(u > n){
        s_b++;
    }else{
        ++s_g;
    }
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(!vis[g[u][i]]){
            dfs(g[u][i]);
        }
    }
}

void f2(int u){
    vis2[u] = true;
    if(u > n){
        s_b++;
        return;
    }else{
        ++s_g;
    }
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(!vis2[g[u][i]] || g[u][i] > u){
            f2(g[u][i]);
        }
    }
}

int main(){
    scanf("%d %d %d %d", &n, &m, &k, &f);
    for(int i = 1; i <= m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back(n+b);
        g[n+b].push_back(a);
    }
    for(int i = 1; i <= f; i++){
        int c, d;
        scanf("%d %d", &c, &d);
        g[c].push_back(d);
        g[d].push_back(c);
    }
    for(int i = 1; i <= n; i++){
        if(!vis2[i]){
            s_b = 0, s_g = 0;
            if(!vis[i]) {
                dfs(i);
            }
            if(s_g > s_b){
                printf("%d", min(k, n));
                return 0;
            }else{
                s_b = 0, s_g = 0;
//                memset(vis2, 0, sizeof vis2);
                f2(i);
                mn = min(s_b, mn);
            }
        }
    }
    printf("%d", min(n, mn+k));
}
