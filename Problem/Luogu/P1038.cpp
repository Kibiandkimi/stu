//
// Created by kibi on 2022/5/12.
//
#include <bits/stdc++.h>
using namespace std;
int n, p;
int mxd;
int c[105], u[105];
int vis[105];
//int g[105][105];
int d[105];
class node{
public:
    int v,w;
};
vector<node> g[105];
int ind[105];
queue<int> q;
//void f(int u, int fa){
//    int sa = g[u].size();
//    for(int i = 0; i < sa; i++){
//
//        ind[g[u][i].v]++;
//        if(!d[g[u][i].v]){
//            d[g[u][i].v] = d[u]+1;
//            mxd = max(mxd, d[g[u][i].v]);
//            f(g[u][i].v, u);
//        }
//    }
//    return;
//}
void t(int v){
    c[v] -= u[v];
    return;
}
int main(){
    scanf("%d %d", &n, &p);
    for(int i = 1; i <= n; i++){
        scanf("%d %d", &c[i], &u[i]);
    }
    for(int i = 1; i <= p; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        //        g[u][v] = g[v][u] = w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    for(int i = 1; i <= n; i++){
        if(c[i]){
            ind[i] = 1;
            //            c[i] -= u[i];
            //            f(i, 0);
        }
    }
    for(int r = 1; ; r++) {
        for (int i = 1; i <= n; i++) {
            if (ind[i] == r) {
                q.push(i);
            }
        }
        if(q.empty()){
            mxd = r-1;
            break;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if(ind[u]!=1) {
                t(u);
            }
            vis[u] = 1;
            int sa = g[u].size();
            for (int i = 0; i < sa; i++) {
                int v = g[u][i].v;
                if (vis[v]) {
                    continue;
                }
                c[v] += g[u][i].w * (c[u] > 0 ? c[u] : 0);
                //                ind[v]--;
                ind[v] = r + 1;
                //                if (!ind[v]) {
                //                    c[v] -= u[v];
                //                    q.push(v);
                //                }
            }

        }
    }
    int fl = false;
    for(int i = 1; i <= n; i++){
        if(ind[i] == mxd && c[i]>0){
            fl = true;
            printf("%d %d\n", i, c[i]);
        }
    }
    if(!fl){
        printf("NULL");
    }
}