//
// Created by Kibi on 2024/5/14.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    auto read = [](int &x) {
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
    };

    class Tree {
        class Node {
        public:
            int id{};
            Node *fa{};
            vector<Node *> son;
        };

        vector<Node> node;

    public:
        explicit Tree(int n) : node(n) {
            for (int i = 0; i < n; i++) {
                node[i].id = i + 1;
            }
        }

        void add_edge(int u, int v) {
            node[u - 1].son.emplace_back(&node[v - 1]);
            node[v - 1].fa = &node[u - 1];
        }

        Node *get_node(int u) {
            return &node[u - 1];
        }
    };

    class SegTree {
        class Node {
        public:
            Node *ls{nullptr}, *rs{nullptr};
            int l{0}, r{0}, val{0}, dep{0};
        };

        Node *rt;

        static void update(Node *u) {
            u->val = u->ls->dep > u->rs->dep ? u->ls->val : u->rs->val;
            u->dep = max(u->ls->dep, u->rs->dep);
        }

    public:
        explicit SegTree(int n) {
            rt = new Node;
            using build = tuple<Node *, int, int>;// u, l, r
            stack<build> stk;
            stk.emplace(rt, 1, n);
            while (!stk.empty()) {
                auto [u, l, r] = stk.top();
                stk.pop();
                u->l = l, u->r = r, u->val = u->dep = 0;
                if (l != r) {
                    u->ls = new Node, u->rs = new Node;
                    stk.emplace(u->ls, l, (l + r) >> 1);
                    stk.emplace(u->rs, ((l + r) >> 1) + 1, r);
                }
            }
        }


        void modify(int u, int val, int dep) {
            stack<Node *> stk;
            Node *now = rt;
            while (now->l != now->r) {
                stk.emplace(now);
                if (u <= now->ls->r) {
                    now = now->ls;
                } else {
                    now = now->rs;
                }
            }
            now->val = val;
            now->dep = dep;
            while (!stk.empty()) {
                update(stk.top());
                stk.pop();
            }
        }

        int query(int l, int r) {
            using q = tuple<Node *, int>;// u, stage
            using Res = tuple<int, int>; // val, dep
            stack<q> stk;
            stack<Res> res;
            stk.emplace(rt, 0);
            while (!stk.empty()) {
                auto [u, sta] = stk.top();
                stk.pop();
                switch (sta) {
                    case 0:
                        if (l <= u->l && u->r <= r) {
                            res.emplace(u->val, u->dep);
                            break;
                        }
                        stk.emplace(u, 1);
                        if (l <= u->ls->r) {
                            stk.emplace(u->ls, 0);
                        }
                        if (r >= u->rs->l) {
                            stk.emplace(u->rs, 0);
                        }
                        break;
                    case 1: {
                        Res temp1{0, 0}, temp2{0, 0};
                        if (r >= u->rs->l) {
                            temp2 = res.top();
                            res.pop();
                        }
                        if (l <= u->ls->r) {
                            temp1 = res.top();
                            res.pop();
                        }
                        auto [v1, d1] = temp1;
                        auto [v2, d2] = temp2;
                        res.emplace(d1 > d2 ? v1 : v2, max(d1, d2));
                    } break;
                    default:
                        throw runtime_error("Error stage!");
                }
            }

            return get<0>(res.top());
        }
    };

    class HPD {
        class Node {
        public:
            Node *top, *fa, *son;
            int dfn, id, siz, dep;
        };

        vector<Node> node;

        SegTree segTree;

    public:
        HPD(int n, int rt, Tree &tree) : node(n), segTree(n) {
            for (int i = 0; i < n; i++) {
                node[i].id = i + 1;
                node[i].siz = 1;
            }

            // dfs1
            using dfs1 = tuple<Node *, Node *, int>;// u, fa, stage
            stack<dfs1> stk1;
            stk1.emplace(&node[rt - 1], nullptr, 0);
            node[rt - 1].dep = 1;
            while (!stk1.empty()) {
                auto [u, fa, sta] = stk1.top();
                stk1.pop();
                switch (sta) {
                    case 0:
                        stk1.emplace(u, fa, 1);
                        for (auto &v : tree.get_node(u->id)->son) {
                            node[v->id - 1].fa = u;
                            node[v->id - 1].dep = u->dep + 1;
                            stk1.emplace(&node[v->id - 1], u, 0);
                        }
                        break;
                    case 1:
                        fa ? fa->siz += u->siz : 0;
                        fa ? fa->son ? fa->son->siz > u->siz ? fa->son : fa->son = u : fa->son = u : nullptr;
                        break;
                    default:
                        throw runtime_error("Error stage!");
                }
            }

            // dfs2
            int cnt = 0;
            using dfs2 = tuple<Node *, Node *, int>;// u, top, stage
            stack<dfs2> stk2;
            stk2.emplace(&node[rt - 1], &node[rt - 1], 0);
            while (!stk2.empty()) {
                auto [u, top, sta] = stk2.top();
                stk2.pop();
                switch (sta) {
                    case 0:
                        u->top = top;
                        u->dfn = ++cnt;
                        stk2.emplace(u, top, 1);
                        u->son ? stk2.emplace(u->son, top, 0) : void();
                        break;
                    case 1:
                        for (auto &v : tree.get_node(u->id)->son) {
                            if (u->son == nullptr || v->id != u->son->id) {
                                stk2.emplace(&node[v->id - 1], &node[v->id - 1], 0);
                            }
                        }
                        break;
                    default:
                        throw runtime_error("Error stage!");
                }
            }
        }

        void modify(int u) {
            segTree.modify(node[u - 1].dfn, u, node[u - 1].dep);
        }

        int query(int u) {
            Node *now = &node[u - 1];
            int res = segTree.query(now->top->dfn, now->dfn);
            while (res == 0) {
                now = now->top->fa;
                res = segTree.query(now->top->dfn, now->dfn);
            }
            return res;
        }
    };

    int n, q;
    read(n), read(q);

    Tree tree(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        read(u), read(v);
        tree.add_edge(u, v);
    }

    HPD hpd(n, 1, tree);

    bool vis[n + 1];
    memset(vis, 0, sizeof vis);

    vis[1] = true;
    hpd.modify(1);

    while (q--) {
        auto readChar = [](int &x) {
            int c = getchar();
            while (c != 'C' && c != 'Q') {
                c = getchar();
            }
            x = c;
        };

        int type, u;
        readChar(type), read(u);
        if (type == 'C') {
            if (!vis[u]) {
                vis[u] = true;
                hpd.modify(u);
            }
        } else {
            printf("%d\n", hpd.query(u));
        }
    }
}

// 树剖维护最深标记