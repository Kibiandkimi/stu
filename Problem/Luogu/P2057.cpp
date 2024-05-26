//
// Created by kibi on 2022/7/12.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int dep[305];
int inf = 0x3f3f3f3f;
struct node{
    int v, w, r;
};
vector<node> g[305];

void add_edge(int u, int v, int val){
    g[u].push_back({v, val, (int)g[v].size()});
    g[v].push_back({u, 0, (int)g[u].size()-1});
}

bool bfs(){
    memset(dep, 0, sizeof dep);
    queue<int> q;
    dep[0] = 1;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sa = g[u].size();
        for(int i = 0; i < sa; i++){
            if(g[u][i].w > 0 && dep[g[u][i].v] == 0){
                dep[g[u][i].v] = dep[u]+1;
                q.push(g[u][i].v);
            }
        }
    }
    if(!dep[n+1]){
        return false;
    }
    return true;
}

int dfs(int u, int f){
    if(u == n+1){
        return f;
    }
    int ans = 0, sa = g[u].size();
    for(int i = 0; i < sa; i++){
        if(g[u][i].w > 0 && dep[g[u][i].v] == dep[u]+1){
            int temp = dfs(g[u][i].v, min(f, g[u][i].w));
            g[u][i].w -= temp;
            g[g[u][i].v][g[u][i].r].w += temp;
            f -= temp;
            ans += temp;
            if(f == 0){
                break;
            }
        }
    }
    return ans;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        int o;
        scanf("%d", &o);
        if(!o){
            add_edge(0, i, 1);
        }else{
            add_edge(i, n+1, 1);
        }
    }

    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y, 1);
        add_edge(y, x ,1);
    }

    int ans = 0;
    while(bfs()){
        ans += dfs(0, inf);
    }
    printf("%d", ans);

    return 0;
}