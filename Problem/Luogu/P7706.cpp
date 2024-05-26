//
// Created by kibi on 23-8-2.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 500000;

void read(int&);

int main(){
    class SegTree{

        class Node{
        public:
            int maxA, minB, maxL, maxR, w; // 1 <= (a, b) <= 1e8

            Node(){
                maxA = maxL = maxR = w = -5e8;
                minB = 5e8;
            }

            Node(int maxA, int minB, int maxL, int maxR, int w) :
                                                                  maxA(maxA), minB(minB), maxL(maxL), maxR(maxR), w(w){}

            void operator += (const Node &b){
                w = max(max(maxL + b.maxA, maxA + b.maxR), max(w, b.w));
                maxL = max(maxA - b.minB, max(maxL, b.maxL)),
                maxR = max(b.maxA - minB, max(maxR, b.maxR)),
                maxA = max(maxA, b.maxA),
                minB = min(minB, b.minB);
            }


            Node operator + (const Node &b) const{
                return {
                        max(maxA, b.maxA),
                        min(minB, b.minB),
                        max(maxA - b.minB, max(maxL, b.maxL)),
                        max(b.maxA - minB, max(maxR, b.maxR)),
                        max(max(maxL + b.maxA, maxA + b.maxR), max(w, b.w))
                };
            }
        };

        int l[4 * N + 5]{}, r[4 * N + 5]{}, ls[4 * N + 5]{}, rs[4 * N + 5]{};
        Node node[4 * N + 5];

        void build(int u, int l, int r, const int *dataA, const int *dataB){
            this -> l[u] = l, this -> r[u] = r;
            if(l == r){
                node[u].maxA = dataA[l];
                node[u].minB = dataB[l];
                return;
            }
            int mid = (l+r)/2;
            ls[u] = u*2, rs[u] = u*2+1;
            build(ls[u], l, mid, dataA, dataB);
            build(rs[u], mid+1, r, dataA, dataB);
            node[u] = node[ls[u]] + node[rs[u]];
        }

        void query(int u, int _l, int _r, Node &res){
            if(_l <= l[u] && r[u] <= _r){
                res += node[u];
                //                res = res + node[u];
                return;
            }

            if(_l <= r[ls[u]]){
                query(ls[u], _l, _r, res);
            }
            if(_r >= l[rs[u]]){
                query(rs[u], _l, _r, res);
            }

        }

        void _change(bool flag, int u, int pos, int v){
            if(l[u] == r[u]){
                flag ? node[u].minB = v : node[u].maxA = v;
                return;
            }
            if(pos <= r[ls[u]]){
                _change(flag, ls[u], pos, v);
            }else{
                _change(flag, rs[u], pos, v);
            }
            node[u] = node[ls[u]] + node[rs[u]];
        }

    public:
        SegTree(int n, const int *dataA, const int *dataB){
            build(1, 1, n, dataA, dataB);
        }

        void change(bool flag, int pos, int v){

            int l = this -> l[1], r = this -> r[1], u = 1, num = 0;

            while(l != r){
                int mid = (l + r) / 2;
                if(mid*2 != (l + r)){ // 真是傻到家了，num写错了还能用， 发现下面根本不用l, r
                    num <<= 1; //应该写if外
                    num ^= 1;
                }

                if(pos <= mid){
                    u = u*2; // u = ls[u]
                    r = mid; // r = r[ls[u]]
                }else{
                    u = u*2+1; // ...
                    l = mid+1; // ...
                }
            }

            if(!flag){
                node[u].maxA = v;
            }else{
                node[u].minB = v;
            }

            while(u != 1){
                if(u & 1){ // 就是这，l,r根本没用，所以num错了没关系
                    // mid = l-1
                    l = (l-1)*2 + (num&1) - r;
                }else{
                    r = r*2 + (num&1) - l;
                }
                u >>= 1;
                num >>= 1;
                node[u] = node[ls[u]] + node[rs[u]];
            }

        }

        void _change(bool flag, int pos, int v){
            _change(flag, 1, pos, v);
        }

        int query(int l, int r){
            Node res;
            query(1, l, r, res);
            return res.w;
        }

    };

    int n, m;
    read(n), read(m);

    static int rawA[N + 5], rawB[N + 5];

    for(int i = 1; i <= n; i++){
        read(rawA[i]);
    }

    for(int i = 1; i <= n; i++){
        read(rawB[i]);
    }

    static SegTree tree(n, rawA, rawB);

    while(m--){
        int opt, x, y;
        read(opt),  read(x), read(y);

        switch(opt){
            case 1: tree.change(false, x, y); break;
            case 2: tree.change(true, x, y); break;
            case 3: printf("%d\n", tree.query(x, y)); break;
            default: throw "";
        }
    }
}

void read(int &x){
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