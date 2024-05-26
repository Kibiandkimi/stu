//
// Created by kibi on 2022/8/26.
//
#include <bits/stdc++.h>
using namespace std;
int n, m;
int s, t = 103;
int lv[105], cur[105];
struct node{
    node(int t1, int t2, int t3) {
        v = t1;
        w = t2;
        r = t3;
    }
    int v, w, r;
};
vector<node> g[105];

bool bfs(){
    memset(lv, -1, sizeof lv);
    lv[s] = 0;
    cur[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            int v = g[u][i].v, w = g[u][i].w;
            if(w > 0 && lv[v]==-1){
                cur[v] = 0;
                lv[v] = lv[u]+1;
                q.push(v);
            }
        }
    }
    return lv[t]!=-1;
}

int dfs(int u = s, int flow = 1e9){
    if(u == t){
        return flow;
    }
    int rmn = flow;
    int sg = g[u].size();
    for(int i = cur[u]; i < sg && rmn; i++){
        cur[u] = i;
        int v = g[u][i].v, &w = g[u][i].w;
        if(w > 0 && lv[v]==lv[u]+1){
            int c = dfs(v, min(rmn, w));
            rmn -= c;
            w -= c;
            //            g[u][i].w -= c;
            g[v][g[u][i].r].w += c;
        }
    }
    return flow - rmn;
}

void find(){
    int sgt = g[t].size();
    for(int i = 0; i < sgt; i++){
        int v = g[t][i].v;
        if(g[t][i].w){
            int sgv = g[v].size();
            for(int j = 0; j < sgv; j++){
                int vv = g[v][j].v;
                //                if(g[v][j].w && m+1<=vv && vv<=m){//它也不给个警告，m+1<=vv && vv<=m能成立吗？？？
                if(g[v][j].w && m+1<=vv && vv<=n){
                    printf("%d %d\n", v, vv);
                    j = sgv;
                }
            }
        }
    }
}

int main(){
    scanf("%d %d", &m, &n);
    while (true){
        int u, v;
        scanf("%d %d", &u, &v);
        if(u==-1){
            break;
        }
        g[v].emplace_back(u, 1, g[u].size());
        g[u].emplace_back(v, 0, g[v].size()-1);
    }

    //    srand((unsigned)time(nullptr));
    //    for(int i = 1; i <= 50; i++){
    //        for(int j = 51; j <= 100; j++){
    //            int t = rand();
    //            if(t%2) {
    //                g[j].emplace_back(i, 1, g[i].size());
    //                g[i].emplace_back(j, 0, g[j].size() - 1);
    //            }
    //        }
    //    }

    for(int i = m+1; i <= n; i++){
        g[s].emplace_back(i, 1, g[i].size());
        g[i].emplace_back(s, 0, g[s].size()-1);
    }
    for(int i = 1; i <= m; i++){
        g[i].emplace_back(t, 1, g[t].size());
        g[t].emplace_back(i, 0, g[i].size()-1);
    }

    int ans = 0;
    while(bfs()){
        ans += dfs();
    }
    printf("%d\n", ans);

    find();
}