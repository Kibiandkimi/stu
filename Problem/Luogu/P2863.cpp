//
// Created by kibi on 2022/10/27.
//
#include <bits/stdc++.h>
using namespace std;

class Graph {
    int head[10005], nxt[50005], to[50005], tot;
public:
    void addEdge(int u, int v, bool flag = true) {
        to[++tot] = v, nxt[tot] = head[u], head[u] = tot;
        if (!flag) {
            return;
        }
        to[++tot] = u, nxt[tot] = head[v], head[v] = tot;
    }
    int begin(int x) {
        return head[x];
    }
    int next(int x) {
        return nxt[x];
    }
    int get(int x) {
        return to[x];
    }
};

void read(int &x);

class Solution{
    static const int Size = 10005;
    int sta[Size]{}, r, dfn[Size]{}, low[Size]{}, idSiz[Size]{}, cntDfs{}, cntId{};
    bool vis[Size]{};
    Graph *g;
    void f(int u){
        dfn[u] = low[u] = ++cntDfs;
        sta[++r] = u;
        vis[u] = true;
        for(int i = g->begin(u); i; i = g->next(i)){
            //            TODO why can't "v" be static
            int v;
            v = g->get(i);
            if(!dfn[v]){
                f(v);
                low[u] = min(low[u], low[v]);
            }else if(vis[v]){
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]){
            cntId++;
            while(sta[r] != u){
                vis[sta[r--]] = false;
                idSiz[cntId]++;
            }
            vis[sta[r--]] = false;
            idSiz[cntId]++;
        }
    }
public:
    int ans{};
    Solution(int n, Graph *g){
        this -> g = g, r = -1;
        for(int i = 1; i <= n; i++){
            if(!dfn[i]){
                f(i);
            }
        }
        for(int i = 1; i <= cntId; i++){
            if(idSiz[i] > 1){
                ans++;
            }
        }
    }
};

int main(){
    int n, m;
    read(n), read(m);
    static Graph g;
    for(int i = 0; i < m; ++i){
        int u, v;
        read(u), read(v);
        g.addEdge(u, v, false);
    }
    static Solution solve(n, &g);
    printf("%d", solve.ans);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}