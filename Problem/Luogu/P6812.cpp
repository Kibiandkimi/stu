//
// Created by kibi on 23-10-1.
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

    class SegTree{
        using ll = long long;
        class Node{
        public:
            int l, r;
            ll mn;
            Node *ls, *rs;
        };
        Node *rt;

        static void update(Node *u){
            u->mn = min(u->ls->mn, u->rs->mn);
        }

        static void build(Node *u, int l, int r, const int *data){
            u->l = l, u->r = r;
            if(l == r){
                u->mn = data[l];
                return;
            }

            int mid = (l + r) / 2;
            u->ls = new Node, u->rs = new Node;
            build(u->ls, l, mid, data);
            build(u->rs, mid + 1, r, data);
            update(u);
        }

        static ll query(Node *u, int l, int r){
            if(l <= u->l && u->r <= r){
                return u->mn;
            }

            ll res = 0;
            if(l <= u->ls->r){
                res = min(res, query(u->ls, l, r));
            }
            if(r >= u->rs->l){
                res = min(res, query(u->rs, l, r));
            }

            return res;
        }

    public:
        SegTree(int n, const int *data){
            rt = new Node;
            build(rt, 1, n, data);
        }

        void modify(int x, int val){
            vector<Node*> v;
            Node *now = rt;
            while(now->l != now->r){
                v.emplace_back(now);
                if(x <= (now->l + now->r) / 2){
                    now = now->ls;
                }else{
                    now = now->rs;
                }
            }
            now->mn += val;
            reverse(v.begin(), v.end());
            for(auto i : v){
                update(i);
            }
        }

        ll query(int l, int r){
            return query(rt, l, r);
        }
    };

    auto read = Tools::read;

    int n, k;
    read(n), read(k);

    int raw_data[n];
    for(int &i : raw_data){
        read(i);
    }

    int inc[n];
    inc[0] = raw_data[0];
    for(int i = 1; i < n; i++){
        inc[i] = raw_data[i] - raw_data[i - 1];
    }

    SegTree tree(n, inc - 1);

    while(k--){
        static int opt, l, r;
        read(opt), read(l), read(r);
        r = (r == n + 1 ? n : r);
        if(opt == 1){
            static int x;
            read(x);
            tree.modify(l, x);
            r == n ? void(0) : tree.modify(r + 1, -x);
        }else{
            l++;
            if(l > r || tree.query(l, r) >= 0){
                printf("Yes\n");
            }else{
                printf("No\n");
            }
        }
    }

}