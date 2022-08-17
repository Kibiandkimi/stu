//
// Created by kibi on 22-8-13.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int b[20005];
bool flag[20005];
int d[20005];

struct e{
    int u, v, w;
};

vector<e> g;

bool cmp(e t1, e t2){
    return t1.w > t2.w;
}

int find(int x){
    if(x != b[x]){
        return b[x] = find(b[x]);
    }
    return x;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1; i <= m; i++){
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        g.push_back({x, y, z});
    }
    sort(g.begin(), g.end(), cmp);
    for(int i = 0; i < m; i++){
//        vis[g[i].u] = true;
//        vis[g[i].v] = true;
        if(find(g[i].u) == find(g[i].v)){
            printf("%d", g[i].w);
            return 0;
        }
        if(!d[g[i].u]){
            d[g[i].u] = g[i].v;
        }else{
            b[find(d[g[i].u])] = find(g[i].v);
        }
        if(!d[g[i].v]){
            d[g[i].v] = g[i].u;
        }else{
            b[find(d[g[i].v])] = find(g[i].u);
        }

    }
    printf("0");
}