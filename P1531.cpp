//
// Created by kibi on 23-8-7.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 200000;

void read(int&);

int main(){

    class SegTree{
        int l[4 * N + 5]{}, r[4 * N + 5]{}, ls[4 * N + 5]{}, rs[4 * N + 5]{}, mx[4 * N + 5]{};

        void build(int u, int l, int r, const int *data){
            this -> l[u] = l, this -> r[u] = r;
            if(l == r){
                mx[u] = data[l];
                return;
            }
            int mid = (l+r)/2;
            ls[u] = u*2, rs[u] = u*2+1;
            build(ls[u], l, mid, data);
            build(rs[u], mid+1, r, data);
            mx[u] = max(mx[ls[u]], mx[rs[u]]);
        }

        int query(int u, const int l, const int r){
            if(l <= this -> l[u] && this -> r[u] <= r){
                return mx[u];
            }
            int res = -1e9;

            if(l <= this -> r[ls[u]]){
                res = max(res, query(ls[u], l, r));
            }
            if(r >= this -> l[rs[u]]){
                res = max(res, query(rs[u], l, r));
            }

            return res;

        }

    public:

        SegTree(int n, int *data){
            build(1, 1, n, data);
        }

        int query(const int l, const int r){
            return query(1, l, r);
        }

        void update(int x, int v){
            int u = 1;
            while(l[u] < r[u]){
                if(x <= r[ls[u]]){
                    u = ls[u];
                }else{
                    u = rs[u];
                }
            }
            mx[u] = v;
            while(u != 1){
                u >>= 1;
                mx[u] = max(mx[ls[u]], mx[rs[u]]);
            }
        }

    };

    int n, m;
    read(n), read(m);

    static int raw[N + 5];

    for(int i = 1; i <= n; i++){
        read(raw[i]);
    }

    static SegTree tree(n, raw);

    class Err : public exception{};

    for(int i = 1; i <= m; i++){
        int opt, l, r, x, v;
        read(opt);
        switch(opt){
            case 'Q':
                read(l), read(r);
                printf("%d\n", tree.query(l, r));
                break;
            case 'U':
                read(x), read(v);
                if(raw[x] < v){
                    raw[x] = v;
                    tree.update(x, v);
                }
                break;
            default:
                throw Err();
        }
    }

}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while((c < '0' || '9' < c) && c != 'U' && c != 'Q'){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    if(c == 'U' || c == 'Q'){
        x = c;
        return;
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}