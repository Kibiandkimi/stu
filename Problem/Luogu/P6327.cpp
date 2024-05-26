//
// Created by kibi on 23-8-15.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 200000;

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

        static double sin(double sin, double cos, long long b){
            return sin * ::cos(b) + cos * ::sin(b);
        }

        static double cos(double sin, double cos, long long b){
            return cos * ::cos(b) - sin * ::sin(b);
        }

    };

    class SegTree{
        class Node{
        public:
            int l, r;
            long long tag; // int->long long 0pts->100pts ??
            double sin, cos;
            Node *ls, *rs;
        };
        Node node[4 * N + 5]{};

        static void update(Node *u){
            u->sin = u->ls->sin + u->rs->sin;
            u->cos = u->ls->cos + u->rs->cos;
        }

        static void update(Node *u, long long v){
            double pre_sin = u->sin, pre_cos = u->cos;
            u->sin = Tools::sin(pre_sin, pre_cos, v);
            u->cos = Tools::cos(pre_sin, pre_cos, v);
        }

        void build(Node *u, int l, int r, const int *data){
            static int cnt = 1;
            u->l = l, u->r = r;
            if(l == r){
                u->sin = sin(data[l]);
                u->cos = cos(data[l]);
                return;
            }
            const int mid = (l+r)/2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid, data);
            build(u->rs, mid+1, r, data);
            update(u);
        }

        static void push_down(Node *u){
            if(u->tag){
                u->ls->tag += u->tag;
                u->rs->tag += u->tag;
                update(u->ls, u->tag);
                update(u->rs, u->tag);
                u->tag = 0;
            }
        }

        static void add(Node *u, const int l, const int r, const int v){
            if(l <= u->l && u->r <= r){
                u->tag += v;
                update(u, v);
                return;
            }
            push_down(u);
            if(l <= u->ls->r){
                add(u->ls, l, r, v);
            }
            if(r >= u->rs->l){
                add(u->rs, l, r, v);
            }
            update(u);
        }

        static double query(Node *u, const int l, const int r){
            if(l <= u->l && u->r <= r){
                return u->sin;
            }
            push_down(u);
            double res = 0;
            if(l <= u->ls->r){
                res += query(u->ls, l, r);
            }
            if(r >= u->rs->l){
                res += query(u->rs, l, r);
            }
            return res;
        }

    public:
        SegTree(int n, const int *data){
            build(&node[1], 1, n, data);
        }

        void add(int l, int r, int v){
            add(&node[1], l, r, v);
        }

        double query(int l, int r){
            return query(&node[1], l, r);
        }

    };

    auto read = Tools::read;

    int n;
    read(n);

    static int a[N + 5];
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }

    static SegTree tree(n, a);

    int m;
    read(m);

    while(m--){
        int opt, l, r;
        read(opt), read(l), read(r);
        switch(opt){
            case 1:
                int v;
                read(v);
                tree.add(l, r, v);
                break;
            case 2:
                printf("%.1lf\n", tree.query(l, r));
                break;
            default:
                throw exception();
        }
    }
}