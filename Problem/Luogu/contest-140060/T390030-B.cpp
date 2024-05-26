//
// Created by kibi on 23-10-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    static int n, m;

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        Graph():head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    class Node{
    public:
        int id, deg;

        Node(int id, int deg):id(id), deg(deg){}
    };

    auto read = Tools::read;

    read(n), read(m);

    int deg_[n];
    memset(deg_, 0, sizeof deg_);
    Graph graph;
    for(int i = 0; i < m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
        deg_[u - 1]++;
        deg_[v - 1]++;
    }

    static int *deg = deg_ - 1;

    class Cmp{
    public:
        bool operator() (const Node &a, const Node &b){
            return a.deg > b.deg;
        }
    };

    priority_queue<Node, vector<Node>, Cmp> q;

    for(int i = 0; i < n; i++){
        q.emplace(i + 1, deg[i + 1]);
    }

    bool vis[n];
    memset(vis, 0, sizeof vis);

    int ans = 0;

    while(!q.empty()){
        auto u = q.top();
        q.pop();
        if(vis[u.id - 1]){
            continue;
        }
        ans = max(ans, u.deg);
        vis[u.id - 1] = true;
        for(auto i = graph.begin(u.id); i; i = i->nxt){
            if(!vis[i->v - 1]){
                deg[i->v]--;
                q.emplace(i->v, deg[i->v]);
            }
        }
        deg[u.id] = 0;
    }

    printf("%d\n", ans);
}