//
// Created by kibi on 23-10-3.
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
            int v;
            Edge *nxt;
        };
        Edge *head[];

    public:
        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Graph graph; // x->x-1, !x->n+x-1
    for(int i = 0; i < m; ++i){
        static int x, a, y, b;
        read(x), read(a), read(y), read(b);
        static int u, v;
        u = n + x - 1, v = n + y - 1;
        if(!a && !b){
            graph.add_edge(x, v);
            graph.add_edge(y, u);
        }else if(!a && b){
            graph.add_edge(x, y);
            graph.add_edge(v, u);
        }else if(a && !b){
            graph.add_edge(u, v);
            graph.add_edge(y, x);
        }else{
            graph.add_edge(u, y);
            graph.add_edge(v, x);
        }
    }

}