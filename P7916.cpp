//
// Created by kibi on 22-9-6.
//
//TODO 似乎不能正常网络流
#include <bits/stdc++.h>
using namespace std;
int n, m, T, y[55];
int s, t = 552, dep[555], cur[555];
struct Edge{
    Edge(int tv, long long tw, int tr){
        v = tv, w = tw, r = tr;
    }
    int v, r;
    long long w;
};
vector<Edge> g[555];

void read(int &x);
bool bfs();
long long dfs(int u = s, long long flow = 1e18);

int main(){
    read(n), read(m), read(T);
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= m; j++){
            int u = (i-1)*n+j, v = i*n+j, w;
            read(w);
            g[u].emplace_back(v, w, g[v].size());
            g[v].emplace_back(u, w, g[u].size()-1);
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j < m; j++){
            int u = (i-1)*n+j, v = u+1, w;
            read(w);
            g[u].emplace_back(v, w, g[v].size());
            g[v].emplace_back(u, w, g[u].size()-1);
        }
    }
    while(T--){
        int k;
        read(k);
        for(int i = 1; i <= k; i++){
            int w, p, c;
            read(w), read(p), read(c);
            int u = 500+i, v = p<=m?p:p<=m+n?(p-m-1)*n+m:p<=2*m+n?(n-1)*n+(m-(p-m-n)+1):(2*m+2*n-p)*n+1;
            g[u].emplace_back(v, w, g[v].size());
            g[v].emplace_back(u, w, g[u].size()-1);
            if(c == 0){
                g[s].emplace_back(u, 1e18, g[u].size());
                g[u].emplace_back(s, 0, g[s].size()-1);
            }else{
                g[u].emplace_back(t, 1e18, g[t].size());
                g[t].emplace_back(u, 0, g[u].size()-1);
            }
        }
        long long ans = 0;
        while(bfs()){
            ans += dfs();
        }
        printf("%lld\n", ans);
        queue<int> q;
        for(int i = 1; i <= k; i++){
            int sg = g[500+i].size();
            for(int j = 0; j < sg; j++){
                int v = g[500+i][j].v;
                q.push(v);
            }
            vector<Edge>().swap(g[500+i]);
        }
        while(!q.empty()){
            int u = q.front();
            q.pop();
            int sg = g[u].size();
            for(int i = sg-1; i >= 0; i--){
                if(g[u][i].v>500){
                    g[u].pop_back();
                }else{
                    i = -1;
                }
            }
        }
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

bool bfs(){
    memset(dep, -1, sizeof dep);
    dep[s] = 0, cur[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            if(g[u][i].w>0&&dep[g[u][i].v]==-1){
                cur[g[u][i].v] = 0, dep[g[u][i].v] = dep[u]+1;
                q.push(g[u][i].v);
            }
        }
    }
    return dep[t]!=-1;
}

long long dfs(int u, long long flow){
    if(u == t){
        return flow;
    }
    long long rmn = flow;
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i].w && dep[g[u][i].v] == dep[u]+1){
            int c = dfs(g[u][i].v, min(g[u][i].w, rmn));
            rmn = rmn - c;
            g[u][i].w -= c;
            g[g[u][i].v][g[u][i].r].w += c;
        }
    }
    return flow - rmn;
}