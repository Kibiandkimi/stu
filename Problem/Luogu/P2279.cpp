//
// Created by kibi on 23-11-8.
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

    static auto rand = [](int val){
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

    class Tree{
        class Node{
        public:
            int id{}, dep{};
            Node *fa{};
            vector<Node*> son;
        };

        Node *rt;
        Graph *graph;
        vector<Node> node;

        void dfs(Node *u, Node *fa){
            u->fa = fa;
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                Node *v = &node[i->v];
                if(v == fa){
                    continue;
                }
                v->dep = u->dep + 1;
                dfs(v, u);
            }
        }

    public:
        Tree(int n, int rt, Graph *graph):node(n), graph(graph){
            for(int i = 0; i < n; i++){
                node[i].id = i;
            }

            this->rt = &node[rt];
            this->rt->dep = 1;
            dfs(this->rt, nullptr);
        }
        friend class Work;
    };

    static int n;
    read({&n});

    static Graph graph(n);
    for(int i = 1; i < n; i++){
        int v;
        read({&v});
        v--;
        graph.add_edge(i, v, true);
    }

    int rt = rand(n);

    static Tree tree(n, rt, &graph);

    class Work{
    public:
        Work(){
            int order[n];
            for(int i = 0; i < n; i++){
                order[i] = i;
            }
            sort(order, order + n,
                 [](const int &x, const int &y){
                     return tree.node[x].dep > tree.node[y].dep;
                 });
            int ans = 0;
            bool vis[n];
            bool is[n];
            memset(vis, 0, sizeof vis);
            memset(is, 0, sizeof is);
            for(auto &i : order){
                if((tree.node[i].fa != nullptr and is[tree.node[i].fa->id]) or
                    (tree.node[i].fa != nullptr and tree.node[i].fa->fa != nullptr and is[tree.node[i].fa->fa->id])){
                    continue;
                }
                if(!vis[i]){
                    int raw = i;
                    if(tree.node[i].fa != nullptr and tree.node[i].fa->fa != nullptr){
                        i = tree.node[i].fa->fa->id;
                    }else if(tree.node[i].fa != nullptr){
                        i = tree.node[i].fa->id;
                    }
                    is[i] = true;
                    vis[i] = true;
                    ans++;
                    if(tree.node[i].fa != nullptr) {
                        vis[tree.node[i].fa->id] = true;
                        for (auto j = graph.begin(tree.node[i].fa->id); j; j = j->nxt) {
                            vis[j->v] = true;
                        }
                    }
                    i = raw;
                }
            }
            printf("%d\n", ans);
        }
    };

    Work{};
}