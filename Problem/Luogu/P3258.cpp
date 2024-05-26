//
// Created by kibi on 2022/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n, id[300005], eid[300005];
vector<int> g[300005];
bool vis[300005];
int b[300005];
int lca[300005];
int ans[300005];
int fa[300005];
int fin_ans[300005];

int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

void f(int u, int fa){
    ::fa[u] = fa;
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue;
        }
        f(g[u][i], u);
    }
    vis[u] = true;
    if(vis[u+1]){
        lca[u] = find(b[u+1]);
    }
    if(vis[u-1]){
        lca[u-1] = find(b[u-1]);
    }
    b[u] = b[fa];
}

void dfs(int u, int fa){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i] == fa){
            continue ;
        }
        dfs(g[u][i], u);
        fin_ans[u] += fin_ans[g[u][i]];
    }
    fin_ans[u] += ans[u];
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        b[i] = i;
        scanf("%d", &id[i]);
        eid[id[i]] = i;
    }

    for(int i = 1; i < n; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        u = eid[u], v = eid[v];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    f(1, 0);

    for(int i = 1; i < n; i++){
        int u = i, v = i+1;
        if(u == lca[u]){
            ans[fa[v]]++;
            ans[fa[u]]--;
        }else if(v == lca[u]){
            ans[u]++;
            ans[v]--;
        }else{
            ans[u]++;
            ans[fa[v]]++;
            ans[fa[lca[u]]]--;
            ans[lca[u]]--;
        }
    }

    dfs(1, 0);

    for(int i = 1; i <= n; i++){
        printf("%d\n", fin_ans[eid[i]]);
    }
}