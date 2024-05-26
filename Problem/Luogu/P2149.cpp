//
// Created by kibi on 23-7-29.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1500, M = 300000;

void read(int&);

int main(){

    class Graph{
        int head[N + 5], nxt[2 * M + 5], to[2 * M + 5], w[2 * M + 5], cnt;

    public:

        class Node{
        public:
            int u, w;

            Node(int u, int w) : u(u), w(w){}

            class Cmp{
            public:
                bool operator() (const Node &a, const Node &b) const{
                    return a.w > b.w;
                }
            };
        };

        void add_edge(int u, int v, int _w, bool flag = false){
            to[++cnt] = v;
            nxt[cnt] = head[u];
            head[u] = cnt;
            w[cnt] = _w;

            if(!flag){
                return;
            }

            to[++cnt] = u;
            nxt[cnt] = head[v];
            head[v] = cnt;
            w[cnt] = _w;
        }

        int begin(int x){
            return head[x];
        }

        int next(int x){
            return nxt[x];
        }

        int get(int x){
            return to[x];
        }

        int get_w(int x){
            return w[x];
        }
    };

    class Func{
    public:
        static void multi_read(int x, int *a){
            for(int i = 0; i < x; i++){
                read(a[i]);
            }
        }
    };

    // pre work

    static Graph graph;

    int n, m;
    read(n), read(m);

    int tem[4];
    Func::multi_read(4, tem);
    auto [Ex, Ey, Wx, Wy] = tem;

    for(int i = 1; i <= m; i++){
        Func::multi_read(3, tem);
        auto [u, v, w, ignore] = tem;
        graph.add_edge(u, v, w, true);
    }

    // get shortest graph

    static int dis[4][N + 5];

    memset(dis, 0x3f, sizeof dis);

    for(int id = 0; id < 4; id++){

        static int begin[4] = {Ex, Ey, Wx, Wy};
        static bool vis[N + 5];
        static priority_queue<Graph::Node, vector<Graph::Node>, Graph::Node::Cmp> q;

        int *d = dis[id];

        q.emplace(begin[id], 0);
        dis[id][begin[id]] = 0;

        while(!q.empty()){
            auto [u, w] = q.top();
            q.pop();
            if(vis[u]){
                continue;
            }
            vis[u] = true;
            for(int i = graph.begin(u); i; i = graph.next(i)){
                int v = graph.get(i), _w = graph.get_w(i);
                if(d[v] > w + _w){
                    d[v] = w + _w;
                    q.emplace(v, d[v]);
                }
            }
        }

        if(id == 3){
            continue;
        }

        memset(vis, 0, sizeof vis);
    }

    // get the longest line

    int ans;

    for(int id = 0; id < 2; id++){

        static Graph short_graph;
        static bool vis[N + 5];
        static int deg[N + 5], len[N + 5];
        static queue<int> q;

        // new graph

        for(int i = 1; i <= n; i++){
            for(int j = graph.begin(i); j; j = graph.next(j)){
                int v = graph.get(j), w = graph.get_w(j);
                if(dis[0][i] + w + dis[1][v] == dis[0][Ey] &&
                    dis[2+id][i] + w + dis[3-id][v] == dis[2][Wy]){ // 2+id, 3-id, low readability
                    short_graph.add_edge(i, v, w);
                    deg[v]++;
                }
            }
        }

        // topo

        for(int i = 1; i <= n; i++){
            if(!deg[i]){
                q.push(i);
            }
        }

        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int i = short_graph.begin(u); i; i = short_graph.next(i)){
                int v = short_graph.get(i), w = short_graph.get_w(i);
                deg[v]--;
                len[v] = max(len[v], len[u] + w);
                if(!deg[v]){
                    q.push(v);
                }
            }
        }

        for(int i = 1; i <= n; i++){
            ans = max(ans, len[i]);
        }

        if(id == 1){
            continue;
        }

        short_graph = Graph();
        memset(vis, 0, sizeof vis);
        memset(len, 0, sizeof len);

    }

    printf("%d\n", ans);

}

void read(int &x){
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