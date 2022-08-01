//
// Created by kibi on 2022/7/22.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, c;
int w[1005][1005];
long long v[1005][1005][3];
int t[4][2] = {{1,0},{-1, 0}, {0, 1}, {0, -1}};
bool vis[1005][1005];
struct node{
    int x, y;
    long long v;
    bool operator <(const node &b) const{
        return v > b.v;
    }
};
//vector<node> g[1005];

long long dis[1005][1005];

//void f(int x, int y, int d){
//    vis[x][y] = true;
//    for(int i = 0; i <= 3; i++){
//        int fx = x+t[i][0], fy = y+t[i][y];
//        if(!vis[fx][fy]){
//            f(fx, fy, d);
//        }
//    }
//}

void f(int x, int y){
    memset(dis, 0x3f, sizeof dis);
    //    memset(res, 0, sizeof res);
    memset(vis, 0, sizeof vis);

    priority_queue<node> q;

    q.push({x, y, w[x][y]});

    dis[x][y] = w[x][y];

    while(!q.empty()){
        node u = q.top();
        q.pop();
        if(vis[u.x][u.y]){
            continue;
        }
        vis[u.x][u.y] = true;
        for(int i = 0; i < 4; i++){
            int fx = u.x+t[i][0], fy = u.y+t[i][1];
            if(fx<1||fx>n||fy<1||fy>m){
                continue;
            }
            if(dis[fx][fy]>dis[u.x][u.y]+w[fx][fy]){
                dis[fx][fy] = dis[u.x][u.y] + w[fx][fy];
                q.push({fx, fy, dis[fx][fy]});
            }
        }
    }

}

int main(){
    scanf("%d %d %d %d %d", &n, &m, &a, &b, &c);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            scanf("%d", &w[i][j]);
        }
    }

    f(1, a);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j][0] = dis[i][j];
        }
    }

    f(n, b);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j][1] = dis[i][j];
        }
    }

    f(n, c);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j][2] = dis[i][j];
        }
    }

    long long ans = 1e18;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            ans = min(ans, v[i][j][0] + v[i][j][1] + v[i][j][2] - 2*w[i][j]);
        }
    }
    printf("%lld", ans);

}