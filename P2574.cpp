//
// Created by kibi on 23-8-7.
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

        static void readStr(bool *x){
            int c = getchar();
            while(c != '0' && c != '1'){
                c = getchar();
            }
            int len = 0;
            while(c == '0' || c == '1'){
                x[len++] = (c == '1');
                c = getchar();
            }
        }
    };

    class SegTree{
        int l[4 * N + 5]{}, r[4 * N + 5]{}, ls[4 * N + 5]{}, rs[4 * N + 5]{}, sum[4 * N + 5]{};

        bool tag[4 * N + 5]{};

        void build(int u, int l, int r, const bool *data){
            this -> l[u] = l, this -> r[u] = r;
            if(l == r){
                sum[u] = data[l];
                return;
            }
            int mid = (l+r)/2;
            ls[u] = 2*u, rs[u] = 2*u+1;
            build(ls[u], l, mid, data);
            build(rs[u], mid+1, r, data);
            sum[u] = sum[ls[u]] + sum[rs[u]];
        }

        void push_down(int u){
            if(tag[u] && l[u] != r[u]){
                tag[ls[u]] = !tag[ls[u]];
                sum[ls[u]] = (r[ls[u]] - l[ls[u]] + 1) - sum[ls[u]];
                tag[rs[u]] = !tag[rs[u]];
                sum[rs[u]] = (r[rs[u]] - l[rs[u]] + 1) - sum[rs[u]];
                tag[u] = false;
            }
        }

        void change(int u, int l, int r){
            if(l <= this -> l[u] && this -> r[u] <= r){
                tag[u] = !tag[u];
                sum[u] = (this -> r[u] - this -> l[u] + 1) - sum[u];
                return;
            }

            push_down(u);

            if(l <= this -> r[ls[u]]){
                change(ls[u], l, r);
            }
            if(r >= this -> l[rs[u]]){
                change(rs[u], l, r);
            }

            sum[u] = sum[ls[u]] + sum[rs[u]];

        }

        int query(int u, int l, int r){
            if(l <= this -> l[u] && this -> r[u] <= r){
                return sum[u];
            }

            push_down(u);

            int res = 0;

            if(l <= this -> r[ls[u]]){
                res += query(ls[u], l, r);
            }
            if(r >= this -> l[rs[u]]){
                res += query(rs[u], l, r);
            }

            return res;
        }

    public:

        SegTree(int n, bool *data){
            build(1, 1, n, data);
        }

        void change(int l, int r){
            change(1, l, r);
        }

        int query(int l, int r){
            return query(1, l, r);
        }

    };

    int n, m;
    Tools::read(n), Tools::read(m);

    static bool raw_data[N + 5];

    Tools::readStr(raw_data+1);

    static SegTree tree(n, raw_data);

    while(m--){
        int opt, l, r;
        Tools::read(opt), Tools::read(l), Tools::read(r);
        switch(opt){
            case 0:
                tree.change(l, r);
                break;
            case 1:
                printf("%d\n", tree.query(l, r));
                break;
            default:
                throw exception();
        }
    }
}