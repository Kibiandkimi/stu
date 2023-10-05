//
// Created by kibi on 23-10-4.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 3000;

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

    class Graph{
        class Edge{
        public:
            int v, w;
            Edge *nxt;
        };

        Edge *head[N + 5];

    public:
        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{v, w, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u, w);
        }

        Edge* begin(int x){
            return head[x];
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Graph graph;
    for(int i = 0; i < n - m; i++){
        static int k;
        read(k);
        for(int j = 0; j < k; j++){
            static int a, c;
            read(a), read(c);
            graph.add_edge(i + 1, a, c);
        }
    }

    int val[m];
    for(int &i : val){
        read(i);
    }

    static int f[N + 5][N + 5];
    memset(f, ~0x3f, sizeof f);

    for(int i = n - m + 1; i <= n; i++){
        f[i][1] = val[i - n + m - 1];
    }
    for(int i = 1; i <= n; i++){
        f[i][0] = 0;
    }

    auto dfs = [&](auto &&dfs, int u) -> int{
        int sum = 0;
        for(auto i = graph.begin(u); i; i = i->nxt){
            int num = dfs(dfs, i->v);
            int t[sum + 1];
            memcpy(t, f[u], sizeof t);
            for(int j = 0; j <= sum; j++){
                for(int k = 0; k <= num; k++){
                    f[u][j + k] = max(f[u][j + k], t[j] + f[i->v][k] - i->w);
                }
            }
            sum += num;
        }
        return sum + (u >= n - m);
    };

    dfs(dfs, 1);

    for(int i = m; i >= 0; i--){
        if(f[1][i] >= 0){
            printf("%d\n", i);
            return 0;
        }
    }
}