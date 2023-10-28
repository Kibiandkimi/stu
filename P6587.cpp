//
// Created by kibi on 23-10-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;

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
            int num{0};
            ll sum{0}, tag{0};
            Node *ls{nullptr}, *rs{nullptr};
        };

        Node *rt;

        static void clear(Node *u){
            if(u->ls){
                clear(u->ls);
            }
            if(u->rs){
                clear(u->rs);
            }
            free(u);
        }

        static void update(Node *u){
            u->sum = 0;
            if(u->ls) {
                u->sum += u->ls->sum;
            }
            if(u->rs){
                u->sum += u->rs->sum;
            }
        }

        static void build(Node *u, int dep, int now, const int *data){
            if(!dep){
                if(data[now] == -1){
                    u->num = 0;
                    return;
                }
                u->num = 1;
                u->sum = data[now];
                u->tag = 0;
                return;
            }

            u->ls = new Node;
            build(u->ls, dep - 1, (now << 1) + 1, data);
            u->rs = new Node;
            build(u->rs, dep - 1, now << 1, data);
            update(u);
            u->num = u->ls->num + u->rs->num;
            //            if(!u->ls->num){
            //                clear(u->ls);
            //                u->ls = nullptr;
            //            }
            //            if(!u->rs->num){
            //                clear(u->rs);
            //                u->rs = nullptr;
            //            }
        }

        static void update(Node *u, ll v){
            u->tag += v;
            u->sum += (ll)v * u->num;
        }

        static void push_down(Node *u){
            if(u->tag){
                if(u->ls) {
                    update(u->ls, u->tag);
                }
                if(u->rs) {
                    update(u->rs, u->tag);
                }
                u->tag = 0;
            }
        }

        static void modify(Node *u, int v, int dep, int path){
            if(u == nullptr){
                return;
            }
            if(dep == 0){
                update(u, v);
                return;
            }

            push_down(u);
            if(path & 1){
                modify(u->ls, v, dep - 1, path >> 1);
            }else{
                modify(u->rs, v, dep - 1, path >> 1);
            }
            update(u);
        }

        static ll query(Node *u, int dep, int path){
            if(u == nullptr){
                return 0;
            }
            if(dep == 0){
                return u->sum;
            }

            push_down(u);
            if(path & 1){
                return query(u->ls, dep - 1, path >> 1);
            }else{
                return query(u->rs, dep - 1, path >> 1);
            }
        }

    public:
        SegTree(int dep, const int *data){
            rt = new Node;
            build(rt, dep, 0, data);
        }

        void modify(int x, int y, int v){
            // dep->x path->y
            modify(rt, v, x, y);
        }

        ll query(int x, int y){
            return query(rt, x, y);
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    int raw_data[n];
    for(auto &i : raw_data){
        read(i);
    }

    // TODO why 20 not ((int)ceil(log2(n)) + 1)
    int len = 20; // 8 = 1000 -> 4 == 1 << 4 = 10000
    int data[(1 << len) + 1];
    memset(data, -1, sizeof data);
    for(int i = 0; i < n; i++){
        int now = i + 1;
        int res = 0;
        for(int l = 0; l < len; l++){
            if(now & (1 << l)){
                res += (1 << (len - l - 1));
            }
        }
        data[res] = raw_data[i];
    }

    SegTree segTree(len, data);

    ll lst = 0;
    while(m--){
        int op, x, y;
        read(op), read(x), read(y);
        op = (int)((op + lst) & 1) + 1;
        if(op == 1){
            int v;
            read(v);
            segTree.modify(x, y, v);
        }else{
            lst = segTree.query(x, y);
            printf("%lld\n", lst);
        }
    }
}