//
// Created by kibi on 22-8-23.
//
#include <bits/stdc++.h>
using namespace std;
int n;
long long v[16005], d[16005][2], mx = -1e18;
vector<int> g[16005];

void f(int u, int fa){
    int sg = g[u].size();
    d[u][0] = -1e18;
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue;
        }
        f(g[u][i], u);
        d[u][0] = max(max(d[g[u][i]][0], d[g[u][i]][1]), d[u][0]);
        d[u][1] = max(d[u][1], d[g[u][i]][1]+d[u][1]);
    }
    d[u][1] += v[u];
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%lld", &v[i]);
        mx = max(mx, v[i]);
    }
    for(int i = 1; i < n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    f(1, 0);
    printf("%lld", max(d[1][0], d[1][1]));
}