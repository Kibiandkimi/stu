//
// Created by kibi on 22-8-25.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, r, p;
vector<int> g[500005];
vector<int> gg[500005];
int w[500005];

int dfn[500005], low[500005], y[500005], sum[500005], tot, cnt;
bool vis[500005];
stack<int> stk;
void tarjan(int u){
    dfn[u] = low[u] = ++tot;
    stk.push(u);
    vis[u] = true;
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        int t = g[u][i];
        if(!dfn[t]){
            tarjan(t);
            low[u] = min(low[u], low[t]);
        }else if(vis[t]){
            low[u] = min(low[u], dfn[t]);
        }
    }
    if(dfn[u] == low[u]){
        cnt++;
        while((!stk.empty())&&stk.top()!=u){
            int tp = stk.top();
            stk.pop();
            sum[cnt] += w[tp];
            vis[tp] = false;
            y[tp] = cnt;
        }
        int tp = stk.top();
        stk.pop();
        sum[cnt] += w[tp];
        vis[tp] = false;
        y[tp] = cnt;
    }
}

int d[500005];

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    scanf("%d %d", &r, &p);
//    for(int i = 1; i <= n; i++){
//        if(!dfn[i]){
//            tarjan(i);
//        }
//    }
    tarjan(r);
    int in[500005];
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            continue;
        }
        int sg = g[i].size();
        for(int j = 0; j < sg; j++){
            if(y[g[i][j]] != y[i]){
                gg[y[i]].push_back(y[g[i][j]]);
                in[y[g[i][j]]]++;
            }
        }
    }
//    memset(vis, 0, sizeof vis);
    d[y[r]] = sum[y[r]];
    queue<int> q;
    q.push(y[r]);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = gg[u].size();
        for(int i = 0; i < sg; i++){
            d[gg[u][i]] = max(d[gg[u][i]], d[u]+sum[gg[u][i]]);
//            in[gg[u][i]]--;
            if(!(--in[gg[u][i]])){
                q.push(gg[u][i]);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= p; i++){
        int t;
        scanf("%d", &t);
        ans = max(ans, d[y[t]]);
    }
    printf("%d", ans);
}