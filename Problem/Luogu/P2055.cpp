//
// Created by kibi on 2022/7/15.
//
#include <bits/stdc++.h>
using namespace std;
int T, n, s = 0, t = 104;
bool in_s[55], ba_h[55];
int dep[105];
int al;
struct node{
    int v, w, r;
};
vector<node> g[105]; //s->0, t->n+1

bool bfs(){
    queue<int> q;
    memset(dep, 0, sizeof dep);
    dep[0] = 1;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            if(g[u][i].w > 0 && (!dep[g[u][i].v])){
                dep[g[u][i].v] = dep[u] + 1;
                q.push(g[u][i].v);
            }
        }
    }
    if(!dep[t]){
        return false;
    }
    return true;
}

int dfs(int u, int f){
    if(u == t){
        return f;
    }
    int ans = 0, sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i].w > 0 && dep[g[u][i].v] == dep[u]+1){
            int temp = dfs(g[u][i].v, min(g[u][i].w, f));
            f -= temp;
            ans += temp;
            g[u][i].w -= temp;
            g[g[u][i].v][g[u][i].r].w += temp;
            if(!f){
                break;
            }
        }
    }
    if(ans == 0){
        dep[u] = 0;
    }
    return ans;
}

void add_edge(int u, int v){
    g[u].push_back({v, 1, (int)g[v].size()});
    g[v].push_back({u, 0, (int)g[u].size()-1});
}

int main(){
    scanf("%d", &T);
    while(T--){
        al = 0;
        memset(in_s, 0, sizeof in_s);
        memset(ba_h, 0, sizeof ba_h);
        vector<node> t_v[105];
        for(int i = 0; i < 105; i++){
            g[i].swap(t_v[i]);
        }
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            int tt;
            scanf("%d", &tt);
            if(tt){
                in_s[i] = true;
            }else{
                in_s[i] = false;
            }
            if(in_s[i]){
                add_edge(i+n, t);
            }
        }
        for(int i = 1; i <= n; i++){
            int tt;
            scanf("%d", &tt);
            if(tt){
                ba_h[i] = true;
            }else{
                ba_h[i] = false;
            }
            if((in_s[i]&&!ba_h[i]) || !in_s[i]){
                add_edge(s, i);
                al++;
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                int tt;
                scanf("%d", &tt);
                if(tt || i==j){
                    add_edge(i, j+n);
                }
            }
        }

        int ans = 0;
        while(bfs()){
            ans += dfs(0, 0x3f3f3f3f);
        }

        if(ans >= al){
            printf("^_^\n");
        }else{
            printf("T_T\n");
        }

    }
}