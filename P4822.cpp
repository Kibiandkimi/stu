//
// Created by kibi on 2022/8/1.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int dp_dis[55][55];
struct node{
    int v, w;
};
vector<node> g[55];
//bool vis[55];

//void f(int u){
//    int sg = g[u].size();
//    for(int i = 0; i < sg; i++){
//        if(vis[g[u][i].v]){
//            continue;
//        }
//        int to = g[u][i].v, wei = g[u][i].w;
//        dp_dis[to][0] = min(dp_dis[to][0], dp_dis[u][0]+wei);
//        for(int i = 1; i <= k; i++){
//            dp_dis[to][i] = min(dp_dis[to][i], min(dp_dis[u][i-1]+wei/2, dp_dis[u][i]+wei));
//        }
//        vis[to] = true;
//        f(to);
//        vis[to] = false;
//    }
//}

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= m; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    memset(dp_dis, 0x3f, sizeof dp_dis);
    dp_dis[1][0] = 0;

    queue<node> q;
    q.push({1, 0});
    while(!q.empty()){
        node t = q.front();
        q.pop();
        int u = t.v, l = t.w;
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            int v = g[u][i].v, wei = g[u][i].w;
            if(dp_dis[v][l] > dp_dis[u][l]+wei){
                dp_dis[v][l] = dp_dis[u][l]+wei;
                q.push({v, l});
            }
            if(l+1<=k && dp_dis[v][l+1] > dp_dis[u][l] + wei/2){
                dp_dis[v][l+1] = dp_dis[u][l] + wei/2;
                q.push({v, l+1});
            }
        }
    }

    //    f(1);
    int ans = 1e9;
    for(int i = 0; i <= k; i++){
        ans = min(ans, dp_dis[n][i]);
    }
    printf("%d", ans);
}