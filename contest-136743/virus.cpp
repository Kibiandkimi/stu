//
// Created by kibi on 23-10-3.
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

    class Virus{
    public:
        int l, r, k;
    };

    class SegTree{
        class Node{
        public:
            int l, r, mx, tag;
            Node *ls, *rs;
        };

        Node *rt;

        static void update(Node *u){
            u->mx = max(u->ls->mx, u->rs->mx);
        }

        static void build(Node *u, int l, int r){
            u->l = l, u->r = r, u->tag = 0;
            if(l == r){
                u->mx = 0;
                return;
            }

            int mid = (l + r) >> 1;
            u->ls = new Node, u->rs = new Node;
            build(u->ls, l, mid);
            build(u->rs, mid + 1, r);
            update(u);
        }

        static void update(Node *u, int k){
            u->tag += k;
            u->mx += k;
        }

        static void push_down(Node *u){
            update(u->ls, u->tag);
            update(u->rs, u->tag);
            u->tag = 0;
        }

        static void modify(Node *u, int l, int r, int k){
            if(l <= u->l && u->r <= r){
                update(u, k);
                return;
            }

            push_down(u);

            if(l <= u->ls->r){
                modify(u->ls, l, r, k);
            }
            if(r >= u->rs->l){
                modify(u->rs, l, r, k);
            }

            update(u);
        }

    public:
        explicit SegTree(int n){
            rt = new Node;
            build(rt, 1, n);
        }

        void modify(int l, int r, int k){
            modify(rt, l, r, k);
        }

        int query_(){
            return rt->mx;
        }
    };

    freopen("virus.in", "r", stdin);
    freopen("virus.out", "w", stdout);

    auto read = Tools::read;

    int n, m;
    read(m), read(n);

    Virus virus[m];
    SegTree tree(n);

    for(int i = 0; i < m; i++){
        read(virus[i].l), read(virus[i].r), read(virus[i].k);
        tree.modify(virus[i].l, virus[i].r, virus[i].k);
    }

    for(int i = 0; i < m; i++){
        tree.modify(virus[i].l, virus[i].r, -virus[i].k);
        printf("%d\n", tree.query_());
        tree.modify(virus[i].l, virus[i].r, virus[i].k);
    }

    fclose(stdin);
    fclose(stdout);
}