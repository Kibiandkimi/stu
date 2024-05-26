//
// Created by kibi on 2021/8/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,bc[10005],d[10005],fa[10005][30],w[10005][30],vis[10005];
struct node{
    int v,w;
};
struct side{
    int u,v,w;
};
int find(int x){
    if(bc[x]!=x){
        bc[x] = find(bc[x]);
    }
    return bc[x];
}
vector<side> ra;
vector<node> pa[10005];
bool cmp(const side &a, const side &b){
    return a.w > b.w;
}
void pre(int x, int f, int s){
    d[x] = d[f]+1;
    fa[x][0] = f;
    w[x][0] = s;
    vis[x] = 1;
    for(int i = 0; i <= 20; i++){
        fa[x][i+1] = fa[fa[x][i]][i];
        w[x][i+1] = min(w[x][i],w[fa[x][i]][i]);
    }
    int sa = pa[x].size();
    for(int i = 0; i < sa; i++){
        if(vis[pa[x][i].v])continue;
        pre(pa[x][i].v, x, pa[x][i].w);
    }
}
int lca(int u, int v){
    if(find(u)!=find(v))return -1;
    if(d[u]>d[v]){
        swap(u,v);
    }
    int s = 1e9;
    for(int i = 20; i >= 0; i--){
        if(d[fa[v][i]]>=d[u]){
            s = min(s, w[v][i]);
            v = fa[v][i];
        }
    }
    if(u == v)return s;
    for(int i = 20; i >= 0; i--){
        if(fa[u][i]!=fa[v][i]){
            s = min(s, min(w[u][i], w[v][i]));
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    s = min(s, min(w[u][0], w[v][0]));
    return s;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        ra.push_back({u,v,w});
    }
    for(int i = 1; i <= n; i++){
        bc[i] = i;
    }
    int sr = ra.size();
    sort(ra.begin(), ra.end(), cmp);
    for(int i = 0; i < sr; i++){
        int tu = ra[i].u, tv = ra[i].v;
        if(find(tu)!=find(tv)){
            int tw = ra[i].w;
            pa[tu].push_back({tv, tw});
            pa[tv].push_back({tu, tw});
            bc[find(tu)] = find(tv);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            pre(i, 0, 1e9);
            fa[i][0] = i;
            w[i][0] = 1e9;
        }
    }
    int q;
    cin >> q;
    while(q--){
        int u,v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u,v));
    }
}

// 2023/9/10

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 10000, M = 50000;

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

    class Bcj{
        Bcj *fa;

    public:
        int id;

        Bcj():fa(this), id(0){}
        explicit Bcj(int id):fa(this), id(id){}

        Bcj* find(){
            if(this != fa){
                fa = fa->find();
            }
            return fa;
        }

        void update(Bcj* v){
            fa = v->find();
        }
    };

    class Graph{
        class Edge{
        public:
            int v{}, w{};
            Edge *nxt{nullptr};
        };

        Edge *head[N + 5]{nullptr};
        Edge edge[2 * N + 5];
        int cnt{0};

    public:
        void add_edge(int u, int v, int w, bool flag = false){
            edge[++cnt] = {v, w, head[u]};
            head[u] = &edge[cnt];

            if(!flag){
                return;
            }

            add_edge(v, u, w);
        }

        class Lca{
            int dep[N + 5]{0}, fo[N + 5][21]{0}, mn[N + 5][21]{0}, n;
            Graph *graph;

            void dfs(int u, int fa){
                dep[u] = dep[fa] + 1, fo[u][0] = fa;
                for(int i = 1; i <= 20; i++){
                    fo[u][i] = fo[fo[u][i - 1]][i - 1];
                    mn[u][i] = min(mn[u][i-1], mn[fo[u][i - 1]][i - 1]);
                }

                for(auto i = graph->head[u]; i; i = i->nxt){
                    if(i->v != fa){
                        mn[i->v][0] = i->w;
                        dfs(i->v, u);
                    }
                }
            }

        public:
            Lca(Graph *graph, int n):graph(graph), n(n){}

            void init_lca(){
                for(int i = 1; i <= n; i++){
                    if(!dep[i]){
                        dfs(i, 0);
                    }
                }
            }

            int query(int x, int y, int inf = 1e9){
                if(dep[x] > dep[y]){
                    swap(x, y);
                }

                int res = inf;

                for(int i = 20; i >= 0; i--){
                    if(dep[fo[y][i]] >= dep[x]){
                        res = min(res, mn[y][i]);
                        y = fo[y][i];
                    }
                }

                if(x == y){
                    return res;
                }

                for(int i = 20; i >= 0; i--){
                    if(fo[y][i] != fo[x][i]){
                        res = min(res, mn[y][i]);
                        y = fo[y][i];
                        res = min(res, mn[x][i]);
                        x = fo[x][i];
                    }
                }

                res = min({res, mn[y][0], mn[x][0]});
                return res;
            }
        };


    };

    class Edge{
    public:
        int u, v, w;

        static bool cmp(const Edge &a, const Edge &b){
            return a.w > b.w;
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Edge edge[M + 5];
    for(int i = 1; i <= m; i++){
        int u, v, w;
        read(u), read(v), read(w);
        edge[i] = {u, v, w};
    }

    sort(edge + 1, edge + 1 + m, Edge::cmp);

    static Bcj bcj[N + 5];
    for(int i = 1; i <= n; i++){
        bcj[i].id = i;
    }

    static Graph graph;
    for(int i = 1; i <= m; i++){
        auto [u, v, w] = edge[i];
        if(bcj[u].find() != bcj[v].find()){
            graph.add_edge(u, v, w, true);
            bcj[u].find()->update(&bcj[v]);
        }
    }

    Graph::Lca lca(&graph, n);
    lca.init_lca();

    int q;
    read(q);
    while(q--){
        int x, y;
        read(x), read(y);

        if(bcj[x].find() != bcj[y].find()){
            printf("%d\n", -1);
            continue;
        }

        printf("%d\n", lca.query(x, y));
    }
}
 *
 * */