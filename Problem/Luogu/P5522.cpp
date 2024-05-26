//
// Created by kibi on 23-10-28.
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

        static void read_(int *x){
            static auto judge = [](int c){
                return c == '0' || c == '1' || c == '?';
            };
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            int cnt = 0;
            while(judge(c)){
                x[cnt++] = c;
                c = getchar();
            }
        }

        static int pow(int a, int p){
            int res = 1;
            while(p){
                if(p & 1){
                    res *= a;
                }
                a *= a;
                p >>= 1;
            }
            return res;
        }
    };

    static int n, m, q;

    class Letter{
    public:
        int stat1, stat2;

        explicit Letter(const int *a):stat1(0), stat2(0){
            for(int i = 0; i < n; i++){
                if(a[i] == '0'){
                    stat1 += (1 << i);
                }else if(a[i] == '1'){
                    stat1 += (1 << i);
                    stat2 += (1 << i);
                }else if(a[i] != '?'){
                    throw exception();
                }
            }
        }

        Letter() = default;
    };

    class SegTree{
        using Stat = tuple<int, int, bool>;
        class Node{
        public:
            int l{}, r{};
            Stat stat;
            Node *ls{}, *rs{};
        };

        Node *rt;

        static void update(Node *u){
            auto [ls_a, ls_b, ls_flag] = u->ls->stat;
            auto [rs_a, rs_b, rs_flag] = u->rs->stat;
            if(!(ls_flag && rs_flag)){
                u->stat = {0, 0, false};
                return;
            }
            int res_a = 0, res_b = 0;
            for(int i = 0; i < n; i++){
                int now_l_a = ls_a & 1,
                    now_l_b = ls_b & 1,
                    now_r_a = rs_a & 1,
                    now_r_b = rs_b & 1;
                if(now_l_a && !now_r_a){
                    res_a += (1 << i);
                    res_b += (now_l_b << i);
                }else if(!now_l_a && now_r_a){
                    res_a += (1 << i);
                    res_b += (now_r_b << i);
                }else if(now_l_a != 0){
                    if(now_l_b == now_r_b){
                        res_a += (1 << i);
                        res_b += (now_l_b << i);
                    }else{
                        u->stat = {0, 0, false};
                        return;
                    }
                }
                ls_a >>= 1, rs_a >>= 1, ls_b >>= 1, rs_b >>= 1;
            }
            u->stat = {res_a, res_b, true};
        }

        static void build(Node *u, int l, int r, const Letter *data){
            u->l = l, u->r = r;
            if(l == r){
                u->stat = {data[l].stat1, data[l].stat2, true};
                return;
            }

            int mid = (l + r) >> 1;
            u->ls = new Node, u->rs = new Node;
            build(u->ls, l, mid, data);
            build(u->rs, mid + 1, r, data);
            update(u);
        }

        static Stat query(Node *u, int l, int r){
            if(l <= u->l && u->r <= r){
                return u->stat;
            }

            Node res, ls = {0}, rs = {0};

            if(l <= u->ls->r){
                ls = {l, r, query(u->ls, l, r)};
            }
            if(r >= u->rs->l){
                rs = {l, r, query(u->rs, l, r)};
            }
            if(!ls.l){
                return rs.stat;
            }else if(!rs.l){
                return ls.stat;
            }else{
                res.ls = &ls, res.rs = &rs;
                update(&res);
                return res.stat;
            }
        }

    public:
        SegTree(int len, const Letter *data){
            rt = new Node;
            build(rt, 1, len, data);
        }

        Stat query(int l, int r){
            return query(rt, l, r);
        }

        void modify(int x, Letter val){
            Node *now = rt;
            vector<Node*> pst;
            while(now->l < now->r){
                pst.emplace_back(now);
                if(x <= now->ls->r){
                    now = now->ls;
                }else{
                    now = now->rs;
                }
            }

            now->stat = {val.stat1, val.stat2, true};

            reverse(pst.begin(), pst.end());
            for(auto i : pst){
                update(i);
            }
        }
    };

    auto read = Tools::read;

    read(n), read(m), read(q);

    Letter letter[m];

    for(auto &i : letter){
        int a[n];
        Tools::read_(a);
        i = Letter{a};
    }

    SegTree tree(m, letter - 1);

    int ans = 0;

    while(q--){
        int opt;
        read(opt);
        if(!opt){
            int l, r;
            read(l), read(r);
            auto res = tree.query(l, r);
            auto [a, b, flag] = res;
            if(flag){
                int sum = 0;
                for(int i = 0; i < n; i++){
                    if((a & 1) == 0){
                        sum++;
                    }
                    a >>= 1;
                }
                sum = Tools::pow(2, sum);
                ans ^= sum;
            }
        }else{
            int pos;
            read(pos);
            int val[n];
            Tools::read_(val);
            tree.modify(pos, (Letter){val});
        }
    }

    printf("%d\n", ans);

}