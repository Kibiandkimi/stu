//
// Created by kibi on 22-8-16.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
struct node{
    int id, v, p;
};
vector<node> t[65];
int d[32005][65];
bool vis[32005];

void up(int u, int v, int p, int a){
    if(u-p<0){
        return ;
    }
    if(d[u-p][a] == -1){
        return ;
    }
//    if(vis[u-p]){
//        return ;
//    }
    if(d[u-p][a]+v>d[u][0]){
        d[u][0] = d[u-p][a]+v;
//        vis[u] = true;
    }
//    d[u] = max(d[u-p]+v, d[u]);
}

int main(){
    scanf("%d %d", &n, &m);
    n = n/10;
    for(int i = 1; i <= m; i++){
        int v, p, q;
        scanf("%d %d %d", &p, &v, &q);
        t[q].push_back({i, v, p/10});
    }
    memset(d, -1, sizeof d);
    int s0 = t[0].size();
    d[0][0] = 0;
    for(int i = 0; i < s0; i++) {
        for(int k = 0; k <= n; k++){
            d[k][t[0][i].id] = d[k][0];
        }
        for (int p = t[0][i].p; p <= n; p++) {
            up(p, t[0][i].v*t[0][i].p, t[0][i].p, t[0][i].id);
            if(t[t[0][i].id].size()>=1){
                up(p, t[0][i].v*t[0][i].p+t[t[0][i].id][0].p*t[t[0][i].id][0].v, t[0][i].p+t[t[0][i].id][0].p, t[0][i].id);
            }
            if(t[t[0][i].id].size()>=2){
                up(p, t[0][i].v*t[0][i].p+t[t[0][i].id][1].p*t[t[0][i].id][1].v, t[0][i].p+t[t[0][i].id][1].p, t[0][i].id);
                up(p, t[0][i].v*t[0][i].p+t[t[0][i].id][1].p*t[t[0][i].id][1].v+t[t[0][i].id][0].p*t[t[0][i].id][0].v, t[0][i].p+t[t[0][i].id][1].p+t[t[0][i].id][0].p, t[0][i].id);
            }
        }
//        memset(vis, 0, sizeof vis);
    }
    int mx = 0;
    for(int i = 0; i <= n; i++){
        mx = max(mx, d[i][0]);
    }
    printf("%d", mx*10);
}