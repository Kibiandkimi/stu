//
// Created by kibi on 23-10-30.
//
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

        static int rand(int mx){
            return (int)(rnd() % mx + mx) % mx + 1;
        }
    };

    static auto rand = Tools::rand;

    class Graph{
        class Node{
        public:
            int v;
            Node *nxt;
        };

        vector<Node*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = false){
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

    class Tree{
    public:
        class Node{
        public:
            int id, siz, mx, mx_2, dpp;
            Node *fa, *heavy_son;
        };

        int n;
        Graph *graph;
        vector<Node> node;
        Node *rt;

        static void update(Node *u, int val){
            if(val >= u->mx){
                u->mx_2 = u->mx;
                u->mx = val;
            }else if(val > u->mx_2){
                u->mx_2 = val;
            }
        }

        void init(Node *u){
            u->siz = 1;
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                if(u->fa != &node[i->v]){
                    node[i->v].fa = u;
                    init(&node[i->v]);
                    u->siz += node[i->v].siz;
                    if(u->heavy_son == nullptr || u->heavy_son->siz < node[i->v].siz){
                        u->heavy_son = &node[i->v];
                    }
                    int val = node[i->v].siz <= (n >> 1) ? node[i->v].siz : node[i->v].mx;
                    update(u, val);
                }
            }
        }

        vector<bool> ans;

        void dfs(Node *u, Node *fa = nullptr){
            if(u->heavy_son != nullptr && u->heavy_son->siz > (n >> 1)){
                ans[u->id] = (u->heavy_son->siz - u->heavy_son->mx <= (n >> 1));
            }else if(n - u->siz > (n >> 1)){
                ans[u->id] = (n - u->siz - u->dpp <= (n >> 1));
            }else{
                ans[u->id] = true;
            }
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                Node *v = &node[i->v];
                if(v != fa){
                    int val = (n - u->siz > (n >> 1)) ? u->dpp : (n - u->siz);
                    v->dpp = max(v->dpp, val);
                    if(u->mx == v->siz){
                        v->dpp = max(v->dpp, u->mx_2);
                    }else{
                        v->dpp = max(v->dpp, u->mx);
                    }
                    dfs(v, u);
                }
            }
        }

    public:
        Tree(int n, Graph *graph):n(n), graph(graph), node(n + 1), ans(n + 1, false){
            for(int i = 1; i < node.size(); i++){
                node[i].id = i;
                node[i].mx = node[i].mx_2 = node[i].dpp = 0;
                node[i].heavy_son = nullptr;
            }

            rt = &node[rand(n)];
            rt->fa = nullptr;
            init(rt);
        };

        vector<bool> deal(){
            dfs(rt);
            return ans;
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    Graph graph(n);
    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
    }

    Tree tree(n, &graph);
    auto ans = tree.deal();

    for(int i = 1; i <= n; i++){
        if(ans[i]){
            printf("1 ");
        }else{
            printf("0 ");
        }
    }
    printf("\n");
}