//
// Created by kibi on 2022/6/12.
//
//P3177
//htr
#include <bits/stdc++.h>
using namespace std;
int n, m;
int sz[2005];
long long d[2005][2005];
struct node{
    int v, w;
};
vector<node> a[2005];

void f(int u, int fa){
    sz[u] = 1;
    d[u][0] = d[u][1] = 0;
    int sa = a[u].size();
    for(int i = 0; i < sa; i++){
        int v = a[u][i].v;
        if(v == fa){
            continue ;
        }
        f(v, u);
        sz[u] += sz[v];
        for(int j = min(m, sz[u]); j >= 0; j--){
            if(d[u][j] != -1){
                d[u][j] += d[v][0] + (long long)sz[v]*(n-m-sz[v])*a[u][i].w;
            }
            for(int k = min(j, sz[v]); k > 0; k--){
                if(d[u][j-k]==-1){
                    continue ;
                }
                d[u][j] = max(d[u][j], d[u][j-k] + d[v][k] + (long long)(k*(m-k)+(sz[v]-k)*(n-m-sz[v]+k))*a[u][i].w);
            }
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    m = n-m<m?n-m:m;
    for(int i = 1; i < n; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back({v, w});
        a[v].push_back({u, w});

    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            d[i][j] = -1;
        }
    }
    f(1, -1);
    printf("%lld", d[1][m]);
}