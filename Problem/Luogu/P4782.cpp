//
// Created by kibi on 23-10-3.
//

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
        Edge *head[2 * N + 5];

    public:
        class Tarjan{
        public:
            class Node{
            public:
                int low, dfn, col, id;
            };

        private:
            Node *node;
            Graph *graph;
            int cnt, num;
            bool *ins;
            stack<int> stk;

            void dfs(Node *u){
                u->dfn = u->low = ++cnt;
                stk.push(u->id);
                ins[u->id] = true;
                for(auto i = graph->head[u->id]; i; i = i->nxt){
                    if(!node[i->v].dfn){
                        dfs(&node[i->v]);
                        u->low = min(u->low, node[i->v].low);
                    }else if(ins[i->v]){
                        u->low = min(u->low, node[i->v].dfn);
                    }
                }
                if(u->low == u->dfn){
                    ++num;
                    u->col = num;
                    ins[stk.top()] = false;
                    u = &node[stk.top()];
                    stk.pop();
                    while(u->low != u->dfn){
                        u->col = num;
                        ins[stk.top()] = false;
                        u = &node[stk.top()];
                        stk.pop();
                    }
                }
            }

        public:
            Tarjan(int n, Node *node, Graph *graph):node(node), graph(graph), cnt(0), num(0){
                bool raw_ins[n];
                memset(raw_ins, 0, sizeof raw_ins);
                ins = raw_ins - 1;
                for(int i = 1; i <= n; i++){
                    if(!node[i].dfn){
                        dfs(&node[i]);
                    }
                }
            }

        };

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};

            if(!flag){[[likely]]
                return;
            }

            add_edge(v, u);
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Graph graph; // x->x, !x->n+x
    for(int i = 0; i < m; ++i){
        static int x, a, y, b;
        read(x), read(a), read(y), read(b);
        static int u, v;
        u = n + x, v = n + y;
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

    Graph::Tarjan::Node node[2 * n];
    memset(node, 0, sizeof node);
    for(int i = 0; i < 2 * n; i++){
        node[i].id = i + 1;
    }
    Graph::Tarjan(2 * n, node - 1, &graph);

    for(int i = 0; i < n; i++){
        if(node[i].col == node[i + n].col){[[unlikely]]
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    printf("POSSIBLE\n");
    for(int i = 0; i < n; i++){
        printf("%d ", node[i].col < node[i + n].col);
    }
}