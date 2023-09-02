//
// Created by kibi on 2021/8/30.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, mxl, ans, num, ret, b[300005], d[300005], ta[300005], vis[300005], s[300005];
struct node{
    int v,w;
};
struct leng{
    int l,u,v,lca;
}len[300005];
vector<node> a[300005];
vector<node> q[300005];
int find(int x){
    if(b[x]!=x){
        b[x] = find(b[x]);
    }
    return b[x];
}
void tarjan(int u, int pre){
    int sa = a[u].size();
    for(int i = 0; i < sa; i++){
        int v = a[u][i].v;
        if(v == pre)continue;
        d[v] = d[u]+a[u][i].w;
        tarjan(v, u);
        ta[v] = a[u][i].w;
        int f1 = find(v), f2 = find(u);
        if(f1 != f2){
            b[f1] = find(f2);
        }
        vis[v] = 1;
    }
    int sq = q[u].size();
    for(int i = 0; i < sq; i++){
        if(vis[q[u][i].v]){
            int p = q[u][i].w;
            len[p].lca = find(q[u][i].v);
            len[p].l = d[u] + d[q[u][i].v] - 2*d[len[p].lca];
            mxl = max(mxl, len[p].l);
        }
    }
}
void f(int u, int pre){
    int sa = a[u].size();
    for(int i = 0; i < sa; i++){
        int v = a[u][i].v;
        if(v==pre)continue;
        f(v, u);
        s[u] += s[v];
    }
    if(s[u]==num&&ta[u]>ret){
        ret = ta[u];
    }
}
bool check(int x){
    memset(s, 0, sizeof(s));
    num = ret = 0;
    for(int i = 1; i <= m; i++){
        if(len[i].l > x){
            s[len[i].u]++;
            s[len[i].v]++;
            s[len[i].lca]-=2;
            num++;
        }
    }
    f(1, 0);
    if(mxl-ret>x){
        return 0;
    }
    return 1;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i < n; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back({v,w});
        a[v].push_back({u,w});
    }
    for(int i = 1; i <= n; i++){
        b[i] = i;
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        q[u].push_back({v,i});
        q[v].push_back({u,i});
        len[i].u = u;
        len[i].v = v;
    }
    tarjan(1, 0);
    int l = 0, r = mxl, mid;
    while(l <= r){
        mid = (l+r)/2;
        if(check(mid)){
            r = mid-1;
            ans = mid;
        }else{
            l = mid+1;
        }
    }
    cout << ans;
}


// 2023/9/2
// TODO not finish

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main() {

    const int N = 300000;
    mt19937 rnd(random_device{}());

    class Tools {
    public:
        static void read(int &x) {
            int s = 0, w = 1, c = getchar();
            while (c < '0' || '9' < c) {
                if (c == '-') {
                    w = -1;
                }
                c = getchar();
            }
            while ('0' <= c && c <= '9') {
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        }
    };

    class BinaryIndexedTree {// Binary Indexed Tree
        int data[N + 5]{}, n;

    public:
        BinaryIndexedTree(int n) : n(n) {}

        void update(int x, int v) {
            while (x <= n) {
                data[x] += v;
                x += x & (-x);
            }
        }

        int query(int x) {
            int res = 0;
            while (x) {
                res += data[x];
                x -= x & (-x);
            }
        }

        int sum(int l, int r){
            l--;
            int res = 0;
            while(r > l){
                res += data[r];
                r -= r & (-r);
            }
            while(l > r){
                res -= data[l];
                l -= l & (-l);
            }
            return res;
        }
    };

    class Graph {
        class Edge {
        public:
            int to, w;
            Edge *nxt;
        };
        Edge *head[N + 5], edge[2 * N + 5];
        int cnt;

    public:
        class HPD {// Heavy path decomposition
            class Node {
            public:
                int id, dep, siz, dfn;
                Node *fa, *heavy_son, *top;
            };
            Node node[N + 5]{};
            int dfn_to_id[N + 5]{}, rt;
            Graph *graph;
            BinaryIndexedTree bit;

            void build(Node *u, Node *fa) {
                u->fa = fa, u->siz = 1;
                u->dep = fa != nullptr ? fa->dep + 1 : 1;
                for (auto i = graph->head[u->id]; i != nullptr; i = i->nxt) {
                    if (fa == nullptr || i->to != fa->id) {
                        node[i->to].id = i->to;
                        build(&node[i->to], u);
                        u->siz += node[i->to].siz;
                        if (u->heavy_son == nullptr || u->heavy_son->siz < node[i->to].siz) {
                            u->heavy_son = &node[i->to];
                        }
                    }
                }
            }

            void decompose(Node *u, Node *top) {
                static int cnt = 0;
                u->top = top;
                u->dfn = ++cnt;
                dfn_to_id[cnt] = u->id;
                if (u->heavy_son != nullptr) {
                    decompose(u->heavy_son, top);

                    for (auto i = graph->head[u->id]; i != nullptr; i = i->nxt) {
                        if (i->to != u->heavy_son->id && i->to != u->fa->id) {
                            decompose(&node[i->to], &node[i->to]);
                        }
                    }
                }
            }

        public:
            HPD(Graph *graph, int rt, int n) : graph(graph), rt(rt), bit(n) {
                node[rt].id = rt;
                build(&node[rt], nullptr);
                decompose(&node[rt], &node[rt]);

                static int init_data[N + 5];
                static bool vis[N + 5];
                static queue<int> q;
                q.push(rt);
                vis[rt] = true;
                while (!q.empty()) {
                    static int u;
                    u = q.front(), q.pop();
                    for (auto i = graph->begin(u); i != nullptr; i = i->nxt) {
                        if (!vis[i->to]) {
                            if (node[i->to].dep < node[u].dep) {
                                init_data[u] = i->w;
                            } else {
                                init_data[i->to] = i->w;
                            }
                            q.push(i->to);
                        }
                    }
                }

                for (int i = 1; i <= n; i++) {
                    bit.update(i, init_data[dfn_to_id[i]]);
                }
            }

            int get_length(int _u, int _v){
                Node *u = &node[_u], *v = &node[_v];
                int ans = 0;

                while(u->top != v->top){
                    if(u->top->dep >= v->top->dep){
                        ans += bit.sum(u->top->dfn, u->dfn);
                        u = u->top->fa;
                    }else{
                        ans += bit.sum(v->top->dfn, v->dfn);
                        v = v->top->fa;
                    }
                }

                if(u->dfn <= v->dfn){
                    ans += bit.sum(u->dfn + 1, v->dfn);
                }else{
                    ans += bit.sum(v->dfn + 1, u->dfn);
                }

                return ans;
            }

            //            Node get(int id) {
            //                return node[id];
            //            }
            //
            //            int rnk(int x) {
            //                return dfn_to_id[x];
            //            }
        };

        void add_edge(int u, int v, int w, bool flag = false) {
            edge[++cnt] = {v, w, head[u]};
            head[u] = &edge[cnt];

            if (!flag) {
                return;
            }

            add_edge(v, u, w);
        }

        Edge *begin(int x) {
            return head[x];
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Graph graph;
    for (int i = 1; i <= n; i++) {
        static int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(u, v, w, true);
    }

    int root = (int) (rnd() % n + n) % n + 1;
    static Graph::HPD Hpd(&graph, root, n);

    for (int i = 1; i <= m; i++) {
        static int u, v, len;
        read(u), read(v);
        len = Hpd.get_length(u, v);

    }
}
 *
 * */