//
// Created by kibi on 23-8-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    //    freopen("t.in", "r", stdin);

    const int N = 1000000;

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

        static long long gcd(long long a, long long b){
            if(!b){
                return a;
            }
            return gcd(b, a % b);
        }
    };

    class SegTree{
        class Node{
        public:
            int l, r;
            long long p, q, lp, lq, rp, rq, sum, tag; // p-->mx, q-->len
                                                     //            double mx, lmx, rmx;
            bool len;
            Node *ls, *rs;
        };

        Node node[4 * N + 5]{};

        static void update(Node *u){
            if(!u->ls->len&&!u->rs->len){
                u->lp = u->rp = u->p = u->ls->p + u->rs->p;
                u->lq = u->rq = u->q = 2;
            }else if(!u->ls->len){
                long long l1 = u->ls->p + u->rs->ls->p,
                          mid = u->ls->p + u->rs->p,
                          r1 = u->rs->p;
                if((double) r1 /2 >= (double) l1 /2 && (double) r1 /2 >= (double) mid /3){
                    u->p = r1;
                    u->q = 2;
                    u->rp = r1;
                    u->rq = 2;

                    if((double) l1 /2 < (double) mid /3){
                        u->lp = mid;
                        u->lq = 3;
                    }else{
                        u->lp = l1;
                        u->lq = 2;
                    }

                }else if((double) l1 /2 < (double) mid /3){
                    u->lp = u->rp = u->p = mid;
                    u->lq = u->rq = u->q = 3;

                }else{
                    u->lp = u->p = l1;
                    u->lq = u->q = 2;

                    if((double) r1 /2 >= (double) mid /3){
                        u->rp = r1;
                        u->rq = 2;
                    }else{
                        u->rp = mid;
                        u->rq = 3;
                    }
                }

            }else if(!u->rs->len){
                long long r1 = u->rs->p + u->ls->rs->p,
                          mid = u->rs->p + u->ls->p,
                          l1 = u->ls->p;
                if((double) l1 /2 >= (double) r1 /2 && (double) l1 /2 >= (double) mid /3){
                    u->p = l1;
                    u->q = 2;
                    u->lp = l1;
                    u->lq = 2;

                    if((double) r1 /2 < (double) mid /3){
                        u->rp = mid;
                        u->rq = 3;
                    }else{
                        u->rp = r1;
                        u->rq = 2;
                    }

                }else if((double) r1 /2 < (double) mid /3){
                    u->lp = u->rp = u->p = mid;
                    u->lq = u->rq = u->q = 3;

                }else{
                    u->rp = u->p = r1;
                    u->rq = u->q = 2;

                    if((double) l1 /2 >= (double) mid /3){
                        u->lp = l1;
                        u->lq = 2;
                    }else{
                        u->lp = mid;
                        u->lq = 3;
                    }
                }

            }else{
                // update p, q
                double l1 = (double)u->ls->p / (double)u->ls->q,
                       mid = (double)(u->ls->rp + u->rs->lp) / (double)(u->ls->rq + u->rs->lq),
                       r1 = (double)u->rs->p / (double)u->rs->q;
                if(l1 > mid && l1 > r1){
                    u->p = u->ls->p;
                    u->q = u->ls->q;
                }else if(r1 > mid){
                    u->p = u->rs->p;
                    u->q = u->rs->q;
                }else{
                    u->p = (u->ls->rp) + (u->rs->lp);
                    u->q = (u->ls->rq) + (u->rs->lq);
                }

                // update lp, lq
                l1 = (double)u->ls->lp / (double)u->ls->lq,
                r1 = (double)(u->ls->sum + u->rs->lp) /
                     (double)(u->ls->r - u->ls->l + 1 + u->rs->lq);
                if(l1 < r1){
                    u->lp = u->ls->sum + u->rs->lp;
                    u->lq = u->ls->r - u->ls->l + 1 + u->rs->lq;
                }else{
                    u->lp = u->ls->lp;
                    u->lq = u->ls->lq;
                }

                // update rp, rq
                l1 = (double)(u->ls->rp + u->rs->sum) /
                     (double)(u->ls->rq + u->rs->r - u->rs->l + 1),
                r1 = (double)(u->rs->rp) / (double)(u->rs->rq);
                if(l1 > r1){
                    u->rp = u->ls->rp + u->rs->sum;
                    u->rq = u->ls->rq + u->rs->r - u->rs->l + 1;
                }else{
                    u->rp = u->rs->rp;
                    u->rq = u->rs->rq;
                }


            }

            u->len = true;
            u->sum = u->ls->sum + u->rs->sum;

        }

        static void push_down(Node *u){
            if(u->tag){
                // update ls
                u->ls->tag += u->tag;
                u->ls->p += u->tag * (u->ls->q);
                u->ls->lp += u->tag * (u->ls->lq);
                u->ls->rp += u->tag * (u->ls->rq);
                u->ls->sum += u->tag * (u->ls->r - u->ls->l + 1);
                // update rs
                u->rs->tag += u->tag;
                u->rs->p += u->tag * (u->rs->q);
                u->rs->lp += u->tag * (u->rs->lq);
                u->rs->rp += u->tag * (u->rs->rq);
                u->rs->sum += u->tag * (u->rs->r - u->rs->l + 1);

                u->tag = 0;
            }
        }

        void build(Node *u, int l, int r, const int *data){
            static int cnt = 1;
            u->l = l, u->r = r;
            if(l == r){
                //                u->mx = data[l];
                u->sum = u->lp = u->rp = u->p = data[l];
                u->lq = u->rq = u->q = 1;
                u->len = false;
                return;
            }
            int mid = (l+r)/2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid, data);
            build(u->rs, mid+1, r, data);
            update(u);
        }

        void add(Node *u, const int l, const int r, const int v){
            if(l <= u->l && u->r <= r){
                u->tag += v;
                u->p += v * (u->q);
                u->lp += v * (u->lq);
                u->rp += v * (u->rq);
                u->sum += v * (u->r - u->l + 1);
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

        Node query(Node *u, const int l, const int r){
            if(l <= u->l && u->r <= r){
                return *u;
            }
            push_down(u);

            Node ls;
            if(l <= u->ls->r){
                ls = query(u->ls, l, r);
            }else{
                return query(u->rs, l, r);
            }

            Node rs;
            if(r >= u->rs->l){
                rs = query(u->rs, l, r);
            }else{
                return ls;
            }

            Node fa = *u;
            fa.ls = &ls, fa.rs = &rs;
            update(&fa);
            return fa;
        }

    public:
        SegTree(int n, const int *data){
            build(&node[1], 1, n, data);
        }

        void add(const int l, const int r, const int v){
            add(&node[1], l, r, v);
        }

        pair<long long, long long> query(int l, int r){
            static Node tem;
            tem = query(&node[1], l, r);
            return {tem.p, tem.q};
        }
    };

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static int raw_data[N + 5];
    for(int i = 1; i <= n; i++){
        read(raw_data[i]);
    }

    static SegTree tree(n, raw_data);
    while(m--){
        int opt, l, r, x;
        read(opt), read(l), read(r);
        switch (opt) {
            case 1:
                read(x);
                tree.add(l, r, x);
                break;
            case 2:
                auto [p, q] = tree.query(l, r);
                if(!p){
                    printf("0/1\n");
                }else {
                    bool w = (p < 0);
                    p = (p < 0) ? -p : p;
                    long long gcd = Tools::gcd(p, q);
                    //                    if(p % gcd != 0 || q % gcd != 0 || q <= 1){
                    //                        throw exception();
                    //                    }
                    p /= gcd, q /= gcd;
                    p = w ? -p : p;
                    printf("%lld/%lld\n", p, q);
                }
        }
    }

    //    fclose(stdin);
}