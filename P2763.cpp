//
// Created by kibi on 2022/8/26.
//
#include <bits/stdc++.h>
using namespace std;
int n, k, m;
int s, t = 1022;
struct node{
    node(int t1, int t2, int t3){
        v = t1, w = t2, r = t3;
    }
    void get(int &t1, int &t2, int &t3) const{
        t1 = v, t2 = w, t3 = r;
    }
    int v, w, r;
};
vector<node> g[1025];

void read(int &t){
    int s = 0, w = 1;
    int c = getchar();
    while(c<'0'||'9'<c){if(c=='-')w=-1;c=getchar();}
    while('0'<=c&&c<='9'){s=s*10+c-'0';c=getchar();}
    t=s*w;
}

int lv[1025], cur[1025];
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
            int v, w, r;
            g[u][i].get(v, w, r);
            if(w && lv[v]==-1){
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
    for(int i = cur[u]; i < sg; i++){
        cur[u] = i;
        int v, w, r;
        g[u][i].get(v, w, r);
        //        w = g[u][i].w;
        if(w && lv[v]==lv[u]+1){
            int c = dfs(v, min(w, rmn));
            rmn -= c;
            g[u][i].w -= c;
            g[v][r].w += c;
        }
    }
    return flow - rmn;
}

void find(){
    int sgt = g[t].size();
    for(int i = 0; i < sgt; i++){
        int v, w, r;
        g[t][i].get(v, w, r);
        if(v>=1000) {
            int sgv = g[v].size();
            printf("%d: ", v-1000);
            for (int j = 0; j < sgv; j++) {
                int vv, vw, vr;
                g[v][j].get(vv, vw, vr);
                if (vw && vv <= n && vv >= 1) {
                    printf("%d ", vv);
                }
            }
            printf("\n");
        }
    }
}

int main(){
    //    scanf("%d %d", &k, &n);
    read(k);
    read(n);
    for(int i = 1; i <= k; i++){
        int t;
        read(t);
        m += t;
        int u = i + 1000;
        int v = ::t;
        g[u].emplace_back(v, t, g[v].size());
        g[v].emplace_back(u, 0, g[u].size()-1);
    }
    for(int i = 1; i <= n; i++){
        int p;
        read(p);
        while(p--){
            int t;
            read(t);
            int u = i, v = t+1000;
            g[u].emplace_back(v, 1, g[v].size());
            g[v].emplace_back(u, 0, g[u].size()-1);
        }
        int u = s, v = i;
        g[u].emplace_back(v, 1, g[v].size());
        g[v].emplace_back(u, 0, g[u].size()-1);
    }

    int ans = 0;
    while(bfs()){
        ans += dfs();
    }
    if(ans != m){
        printf("No Solution!");
    }else {
        //        printf("%d\n", ans);
        find();
    }
}