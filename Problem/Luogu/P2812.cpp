//
// Created by kibi on 23-11-7.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());

    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

    auto rand = [](int val){
        return (int)((rnd() % val + val) % val);
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};
            flag ? add_edge(v, u) : void(0);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, col;
            bool vis;
        };

        int num_of_col;
        Node *rt;
        Graph *graph;
        vector<Node> node;

        void dfs(Node *u){
            static stack<int> stk;
            static int cnt;
            u->vis = true;
            u->dfn = u->low = ++cnt;
            stk.push(u->id);

            for(auto i = graph->begin(u->id); i; i = i->nxt){
                if(!node[i->v].dfn){
                    dfs(&node[i->v]);
                    u->low = min(u->low, node[i->v].low);
                }else if(node[i->v].vis){
                    u->low = min(u->low, node[i->v].dfn);
                }
            }

            if(u->low == u->dfn){
                int x;
                do{
                    x = stk.top();
                    stk.pop();
                    node[x].col = num_of_col;
                    node[x].vis = false;
                }while(x != u->id);
                num_of_col++;
            }
        }

    public:
        Tarjan(int n, int rt, int &res, Graph *graph, Graph **new_graph):node(n), graph(graph), num_of_col(0){
            for(int i = 0; i < n; i++){
                node[i].id = i;
                node[i].vis = false;
            }

            this->rt = &node[rt];

            dfs(this->rt);

            for(int i = 0; i < n; i++){
                if(!node[i].dfn){
                    dfs(&node[i]);
                }
            }

            *new_graph = new Graph(num_of_col);

            for(int i = 0; i < n; i++){
                for(auto j = graph->begin(i); j; j = j->nxt){
                    if(node[i].col != node[j->v].col){
                        (*new_graph)->add_edge(node[i].col, node[j->v].col);
                    }
                }
            }
            res = num_of_col;
        }
    };

    int n;
    read({&n});

    Graph graph(n);

    for (int i = 0; i < n; ++i){
        int v;
        read({&v});
        v--;
        while(v != -1){
            graph.add_edge(i, v);
            read({&v});
            v--;
        }
    }

    int num_of_col;
    Graph *new_graph;
    Tarjan(n, rand(n), num_of_col, &graph, &new_graph);

    bool in[num_of_col], out[num_of_col];
    memset(in, 0, sizeof in), memset(out, 0, sizeof out);
    for(int i = 0; i < num_of_col; i++){
        for(auto j = new_graph->begin(i); j; j = j->nxt){
            in[j->v] = true;
            out[i] = true;
        }
    }

    int sum_in = 0, sum_out = 0;
    for(int i = 0; i < num_of_col; i++){
        sum_in += !in[i];
        sum_out += !out[i];
    }

    if(num_of_col == 1){
        printf("1\n0\n");
    }else{
        printf("%d\n%d\n", sum_in, max(sum_in, sum_out));
    }
}