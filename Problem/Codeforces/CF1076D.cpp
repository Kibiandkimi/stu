//
// Created by kibi on 23-11-5.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;

    auto read_ = [](initializer_list<int*> x){
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
            int id, v, w;
            Edge *nxt;
        };

        int cnt;
        vector<Edge*> head;

    public:
        explicit Graph(int n):cnt(1), head(n + 1, nullptr){}

        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{(++cnt) >> 1 ,v, w, head[u]};

            flag ? add_edge(v, u, w) : (void)0;
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    class Tree{
        class Node{
        public:
            int id{0};
            Node *fa{nullptr};
            Graph son{0};
        };

        int n;
        Node *rt;
        vector<Node> node;
        vector<int> ans;

        void dfs(Node *u){
            for(auto i = u->son.begin(0); i; i = i->nxt){
                ans.emplace_back(i->id);
                dfs(&node[i->v]);
            }
        }

    public:
        Tree(int n, int rt):n(n), node(n + 1){
            for(int i = 1; i <= n; i++){
                node[i].id = i;
            }

            this->rt = &node[rt];
        }

        void deal(Graph *graph){
            ll raw_dis[n];
            int raw_tem_w[n];
            int raw_tem_id[n];
            bool raw_vis[n];
            ll *dis = raw_dis - 1;
            int *tem_w = raw_tem_w - 1;
            int *tem_id = raw_tem_id - 1;
            bool *vis = raw_vis - 1;
            memset(raw_vis, 0, sizeof raw_vis),
                    memset(raw_dis, 0x3f, sizeof raw_dis);
            class Node{
            public:
                int dis, id;

                class Cmp{
                public:
                    bool operator () (const Node &u, const Node &v){
                        return u.dis > v.dis;
                    }
                };

                Node(int dis, int id):dis(dis), id(id){}
            };
            priority_queue<Node, vector<Node>, Node::Cmp> q;
            q.emplace(0, rt->id);
            dis[rt->id] = 0, vis[rt->id] = true;
            while(!q.empty()){
                auto now = q.top();
                int u = now.id;
                q.pop();
                vis[u] = false;
                for(auto i = graph->begin(u); i; i = i->nxt){
                    ll val = dis[u] + i->w;
                    int v = i->v;
                    if(dis[v] > val){
                        dis[v] = val;
                        if(!vis[v]){
                            q.emplace(dis[v], v);
                            vis[v] = true;
                        }
                        tem_id[v] = i->id;
                        tem_w[v] = i->w;
                        node[v].fa = &node[u];
                    }
                }
            }

            for(int i = 2; i <= n; i++){
                node[i].fa->son.add_edge(0, i, tem_w[i]);
                node[i].fa->son.begin(0)->id = tem_id[i];
            }
        }

        vector<int>* work(int k){
            dfs(rt);
            ans.resize(min(k, n - 1));
            return &ans;
        }
    };

    int n, m, k;
    read_({&n, &m, &k});

    Graph graph(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        read_({&u, &v, &w});
        graph.add_edge(u, v, w, true);
    }

    Tree tree(n, 1);
    tree.deal(&graph);
    auto ans = tree.work(k);

    printf("%d\n", (int)ans->size());
    for(auto &i : *ans){
        printf("%d ", i);
    }
    printf("\n");
}