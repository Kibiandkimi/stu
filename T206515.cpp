//
// Created by kibi on 23-9-10.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 1000000;

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if(c == '-')[[unlikely]]{
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
            int v{};
            Edge *nxt{nullptr};
        };

        Edge *head[N + 5]{nullptr};
        Edge edge[N + 5];
        int cnt;

        friend class Work;

    public:
        void add_edge(int u, int v, bool flag = false){
            edge[++cnt] = {v, head[u]};
            head[u] = &edge[cnt];

            if(!flag)[[likely]]{
                return;
            }

            add_edge(v, u);
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static bool in[N + 5];
    static Graph graph;
    for(int i = 1; i <= n; i++){
        int pre;
        read(pre);
        if(pre != -1){
            in[i] = true;
            graph.add_edge(pre, i);
        }
    }

    class Work{
    public:
        int calc_tree(int x, int fa){
            for(auto i = graph.head[x]; i; i = i->nxt){
                if(i->v != fa){
                    calc_tree(i->v, x);
                }
            }
        }
    };

    for(int i = 1; i <= n; i++){
        if(!in[i]){

        }
    }

}