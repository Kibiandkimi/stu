//
// Created by kibi on 2022/8/21.
//
#include <bits/stdc++.h>
using namespace std;
int n, q, d[105][105];
int root;
struct node{
    int v, w;
};
vector<node> g[105];
//int num_e[105];
//bool vis[105];

int f(int u, int fa){
    int sg = g[u].size();
    //    d[u][0] =
    if(sg == 1){
        d[u][0] = g[u][0].w;
        return 1;
    }else if(sg == 2){
        int s1, s2, ans = 0;
        s1 = f(g[u][0].v, u);
        s2 = f(g[u][1].v, u);
        int mxi = min(s1, q);
        for(int i = max(q-s2, 0); i <= mxi; i++){
            ans = max(ans, d[g[u][0].v][i]+d[g[u][1].v][q-i]);
        }
        return ans;
    }else{
        int s1, s2, v1, v2, w;
        if(g[u][0].v==fa){
            v1 = g[u][1].v;
            v2 = g[u][2].v;
            w = g[u][0].w;
        }else if(g[u][1].v==fa){
            v1 = g[u][0].v;
            v2 = g[u][2].v;
            w = g[u][1].w;
        }else{
            v1 = g[u][0].v;
            v2 = g[u][1].v;
            w = g[u][2].w;
        }
        s1 = f(v1, u);
        s2 = f(v2, u);
        //        int mxk = min(q, s1+s2);
        for(int k = 0; k <= q; k++) {
            int mxi = min(s1, k);
            for (int i = max(k - s2, 0); i <= mxi; i++) {
                d[u][k] = max(d[u][k], d[v1][i] + d[v2][k - i] + w);
            }
        }
        //        if(s1+s2+1<=q){
        //            d[u][s1+s2+1] = 0;
        //        }
        return s1+s2+1;
    }
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i = 1; i < n; i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        //        ++num_e[u], ++num_e[v];
    }
    q = (n-1)-q;
    //    for(int i = 1; i <= n; i++){
    //        if(!(num_e[i]%2)){
    //            root = i;
    //            break;
    //        }
    //    }
    root = 1;
    printf("%d", f(root, 0));
}