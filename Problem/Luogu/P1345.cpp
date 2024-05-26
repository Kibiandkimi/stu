//
// Created by kibi on 2022/7/12.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, s, t;
int inf = 0x3f3f3f3f;
int depth[205];
struct node{
    int v, w, r;
};
vector<node> g[205];

void add_edge(int u, int v, int w){
    g[u].push_back({v, w, (int)g[v].size()});
    g[u].push_back({u, 0, (int)g[u].size()});
}

// ???

//void add_edge(int u, int v, int w){
//    g[u].push_back({v, w, (int)g[v].size()});
//    g[v].push_back({u, 0, (int)g[u].size()-1});
//}

bool bfs(){
    queue<int> q;
    memset(depth, 0, sizeof depth);
    depth[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sa = g[u].size();
        for(int i = 0; i < sa; i++){
            if(g[u][i].w > 0 && depth[g[u][i].v] == 0){
                depth[g[u][i].v] = depth[u] + 1;
                q.push(g[u][i].v);
            }
        }
    }
    if(depth[t] == 0){
        return false;
    }
    return true;
}

int dfs(int u, int f){
    if(u == t){
        return f;
    }
    int ans = 0, sa = g[u].size();
    for(int i = 0; i < sa; i++){
        if(g[u][i].w > 0 && depth[g[u][i].v] == depth[u]+1){
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
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for(int i = 1; i <= n; i++){
        g[i].reserve(8);
    }
    for(int i = 1; i <= n; i++){
        if(i == s || i == t){
            add_edge(i, i+n, inf);
        }else{
            add_edge(i, i+n, 1);
        }
    }
    for(int i = 1; i <= m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x+n, y, inf);
        add_edge(y+n, x, inf);
    }

    int ans = 0;
    while(bfs()){
        ans += dfs(s, inf);
    }
    printf("%d", ans);

    return 0;
}