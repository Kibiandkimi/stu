//
// Created by kibi on 2022/7/20.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, r;
struct node{
    int v, id;
};
vector<int> g[500005];
vector<node> q[500005];
int ans[500005];
int b[500005];
bool vis[500005];

int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

void f(int u, int fa){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue ;
        }
        f(g[u][i], u);
    }
    vis[u] = true;

    int sq = q[u].size();
    for(int i = 0; i < sq; i++){
        if(vis[q[u][i].v]){
            ans[q[u][i].id] = find(b[q[u][i].v]);
        }
    }
    b[u] = find(b[fa]);
}

int main(){
    scanf("%d %d %d", &n, &m, &r);
    for(int i = 1; i < n; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].push_back(y);
        g[y].push_back(x);
        b[i] = i;
    }
    b[n] = n;
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        q[x].push_back({y, i});
        q[y].push_back({x, i});
    }
    f(r, r);
    for(int i = 1; i <= m; i++){
        printf("%d\n", ans[i]);
    }
}