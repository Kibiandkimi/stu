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

        static void build(Node *u, int l, int r, const int *data){
            u->l = l, u->r = r, u->tag = 0;
            if(l == r){
                u->mx = data[l];
                return;
            }

            int mid = (l + r) >> 1;
            u->ls = new Node, u->rs = new Node;
            build(u->ls, l, mid, data);
            build(u->rs, mid + 1, r, data);
            update(u);
        }

        static int query_(Node *u, int l, int r, int k){
            if(l <= u->l && u->r <= r){
                return u->mx - k;
            }else if(u->r < l || r < u->l){
                return u->mx;
            }

            int mx = 0;
            mx = max(mx, query_(u->ls, l, r, k));
            if(mx >= u->rs->mx){
                return mx;
            }
            mx = max(mx, query_(u->rs, l, r, k));

            return mx;
        }

    public:
        explicit SegTree(int n, const int *data){
            rt = new Node;
            build(rt, 1, n, data);
        }

        int query_(int l, int r, int val){
            return query_(rt, l, r, val);
        }
    };

    freopen("virus.in", "r", stdin);
    freopen("virus.out", "w", stdout);

    auto read = Tools::read;

    int n, m;
    read(m), read(n);

    static Virus virus[1000001];

    static int inc[1000001], sum[1000001];

    for(int i = 0; i < m; i++){
        read(virus[i].l), read(virus[i].r), read(virus[i].k);
        inc[virus[i].l - 1] += virus[i].k;
        inc[virus[i].r] -= virus[i].k;
    }

    sum[0] = inc[0];
    for(int i = 1; i < n; i++){
        sum[i] = sum[i - 1] + inc[i];
    }

    static SegTree tree(1000000, sum - 1);

    for(int i = 0; i < m; i++){
        printf("%d\n", tree.query_(virus[i].l, virus[i].r, virus[i].k));
    }

    fclose(stdin);
    fclose(stdout);
}