//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 500, K = 500;

    class Graph{
        int head[N + 5], nxt[2 * N + 5], to[2 * N + 5], cnt;

        int dep[N + 5], fa[N + 5];

        void dfs(int u, int fa){
            dep[u] = dep[fa]+1;
            this -> fa[u] = fa;
            for(int i = head[u]; i; i = nxt[i]){
                int v = to[i];
                if(v != fa){
                    dfs(v, u);
                }
            }
        }

    public:
        void add_edge(int u, int v, bool flag = false){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;

            if(!flag){
                return;
            }

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
        }

        void init(int rt = 1){
            dfs(rt, 0);
        }

        int* get_dep(){
            return dep;
        }
    };

    class Tools{
    public:
        static void read(int &x){
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
    };

    auto read = Tools::read;

    int n, k;
    read(n), read(k);

    static Graph tree[K];

    static int dis[N + 5][N + 5];

    for(int i = 0; i < k; i++){
        for(int j = 1; j < n; j++){
            int u, v;
            read(u), read(v);
            tree[i].add_edge(u, v, true);
        }
        for(int j = 1; j <= n; j++) {
            tree[i].init(j);
            auto dep = tree[i].get_dep();
            for(int _k = 1; _k <= n; _k++){
                dis[j][_k] += dep[_k] - 1;
            }
        }
    }

    static int ans[N + 5][N + 5];

    for(int i = 1; i < n; i++){
        for(int j = i+1; j <= n; j++){
            for(int _k = 1; _k <= n; _k++){
                if(dis[i][_k] + dis[_k][j] == dis[i][j]){
                    ans[i][j]++;
                }
            }
            ans[j][i] = ans[i][j];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j){
                printf("1 ");
            }else{
                printf("%d ", ans[i][j]);
            }
        }
        printf("\n");
    }
}