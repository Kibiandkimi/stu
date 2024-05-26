//
// Created by kibi on 2022/7/14.
//

//两段是一样哒

//#include <bits/stdc++.h>
//using namespace std;
//long long n, m;
//long long inf = 1e18;
////long long w[505][505];
////struct node{
////    int v;
////    long long w = -inf;
////};
////vector<node> g[505];
//
//long long w[505][505];
//long long link[505], lx[505], ly[505], pre[505], slack[505];
//bool vis[505];
//
////void add_edge(int x, int y, long long w){
//////    g[x].push_back({y, w});
////    ::w[x][y] = w;
////}
//
//void bfs(long long u){
//
//    //    long long x, y = 0, yy = 0, delta;
//    //    memset(pre, 0, sizeof(pre));
//    //    for (int i = 1; i <= n; ++i)
//    //        slack[i] = inf;
//    //    link[y] = u;
//    long long x, y = 0, yy = 0, delta;
//    memset(pre, 0, sizeof pre);
//
//    for(int i = 1; i <= n; i++){
//        slack[i] = inf;
//    }
//    link[y] = u;
//
//    while(true) {
//        x = link[y];
//        delta = inf;
//        vis[y] = true;
//        //        int sg = g[x].size();
//
//        //        for(int i = 0; i < sg; i++){
//        //            int v = g[x][i].v;
//        //            if(vis[v]){
//        //                continue;
//        //            }
//        //            if(slack[v] > lx[x] + ly[v] - g[x][i].w){
//        //                slack[v] = lx[x] + ly[y] - g[x][i].w;
//        //                pre[v] = y;
//        //            }
//        //            if(slack[v] < delta){
//        //                delta = slack[v];
//        //                yy = v;
//        //            }
//        //        }
//
//        for (int i = 1; i <= n; i++) {
//            if (vis[i]) {
//                continue;
//            }
//            if (slack[i] > lx[x] + ly[i] - w[x][i]) {
//                slack[i] = lx[x] + ly[i] - w[x][i];
//                pre[i] = y;
//            }
//            if (slack[i] < delta) {
//                delta = slack[i];
//                yy = i;
//            }
//        }
//
//        for (int i = 0; i <= n; i++) {
//            if (vis[i]) {
//                lx[link[i]] -= delta;
//                ly[i] += delta;
//            } else {
//                slack[i] -= delta;
//            }
//        }
//
//        y = yy;
//        if (link[y] == -1) {
//            break;
//        }
//    }
//
//    while(y){
//        link[y] = link[pre[y]];
//        y = pre[y];
//    }
//}
//
//
//
//int main(){
//    scanf("%d %d", &n, &m);
//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j <= n; j++){
//            w[i][j] = -inf;
//        }
//    }
//    for(int i = 1; i <= m; i++){
//        int x, y;
//        long long z;
//        scanf("%d %d %lld", &x, &y, &z);
//        //        add_edge(x, y, z);
//        w[x][y] = z;
//    }
//
//    memset(link, -1, sizeof link);
//    memset(lx, 0, sizeof lx);
//    memset(ly, 0, sizeof ly);
//    for(int i = 1; i <= n; i++){
//        memset(vis, 0, sizeof vis);
//        bfs(i);
//    }
//    long long ans = 0;
//    for(int i = 1; i <= n; i++){
//        if(link[i] != -1){
//            ans += w[link[i]][i];
//        }
//        //        int sg = g[link[i]].size();
//        //        for(int j = 0; j < sg; j++){
//        //            if(g[link[i]][j].v == i){
//        //                ans += g[link[i]][j].w;
//        //            }
//        //        }
//
//    }
//    printf("%lld\n", ans);
//
//    for(int i = 1; i <= n; i++){
//        printf("%lld ", link[i]);
//    }
//    printf("\n");
//}

#include <bits/stdc++.h>
using namespace std;
long long n, m;
long long inf = 1e18;
long long w[505][505];
long long link[505], lx[505], ly[505], pre[505], slack[505];
bool vis[505];

void bfs(long long u) {
    long long x, y = 0, yy = 0, delta;
    memset(pre, 0, sizeof pre);
    for (int i = 1; i <= n; i++) {
        slack[i] = inf;
    }
    link[y] = u;

    while (true) {
        x = link[y];
        delta = inf;
        vis[y] = true;

        for (int i = 1; i <= n; i++) {
            if (vis[i]) {
                continue;
            }
            if (slack[i] > lx[x] + ly[i] - w[x][i]) {
                slack[i] = lx[x] + ly[i] - w[x][i];
                pre[i] = y;
            }
            if (slack[i] < delta) {
                delta = slack[i];
                yy = i;
            }
        }

        for (int i = 0; i <= n; i++) {
            if (vis[i]) {
                lx[link[i]] -= delta;
                ly[i] += delta;
            } else {
                slack[i] -= delta;
            }
        }

        y = yy;
        if (link[y] == -1) {
            break;
        }
    }

    while (y) {
        link[y] = link[pre[y]];
        y = pre[y];
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            w[i][j] = -inf;
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        long long z;
        scanf("%d %d %lld", &x, &y, &z);
        w[x][y] = z;
    }

    memset(link, -1, sizeof link);
    memset(lx, 0, sizeof lx);
    memset(ly, 0, sizeof ly);

    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        bfs(i);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (link[i] != -1) {
            ans += w[link[i]][i];
        }
    }

    printf("%lld\n", ans);
    for (int i = 1; i <= n; i++) {
        printf("%lld ", link[i]);
    }
    printf("\n");
}