//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main() {

    const int N = 500000, M = 500000, Q = 500000;

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

    class Node {
    public:
        int id, l, r;

        static bool cmp(Node &a, Node &b) {
            return a.l > b.l;
        }

        static bool cmp_by_id(Node &a, Node &b){
            return a.id < b.id;
        }
    };

    class Question : public Node {
    public:
        bool ans{};
        Question() = default;
        Question(int id, int l, int r) : Node({id, l, r}) {}
    };

    class SegTree {
        class Node {
        public:
            int l, r, mx, tag;
            Node *ls, *rs;
        };

        Node node[4 * N + 5]{};

        static void push_down(Node *u) {
            if (u->tag) {
                if (u->tag < u->ls->mx) {
                    u->ls->tag = u->tag;
                    u->ls->mx = u->tag;
                }
                if (u->tag < u->rs->mx) {
                    u->rs->tag = u->tag;
                    u->rs->mx = u->tag;
                }
                u->tag = 0;
            }
        }

        void build(Node *u, int l, int r) {
            static int cnt = 1;
            u->l = l, u->r = r;
            if (l == r) {
                u->mx = node[1].r+1;
                u->tag = 0;
                return;
            }
            int mid = (l + r) / 2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid);
            build(u->rs, mid + 1, r);
            u->mx = max(u->ls->mx, u->rs->mx);
        }

        void change(Node *u, const int l, const int r, const int v) {
            if (u->mx <= v) {
                return;
            }
            if (l <= u->l && u->r <= r) {
                u->tag = v;
                u->mx = v;
                return;
            }
            push_down(u);
            if(l <= u->ls->r){
                change(u->ls, l, r, v);
            }
            if(r >= u->rs->l){
                change(u->rs, l, r, v);
            }
            u->mx = max(u->ls->mx, u->rs->mx);
        }

        int query(Node *u, const int l, const int r){
            if(l <= u->l && u->r <= r){
                return u->mx;
            }
            push_down(u);
            int res = 0;
            if(l <= u->ls->r){
                res = max(res, query(u->ls, l, r));
            }
            if(r >= u->rs->l){
                res = max(res, query(u->rs, l, r));
            }
            return res;
        }

    public:
        explicit SegTree(int n) {
            build(&node[1], 1, n);
        }

        void change(const int l, const int r, const int v) {
            change(&node[1], l, r, v);
        }

        int query(const int l, const int r){
            return query(&node[1], l, r);
        }
    };

    auto read = Tools::read;

    int n, m, q;
    read(n), read(m), read(q);

    static Node node[M + 5];

    for (int i = 1; i <= m; i++) {
        int l, r;
        read(l), read(r);
        node[i] = {i, l, r};
    }

    sort(node + 1, node + 1 + m, Node::cmp);

    static Question question[Q + 5];

    for (int i = 1; i <= q; i++) {
        int l, r;
        read(l), read(r);
        question[i] = {i, l, r};
    }

    sort(question + 1, question + 1 + q, Question::cmp);

    static SegTree tree(n);

    for (int i = 1, cnt_of_node = 1; i <= q; i++) {
        while (node[cnt_of_node].l >= question[i].l && cnt_of_node <= m) {
            tree.change(node[cnt_of_node].l, node[cnt_of_node].r, node[cnt_of_node].r);
            cnt_of_node++;
        }
        question[i].ans = (tree.query(question[i].l, question[i].r) <= question[i].r);
    }

    sort(question + 1, question + 1 + q, Question::cmp_by_id);

    for(int i = 1; i <= q; i++){
        question[i].ans ? printf("YES\n") : printf("NO\n");
    }
}