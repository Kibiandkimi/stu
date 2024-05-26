//
// Created by kibi on 2022/7/30.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, q;
int t[205];
struct node{
    int v, w;
};
struct node2{
    int u, v, w, s;
};
vector<node> g[205];
vector<node2> edge;
bool cmp(node2 a, node2 b){
    return a.s < b.s;
}
int z[205][205];

int main(){
    memset(z, 0x3f, sizeof z);
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%d", &t[i]);
    }
    for(int i = 1; i <= m; i++){
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        //        g[x].push_back({y, w});
        //        g[y].push_back({x, w});
        edge.push_back({x, y, w, max(t[x], t[y])});
    }
    sort(edge.begin(), edge.end(), cmp);
    int cnt = 0;
    scanf("%d", &q);
    while(q--){
        int x, y, d;
        scanf("%d %d %d", &x, &y, &d);
        while(edge[cnt].s <= d && cnt < edge.size()){
            node2 t = edge[cnt++];
            int tx = t.u, ty = t.v, tw = t.w;
            if(z[tx][ty]>tw) {
                g[tx].push_back({ty, tw});
                g[ty].push_back({tx, tw});
                z[tx][ty] = z[ty][tx] = tw;
                queue<node> q;
                q.push({tx, ty});
                //                q.push(ty);
                while(!q.empty()){
                    node ut = q.front();
                    q.pop();
                    int x = ut.v, y = ut.w;
                    int sg = g[x].size();
                    for(int i = 0; i < sg; i++){
                        int v = g[x][i].v;
                        if(z[y][v] > z[x][y] + z[x][v]){
                            z[y][v] = z[v][y] = z[y][x] + z[x][v];
                            q.push({y, v});
                        }
                    }
                    sg = g[y].size();
                    for(int i = 0; i < sg; i++){
                        int v = g[y][i].v;
                        if(z[x][v] > z[x][y] + z[y][v]){
                            z[x][v] = z[v][x] = z[x][y] + z[y][v];
                            q.push({x, v});
                        }
                    }
                }
            }
        }
        if(z[x][y] > 1e8){
            printf("-1\n");
        }else{
            printf("%d\n", z[x][y]);
        }

    }

}