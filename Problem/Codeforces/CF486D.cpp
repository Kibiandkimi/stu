//
// Created by kibi on 23-11-8.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static int Mod = 1000000007;
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

    static auto add = [](int &x, int y){
        x = (x + y) >= Mod ? x + y - Mod : x + y;
    };

    static auto sub = [](int x, int y){
        return (int)((long long)x * y % Mod);
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
            int id{}, val{};
            Node *fa{};
            vector<Node*> son;
        };

        Node *rt;
        Graph *graph;
        vector<Node> node;

        void dfs(Node *u, Node *fa){
            u->fa = fa;
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                if(&node[i->v] == fa){
                    continue;
                }
                u->son.emplace_back(&node[i->v]);
                dfs(u->son.back(), u);
            }
        }

    public:
        Tree(int n, int rt, Graph *graph, const int *val):node(n), graph(graph){
            for(int i = 0; i < n; i++){
                node[i].id = i;
                node[i].val = val[i];
            }

            this->rt = &node[rt];
            dfs(this->rt, nullptr);
        }

        friend class Work;
    };

    static int d, n;
    read({&d, &n});

    int raw_val[n];
    for(auto &i : raw_val){
        read({&i});
    }

    static Graph graph(n);
    for(int i = 1; i < n; i++){
        int u, v;
        read({&u, &v});
        u--, v--;
        graph.add_edge(u, v, true);
    }

    static Tree tree(n, rand(n), &graph, raw_val);

    static int *val = raw_val;

    class Work{
        int ans{};
        Tree::Node *rt;
        vector<int> dp;
        void dfs(Tree::Node *u, Tree::Node *fa){
            dp[u->id] = 1;
            for(auto i = graph.begin(u->id); i; i = i->nxt){
                auto v = &tree.node[i->v];
                if(v == fa){
                    continue;
                }
                if((rt->val > v->val || (rt->val == v->val && rt->id > v->id)) && rt->val - v->val <= d){
                    dfs(v, u);
                    add(dp[u->id], sub(dp[u->id], dp[v->id]));
                }
            }
        }

    public:
        Work():dp(n){
            for(int i = 0; i < n; i++){
                rt = &tree.node[i];
                dfs(rt, nullptr);
                add(ans, dp[i]);
                dp.clear();
                dp.resize(n);
            }
            printf("%d\n", ans);
        }
    };

    Work{};
}