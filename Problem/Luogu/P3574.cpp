//
// Created by kibi on 23-11-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    class Tree{
        class Node{
        public:
            int id, val, tim, w; // val->self install time, time->siz, w->mx time
            Node *fa;
            vector<Node*> son;
        };

        Node *rt;
        vector<Node*> node;
        Graph *graph;

        void dfs(Node *u, Node *fa){
            u->tim = 0;
            if(fa) {
                u->w = u->val;
            }
            u->fa = fa;
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                Node *v = node[i->v];
                if(v == fa){
                    continue;
                }
                u->son.emplace_back(v);
                dfs(v, u);
            }
            sort(u->son.begin(), u->son.end(), [](const Node *a, const Node *b){
                return a->tim - a->w < b->tim - b->w;
            });
            for(auto &i : u->son){
                u->w = max(u->w, i->w + u->tim + 1);
                u->tim += i->tim + 2;
            }
        }

    public:
        Tree(int n, int rt, const int *val, Graph *graph):graph(graph), node(n){
            for(int i = 0; i < n; i++){
                node[i] = new Node{i, val[i]};
            }

            this->rt = node[rt];

            dfs(this->rt, nullptr);
        }

        int get_ans(){
            return max(rt->w, rt->tim + rt->val);
        }
    };

    int n;
    read({&n});

    int w[n];
    for(auto &i : w){
        read({&i});
    }

    Graph graph(n);
    for(int i = 1; i < n; i++){
        int u, v;
        read({&u, &v});
        u--, v--;
        graph.add_edge(u, v, true);
    }

    Tree tree(n, 0, w, &graph);
    int ans = tree.get_ans();
    printf("%d\n", ans);
}