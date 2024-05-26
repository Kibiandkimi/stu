//
// Created by kibi on 2022/7/15.
//

#include <bits/stdc++.h>
using namespace std;
long long n, m, s, t;
int dep[205];
struct node{
    long long v, w, r;
};
vector<node> g[205]; //s->0, t->n+1

bool bfs(){
    queue<int> q;
    memset(dep, 0, sizeof dep);
    dep[s] = 1;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            if(g[u][i].w > 0 && (!dep[g[u][i].v])){
                dep[g[u][i].v] = dep[u] + 1;
                q.push(g[u][i].v);
            }
        }
    }
    if(!dep[t]){
        return false;
    }
    return true;
}

long long dfs(int u, long long f){
    if(u == t){
        return f;
    }
    long long ans = 0, sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i].w > 0 && dep[g[u][i].v] == dep[u]+1){
            long long temp = dfs(g[u][i].v, min(g[u][i].w, f));
            f -= temp;
            ans += temp;
            g[u][i].w -= temp;
            g[g[u][i].v][g[u][i].r].w += temp;
            if(!f){
                break;
            }
        }
    }
    if(ans == 0){
        dep[u] = 0;
    }
    return ans;
}

void add_edge(long long u, long long v, long long w){
    g[u].push_back({v, w, (long long)g[v].size()});
    g[v].push_back({u, 0, (long long)g[u].size()-1});
}

int main(){
    scanf("%lld %lld %lld %lld", &n, &m, &s, &t);
    for(int i = 1; i <= m; i++){
        long long x, y, z;
        scanf("%lld %lld %lld", &x, &y, &z);
        add_edge(x, y, z);
    }
    long long ans = 0;
    while(bfs()){
        ans += dfs(s, 1e18);
    }
    printf("%lld", ans);

}