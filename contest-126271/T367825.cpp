//
// Created by kibi on 23-8-20.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 200000 * 2 + 1;

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

    class SegTree{
        class Node{
        public:
            int l, r, val, tag;
            Node *ls, *rs;
        };
        Node node[4 * N + 5]{};

        void build(Node *u, int l, int r, const int *data){
            static int cnt = 1;
            u->l = l, u->r = r;
            if(l == r){
                u->val = data[l];
                return;
            }
            int mid = (l+r)/2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid, data);
            build(u->rs, mid+1, r, data);
            u->val = max(u->ls->val, u->rs->val);
        }

        static void update(Node *u, int val){
            u->val += val;
            u->tag += val;
        }

        static void push_down(Node *u){
            if(u->tag){
                update(u->ls, u->tag);
                update(u->rs, u->tag);
                u->tag = 0;
            }
        }

        static void add(Node *u, const int l, const int r, const int val){
            if(l <= u->l && u->r <= r){
                update(u, val);
                return;
            }
            push_down(u);
            if(l <= u->ls->r){
                add(u->ls, l, r, val);
            }
            if(r >= u->rs->l){
                add(u->rs, l, r, val);
            }
            u->val = max(u->ls->val, u->rs->val);
        }

    public:
        SegTree(int n, const int *data){
            build(&node[1], 1, n, data);
        }

        void add(int l, int r, int val){
            add(&node[1], l, r, val);
        }

        int query_(){
            return node[1].val;
        }
    };

    auto read = Tools::read;

    int n;
    read(n);

    static int raw_data[N + 5], pos[N + 5];
    for(int i = 1; i <= 2 * n + 1; i++){
        read(raw_data[i]);
        pos[raw_data[i]] = i;
    }

    static int data[N + 5];
    for(int i = 1; i <= n+1; i++){
        data[i] = i-2;
    }
    static SegTree tree(n+1, data);

    int now = 0, ans = 1;
    for(int i = 1; i <= 2 * n + 1; i++){ // TODO understand
        while(tree.query_() <= n && now <= 2 * n + 1){ // how does the tree work
            tree.add(1, abs(pos[++now] - n - 1) + 1, 1); // why abs
        }
        ans = max(ans, now - i);
        tree.add(1, abs(pos[i] - n - 1) + 1, -1);
    }

    printf("%d\n", ans);
}