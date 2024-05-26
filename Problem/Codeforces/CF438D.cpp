//
// Created by kibi on 23-8-3.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

template<typename Num>
void read(Num&);

int main(){

    class SegTree{
        class Node{
        public:
            long long mx, sum;

            Node operator + (const Node &b) const{
                return {max(mx, b.mx), sum+b.sum};
            }

            void operator %= (const int &p) {
                mx %= p;
                sum %= p;
            }

            /* can't deal with sum
			void operator += (const int &b) {
				mx = max(mx, b.mx);
				sum += b.sum;
			}
			*/
        };
        int l[4 * N + 5]{}, r[4 * N + 5]{}, ls[4 * N + 5]{}, rs[4 * N + 5]{};
        Node node[4 * N + 5]{};

        void build(int u, int l, int r, const long long *data){
            this -> l[u] = l, this -> r[u] = r;
            if(l == r){
                node[u] = {data[l], data[l]};
                return;
            }
            int mid = (l+r)/2;
            ls[u] = u*2, rs[u] = u*2+1;
            build(ls[u], l, mid, data);
            build(rs[u], mid+1, r, data);
            node[u] = node[ls[u]] + node[rs[u]];
        }

        long long query(int u, const int l, const int r){
            if(l <= this -> l[u] && this -> r[u] <= r){
                return node[u].sum;
            }
            long long res = 0;
            if(l <= this -> r[ls[u]]){
                res += query(ls[u], l, r);
            }
            if(r >= this -> l[rs[u]]){
                res += query(rs[u], l, r);
            }
            return res;
        }

        void mod(int u, const int l, const int r, const int p){
            if(node[u].mx < p){
                return;
            }
            if(this -> l[u] == this -> r[u]){
                node[u] %= p;
                return ;
            }
            if(l <= this -> r[ls[u]]){
                mod(ls[u], l, r, p);
            }
            if(r >= this -> l[rs[u]]){
                mod(rs[u], l, r, p);
            }
            node[u] = node[ls[u]] + node[rs[u]];
        }

        void change(int u, const int x, const int v){
            if(l[u] == r[u]){
                node[u] = {v, v};
                return;
            }
            if(x <= r[ls[u]]){
                change(ls[u], x, v);
            }else{
                change(rs[u], x, v);
            }
            node[u] = node[ls[u]] + node[rs[u]];
        }

    public:
        SegTree(int n, const long long *data){
            build(1, 1, n, data);
        }

        long long query(const int l, const int r){
            return query(1, l, r);
        }

        void mod(const int l, const  int r, const int p){
            mod(1, l, r, p);
        }

        void change(const int x, const int v){
            change(1, x, v);
        }
    };

    int n, m;
    static long long raw[N + 5];

    read(n), read(m);

    for(int i = 1; i <= n; i++){
        read(raw[i]);
    }

    static SegTree tree(n, raw);

    while(m--){
        int opt, l, r, k, x;
        read(opt);
        switch(opt){
            case 1:
                read(l), read(r);
                printf("%lld\n", tree.query(l, r));
                break;
            case 2:
                read(l), read(r), read(x);
                tree.mod(l, r, x);
                break;
            case 3:
                read(k), read(x);
                tree.change(k, x);
                break;
            default:
                throw " ";
        }
    }
}

template<typename Num>
void read(Num& x){
    Num s = 0, w = 1, c = getchar();
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