//
// Created by kibi on 23-11-7.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());
    static const int Mod = 998244353;

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
            int v, w;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{v, w, head[u]};
            flag ? add_edge(v, u, w) : void(0);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    class DSU{
    public:
        int id;
        DSU* fa;
        DSU* find(){
            if(fa != this){
                fa = fa->find();
            }
            return fa;
        }

        DSU():id(0), fa(this){}
    };

    class Tree{
        class Node{
        public:
            int id{}, siz{}, dep{}, val_to_fa{};
            Node *fa{};
            vector<Node*> son;
            Node *anc[20]{};
            int mx_val[20]{};

            void init_lca(){
                anc[0] = fa == nullptr ? this : fa;
                mx_val[0] = val_to_fa;
                for(int i = 1; i < 20; i++){
                    anc[i] = anc[i - 1]->anc[i - 1];
                    mx_val[i] = max(mx_val[i - 1], anc[i - 1]->mx_val[i - 1]);
                }
            }
        };

        Node *rt;
        Graph *graph;
        vector<Node> node;

        void dfs(Node *u, Node *fa){
            u->fa = fa;
            u->init_lca();
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                if(&node[i->v] != fa){
                    u->son.emplace_back(&node[i->v]);
                    u->son.back()->val_to_fa = i->w;
                    u->son.back()->dep = u->dep + 1;
                    dfs(u->son.back(), u);
                }
            }
        }

    public:
        Tree(int n, int rt, Graph *graph):node(n), graph(graph){
            for(int i = 0; i < n; i++){
                node[i].id = i;
            }

            this->rt = &node[rt];
            this->rt->val_to_fa = 0;
            this->rt->dep = 1;

            dfs(this->rt, nullptr);
        }

        int query(int u, int v){
            Node *x = &node[u], *y = &node[v];
            if(x->dep > y->dep){
                swap(x, y);
            }

            int res = 0;

            for(int i = 19; i >= 0; i--){
                if(y->anc[i]->dep >= x->dep){
                    res = max(res, y->mx_val[i]);
                    y = y->anc[i];
                }
            }

            if(y == x){
                return res;
            }

            for(int i = 19; i >= 0; i--){
                if(y->anc[i] != x->anc[i]){
                    res = max({res, y->mx_val[i], x->mx_val[i]});
                    x = x->anc[i];
                    y = y->anc[i];
                }
            }

            return max({res, x->val_to_fa, y->val_to_fa});
        }
    };

    int n, m;
    read({&n, &m});

    class Edge{
    public:
        int id, u, v, w;
    };
    Edge edge[m];
    for(auto &i : edge){
        static int cnt;
        read({&i.u, &i.v, &i.w});
        i.u--, i.v--;
        i.id = cnt++;
    }

    sort(edge, edge + m, [](const Edge &a, const Edge &b){return a.w < b.w;});

    Graph graph(n);
    DSU node_set[n];
    for(int i = 0; i < n; i++){
        node_set[i].id = i;
    }

    using ll = long long;

    ll res = 0;

    for(auto &i : edge){
        static int cnt;
        if(node_set[i.u].find() != node_set[i.v].find()){
            node_set[i.u].find()->fa = node_set[i.v].find();
            graph.add_edge(i.u, i.v, i.w, true);
            cnt++;
            res += i.w;
        }
        if(cnt == n - 1){
            break;
        }
    }

    int rt = rand(n);
    Tree tree(n, rt, &graph);

    sort(edge, edge + m, [](const Edge &a, const Edge &b){return a.id < b.id;});
    for(auto &i : edge){
        printf("%lld\n", res + i.w - tree.query(i.u, i.v));
    }
}