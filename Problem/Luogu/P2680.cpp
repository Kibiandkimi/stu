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


// 2023/9/3

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
        explicit BinaryIndexedTree(int n) : n(n) {}

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
            return res;
        }

        int sum(int l, int r, bool flag = false){
            if(flag){
                return quick_sum(l, r);
            }else{
                return query(r) - query(l - 1);
            }
        }

        int quick_sum(int l, int r){
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

    class SegTree{
        class Node{
        public:
            int l, r, mx, tag;
            Node *ls, *rs;
        };
        Node node[4 * N + 5]{};

        void build(Node *u, int l, int r, const int *data){
            static int cnt = 1;
            u->l = l, u->r = r;
            if(l == r){
                u->mx = data == nullptr ? 0 : data[l];
                return;
            }
            int mid = (l + r) / 2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid, data);
            build(u->rs, mid + 1, r, data);
            u->mx = max(u->ls->mx, u->rs->mx);
        }

        static void update(Node *u, int val){
            u->tag = max(u->tag, val);
            u->mx = max(u->mx, val);
        }

        static void push_down(Node *u){
            if(u->tag){
                update(u->ls, u->tag);
                update(u->rs, u->tag);
                u->tag = 0;
            }
        }

        static void modify(Node *u, const int l, const int r, const int v){
            if(l <= u->l && u->r <= r){
                update(u, v);
                return;
            }

            push_down(u);

            if(l <= u->ls->r){
                modify(u->ls, l, r, v);
            }
            if(r >= u->rs->l){
                modify(u->rs, l, r, v);
            }

            u->mx = max(u->ls->mx, u->rs->mx);
        }

    public:
        explicit SegTree(int n, const int *data = nullptr){
            build(&node[1], 1, n, data);
        }

        void modify(int l, int r, int v){
            if(l > r){
                return;
            }
            modify(&node[1], l, r, v);
        }

        int query(int x){
            Node *u = &node[1];
            while(u->l < u->r){
                push_down(u);
                if(x <= u->ls->r){
                    u = u->ls;
                }else{
                    u = u->rs;
                }
            }
            return u->mx;
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
                        if (i->to != u->heavy_son->id && (u->fa == nullptr || i->to != u->fa->id) ) {
                            decompose(&node[i->to], &node[i->to]);
                        }
                    }
                }
            }

            friend class Work;

        public:
            HPD(Graph *graph, int rt, int n) : graph(graph), rt(rt), bit(n) {
                node[rt].id = rt;
                build(&node[rt], nullptr);
                decompose(&node[rt], &node[rt]);

                static int init_data[N + 5];
                static bool vis[N + 5], flag;
                static queue<int> q;

                flag ? memset(vis, 0, sizeof vis) : nullptr;

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
                            vis[i->to] = true;
                            q.push(i->to);
                        }
                    }
                }

                flag = true;

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

            class Data{
            public:
                class Interval{
                public:
                    int l, r;

                    static bool cmp(const Interval &a, const Interval &b){
                        return a.l < b.l;
                    }

                    explicit Interval(int l = 0, int r = 0):l(l), r(r){}
                };
                vector<Interval> data;
            };

            Data query_path(int _u, int _v){
                Data res;
                Node *u = &node[_u], *v = &node[_v];

                while(u->top != v->top){
                    if(u->top->dep >= v->top->dep){
                        res.data.emplace_back(u->top->dfn, u->dfn);
                        u = u->top->fa;
                    }else{
                        res.data.emplace_back(v->top->dfn, v->dfn);
                        v = v->top->fa;
                    }
                }

                if(u->dfn <= v->dfn){
                    res.data.emplace_back(u->dfn + 1, v->dfn);
                }else{
                    res.data.emplace_back(v->dfn + 1, u->dfn);
                }

                return res;
            }

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
    for (int i = 1; i < n; i++) {
        static int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(u, v, w, true);
    }

    static int root = (int) (rnd() % n + n) % n + 1, mx_u, mx_v, mx;
    static Graph::HPD Hpd(&graph, root, n);
    static SegTree tree(n);

    for (int i = 1; i <= m; i++) {
        static int u, v, len;
        read(u), read(v);
        len = Hpd.get_length(u, v);
        auto res = Hpd.query_path(u, v);
        sort(res.data.begin(), res.data.end(), Graph::HPD::Data::Interval::cmp);
        if(res.data.front().l > 1){
            tree.modify(1, res.data[0].l - 1, len);
        }
        if(res.data.back().r < n){
            tree.modify(res.data.back().r + 1, n, len);
        }

        for(int j = 0; j < res.data.size() - 1; j++){
            tree.modify(res.data[j].r + 1, res.data[j + 1].l - 1, len);
        }

        if(len > mx){
            mx_u = u, mx_v = v, mx = len;
        }
    }

    class Work{
    public:
        int operator () (){
            int ans = 1e9;

            Graph::HPD::Node *u = &Hpd.node[mx_u], *v = &Hpd.node[mx_v];

            if(u == v){
                return 0;
            }

            if(u->dep < v->dep){
                swap(u, v);
            }
            while(u->dep != v->dep){
                ans = min(ans, max(mx - Hpd.bit.sum(u->dfn, u->dfn), tree.query(u->dfn)));
                u = u->fa;
            }
            while(u != v){
                if(u->dep > v->dep){
                    ans = min(ans, max(mx - Hpd.bit.sum(u->dfn, u->dfn), tree.query(u->dfn)));
                    u = u->fa;
                }else{
                    ans = min(ans, max(mx - Hpd.bit.sum(v->dfn, v->dfn), tree.query(v->dfn)));
                    v = v->fa;
                }
            }

            return ans;
        }
    };

    int ans = Work{}();

    printf("%d\n", ans);

}
 *
 * */