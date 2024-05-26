//
// Created by kibi on 2022/7/31.
//
#include <bits/stdc++.h>
using namespace std;
int n, mxx, mxy;
int xy[3005][2];
double dis[3005][3005];
bool vis[3005];
//double mem[3005];
//struct node{
//    int v;
//    double w;
//};
//vector<node> g[3005];
//bool cmp(node a, node b){
//    return a.w < b.w;
//}
//double ans = 1e9;

//double f(int u){
//    if(u == 3001){
//        return 0;
//    }
//    if(mem[u]!=10843961455707782.0){
//        return mem[u];
//    }
//    int sg = g[u].size();
//    for(int i = 0; i < sg; i++){
//        if(g[u][i].w > max(mem[u], mem[0]) || vis[g[u][i].v]){
//            continue;
//        }
//        vis[g[u][i].v] = true;
//        mem[u] = min(max(f(g[u][i].v), g[u][i].w), mem[u]);
//        vis[g[u][i].v] = false;
////        ans = min(ans, mem[u]);
//    }
//    return mem[u];
//}

int nxt[3005], pre[3005];
bool bfs(double d){
    //    memset(vis, 0, sizeof vis);
    queue<int> q;
    //    head = 1;
    for(int i = 1; i <= n; i++){
        nxt[i-1] = i;
        pre[i] = i-1;
    }
    //    nxt[]
    //    nxt[n] = 0;
    //    pre[n+1] = 0;
    for(int i = 1; i <= n; i++){
        if(dis[0][i] < d){
            //            vis[i] = true;
            nxt[pre[i]] = nxt[i];
            pre[nxt[i]] = pre[i];
            q.push(i);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(dis[u][3001] < d){
            return false;
        }
        for(int i = nxt[0]; i != 0; i=nxt[i]){
            if(dis[u][i] < d*d*4/* && !vis[i]*/){
                //                vis[i] = true;
                nxt[pre[i]] = nxt[i];
                pre[nxt[i]] = pre[i];
                q.push(i);
            }
        }
    }
    return true;
}

int main(){
    scanf("%d %d %d", &n, &mxx, &mxy);
    mxx--;
    mxy--;
    //    memset(mem, 0x43, sizeof mem);
    for(int i = 1; i <= n; i++){
        scanf("%d %d", &xy[i][0], &xy[i][1]);
        xy[i][0]--;
        xy[i][1]--;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j < i; j++){
            //            double tw = sqrt(pow(xy[i][0]-xy[j][0], 2)+pow(xy[i][1]-xy[j][1], 2));
            double tw = pow(xy[i][0]-xy[j][0], 2)+pow(xy[i][1]-xy[j][1], 2);
            dis[i][j] = dis[j][i] = tw;
            //            g[i].push_back({j, tw});
            //            g[j].push_back({i, tw});
        }
    }
    for(int i = 1; i <= n; i++){
        double fw = min(xy[i][0] ,mxy-xy[i][1]), tw = min(xy[i][1], mxx-xy[i][0]);
        dis[0][i] = dis[i][0] = fw;
        dis[3001][i] = dis[i][3001] = tw;
        //        g[0].push_back({i, fw});
        //        g[i].push_back({0, fw});
        //        g[3001].push_back({i, tw});
        //        g[i].push_back({3001, tw});
    }
    //    for(int i = 0; i <= n; i++){
    //        sort(g[i].begin(), g[i].end(), cmp);
    //    }
    //    f(0);
    //    printf("%.2lf", mem[0]);
    double l = 0, r = min(mxx, mxy), mid;
    for(int i = 1; i <= 25; i++){
        mid = (l+r)/2;
        if(bfs(mid)){
            l = mid;
        }else{
            r = mid;
        }
    }
    printf("%.2lf", l);
}