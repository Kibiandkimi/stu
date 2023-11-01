//
// Created by kibi on 23-11-1.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());

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

        static int deal(int x){
            return (int)((rnd() % x + x) % x + 1);
        }
    };

    class Graph{
        class Node{
        public:
            int v;
            Node *nxt;
        };

        vector<Node*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = true){
            head[u] = new Node{v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Node* begin(int u){
            return head[u];
        }
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, bel;
            bool vis;
        };

        Graph *graph;
        vector<int> num;
        vector<Node> node;

        void dfs(Node *u, Node *fa){
            static int cnt = 0, p = 0;
            static stack<int> stk;
            u->dfn = u->low = ++cnt;
            u->vis = true;
            stk.push(u->id);
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                auto v = &node[i->v];
                if(v == fa){
                    continue;
                }
                if(!v->dfn){
                    dfs(v, u);
                    u->low = min(u->low, v->low);
                }else if(v->vis){
                    u->low = min(u->low, v->dfn);
                }
            }
            if(u->dfn == u->low){
                ++p;
                num.emplace_back(0);
                int x;
                do {
                    x = stk.top();
                    node[x].vis = false;
                    node[x].bel = p;
                    num[p]++;
                } while(x != u->id);
            }

        }

    public:
        Tarjan(int n, int rt, Graph *graph):graph(graph), num(1, 0), node(n + 1){
            for(int i = 1; i <= n; i++){
                node[i].id = i;
                node[i].vis = false;
            }
            dfs(&node[rt], nullptr);
        }
    };

    auto rand = Tools::deal;
    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Graph graph(n);
    for(int i = 0; i < m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
    }

    int rt = rand(n);
    Tarjan tarjan(n, rt, &graph);


}