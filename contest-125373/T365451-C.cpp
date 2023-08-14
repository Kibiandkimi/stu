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

        void init(){
            dfs(1, 0);
        }

        int calc(int u, int v, int *res){
            if(dep[u] > dep[v]){
                swap(u, v);
            }
            int cnt_of_res = 0;
            while(dep[v] > dep[u]){
                res[cnt_of_res++] = v;
                v = fa[v];
            }
            while(v != u){
                res[cnt_of_res++] = u, res[cnt_of_res++] = v;
                u = fa[u], v = fa[v];
            }
            res[cnt_of_res++] = u;
            return cnt_of_res;
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

    for(int i = 0; i < k; i++){
        for(int j = 1; j < n; j++){
            int u, v;
            read(u), read(v);
            tree[i].add_edge(u, v, true);
        }
        tree[i].init();
    }

    static int ans[N + 5][N + 5];

    int cnt = 1;

    for(int i = 1; i < n; i++){
        for(int j = i+1; j <= n; j++){
            static int flag[N + 5];
            for(int flag_id = 1; flag_id <= n; flag_id++){
                flag[flag_id] = cnt;
            }
            for(int id = 0; id < k; id++){
                static int res[N + 5];
                int sum = tree[id].calc(i, j, res);
                for(int _i = 0; _i < sum; _i++){
                    flag[res[_i]] = (flag[res[_i]] == cnt) ? cnt+1 : 0;
                }
                for(int _i = 1; _i <= n; _i++){
                    flag[_i] = (flag[_i] == cnt+1) ? cnt : 0;
                }

            }
            for(int flag_id = 1; flag_id <= n; flag_id++){
                (flag[flag_id] == cnt) ? ans[i][j]++ : 0;
            }
            ans[j][i] = ans[i][j];
            cnt++;
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