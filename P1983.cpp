//
// Created by kibi on 2022/7/19.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int in[1005];
vector<int> g[1005];
bool f[1005][1005];
int c[1005][1005];
int vis[1005];
int st = 1005, nd;
int id[1005];
//struct node{
//    int u, s;
//};
int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int k;
        scanf("%d", &k);
        for(int j = 1; j <= k; j++){
            scanf("%d", &c[i][j]);
            vis[c[i][j]] = i;
        }
        for(int j = c[i][1]; j <= c[i][k]; j++){
            if(vis[j] != i){
                for(int t = 1; t <= k; t++){
                    if(!f[j][c[i][t]]) {
                        g[j].push_back(c[i][t]);
                        in[c[i][t]]++;
                        f[j][c[i][t]] = true;
                    }
                }
            }
        }
        st = min(st, c[i][1]);
        nd = max(nd, c[i][k]);
    }
    stack<int> s;
    for(int i = 1; i <= n; i++){
        if(!in[i]){
            s.push(i);
            id[i] = 1;
        }
    }
    int ans = 1;
    while(!s.empty()){
        //        node t = s.top();
        int u = s.top();
        s.pop();
        ans = max(ans, id[u]);
        //        int u = t.u, num = t.s;
        //        if(vis[u] == 1e8){
        //
        //        }
        //        vis[u] = 1e8;
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            in[g[u][i]]--;
            id[g[u][i]] = max(id[g[u][i]], id[u]+1);
            if(!in[g[u][i]]){
                s.push(g[u][i]);
            }
        }
    }
    printf("%d", ans);
}
