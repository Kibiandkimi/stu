//
// Created by kibi on 2022/8/18.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
//vector<int> g[55];
bool g[65][65][65];
int dis[65][65];

int main(){
    memset(dis, 0x3f, sizeof dis);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        //        g[u].push_back(v);
        g[u][v][0] = true;
        dis[u][v] = 1;
        //        g[v].push_back(u);
    }
    for(int k = 1; k <= 40; k++){
        for(int i = 1; i <= n; i++){
            for(int t = 1; t <= n; t++){
                for(int j = 1; j <= n; j++){
                    if(g[i][t][k-1]&&g[t][j][k-1]){
                        g[i][j][k] = true;
                        dis[i][j] = 1;
                    }
                }
            }
        }
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    printf("%d", dis[1][n]);
}