//
// Created by kibi on 2022/8/26.
//
#include <bits/stdc++.h>
static const int MAXN = 405;
using namespace std;
int n, m, s, t = 401;
struct node{
    node(int t1, int t2, int t3){
        v = t1, w = t2, r = t3;
    }
    void get(int &tv, int &tw, int &tr)const{
        tv = v, tw = w, tr = r;
    }
    int v, w, r;
};

vector<node> g[MAXN];

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c<'0'||'9'<c){
        if(c=='-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0'<=c&&c<='9'){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s;
}

void add_edge(int u, int v) {
    g[u].emplace_back(v, 1, g[v].size());
    g[v].emplace_back(u, 0, g[u].size()-1);
    //    return u;
}

int lv[MAXN], cur[MAXN];
bool bfs(){
    memset(lv, -1, sizeof lv);
    lv[s] = 0, cur[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        int sg = g[u].size();
        for(int i = 0; i < sg; i++){
            int v, w, r;
            g[u][i].get(v, w, r);
            if(w && lv[v]==-1){
                lv[v] = lv[u]+1;
                cur[u] = 0;
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
    int sg = g[u].size(), rmn = flow;
    for(int i = cur[u]; i < sg; i++){
        int v, w, r;
        g[u][i].get(v, w, r);
        if(w && lv[v]==lv[u]+1){
            int c = dfs(v, min(rmn, w));
            rmn -= c;
            g[u][i].w -= c;
            g[v][r].w += c;
        }
    }
    return flow - rmn;
}


int main(){
    //    scanf("%d %d", &n, &m);
    read(n);
    read(m);
    for(int i = 1; i <= n; i++){
        int sum;
        read(sum);
        while(sum--){
            int l;
            read(l);
            int v = l+200;
            add_edge(i, v);
        }
        add_edge(s, i);
        //        g[s].emplace_back(i, 1, g[i].size());
        //        g[i].emplace_back(s, 0, g[s].size()-1);
    }
    for(int i = 1; i <= m; i++){
        int u = i+200, v = t;
        add_edge(u, v);
        //        g[u].emplace_back(v, 1, g[v].size());
        //        g[v].emplace_back(u, 0, g[u].size()-1);
    }
    int ans = 0;
    while(bfs()){
        ans += dfs();
    }
    printf("%d", ans);
}