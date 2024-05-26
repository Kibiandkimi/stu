//
// Created by kibi on 23-8-17.
//

// wrong (3 5 -1 9 -9)
// see tem/tem-2023-8-18.diff

#include <bits/stdc++.h>
using namespace std;

int main(){

    freopen("t.in", "r", stdin);
    freopen("t.out", "w", stdout);

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
            long long single_lp, single_rp;
            //            double mx, lmx, rmx;
            bool len;
            Node *ls, *rs;
        };

        Node node[4 * N + 5]{};

        static void update(Node *u){
            if(!u->ls->len&&!u->rs->len){
                u->lp = u->rp = u->p = u->ls->p + u->rs->p;
                u->lq = u->rq = u->q = 2;
                //                u->single_lp = u->ls->p;
                //                u->single_rp = u->rs->p;
            }else if(!u->ls->len){
                // update p, q
                double l1 = (double)(u->ls->rp + u->rs->lp)/(double)(u->ls->rq + u->rs->lq),
                       r1 = (double)u->rs->p/(double)u->rs->q,
                       mid = (double)(u->ls->rp + u->rs->single_lp)/(double)(u->ls->rq + 1);
                if(mid > l1 && mid > r1){
                    u->p = (u->ls->rp + u->rs->single_lp);
                    u->q = (u->ls->rq + 1);
                }else if(l1 < r1){
                    u->p = u->rs->p;
                    u->q = u->rs->q;
                }else{
                    u->p = (u->ls->rp + u->rs->lp);
                    u->q = (u->ls->rq + u->rs->lq);
                }

                // update lp, lq
                l1 = (double)(u->ls->sum + u->rs->lp)/(double)(u->ls->r - u->ls->l + 1 + u->rs->lq),
                mid = (double)(u->ls->sum + u->rs->single_lp)/(double)(u->ls->r - u->ls->l + 1 + 1);
                if(mid > l1){
                    u->lp = (u->ls->sum + u->rs->single_lp);
                    u->lq = (u->ls->r - u->ls->l + 1 + 1);
                }else{
                    u->lp = (u->ls->sum + u->rs->lp);
                    u->lq = (u->ls->r - u->ls->l + 1 + u->rs->lq);
                }


                //update rp, rq
                l1 = (double)(u->ls->rp + u->rs->sum)/(double)(u->ls->rq + u->rs->r - u->rs->l + 1),
                r1 = (double)u->rs->rp/(double)u->rs->rq;
                if(l1 > r1){
                    u->rp = (u->ls->rp + u->rs->sum);
                    u->rq = (u->ls->rq + u->rs->r - u->rs->l + 1);
                }else{
                    u->rp = (u->rs->rp);
                    u->rq = (u->rs->rq);
                }

            }else if(!u->rs->len){
                // update p, q
                double l1 = (double)(u->ls->p)/(double)(u->ls->q),
                       r1 = (double)(u->ls->rp + u->rs->lp)/(double)(u->ls->rq + u->rs->lq),
                       mid = (double)(u->ls->single_rp + u->rs->lp)/(double)(1 + u->rs->lq);
                if(mid > r1 && mid > l1){
                    u->p = (u->ls->single_rp + u->rs->lp);
                    u->q = (1 + u->rs->lq);
                }else if(r1 > l1){
                    u->p = (u->ls->rp + u->rs->lp);
                    u->q = (u->ls->rq + u->rs->lq);
                }else{
                    u->p = (u->ls->p);
                    u->q = (u->ls->q);
                }

                //update rp, rq
                r1 = (double)(u->ls->rp + u->rs->sum)/(double)(u->ls->rq + u->rs->r - u->rs->l + 1),
                mid = (double)(u->ls->single_rp + u->rs->sum)/(double)(1 + u->rs->r - u->rs->l + 1);
                if(mid > r1){
                    u->rp = (u->ls->single_rp + u->rs->sum);
                    u->rq = (1 + u->rs->r - u->rs->l + 1);
                }else {
                    u->rp = (u->ls->rp + u->rs->sum);
                    u->rq = (u->ls->rq + u->rs->r - u->rs->l + 1);
                }

                //update lp, lq
                l1 = (double)(u->ls->lp)/(double)(u->ls->lq);
                r1 = (double)(u->ls->sum + u->rs->lp)/(double)(u->ls->r - u->ls->l + 1 + u->rs->lq);
                if(r1 > l1){
                    u->lp = (u->ls->sum + u->rs->lp);
                    u->lq = (u->ls->r - u->ls->l + 1 + u->rs->lq);
                }else{
                    u->lp = (u->ls->lp);
                    u->lq = (u->ls->lq);
                }

            }else{
                // update p, q
                double l1 = (double)u->ls->p / (double)u->ls->q,
                       mid = (double)(u->ls->rp + u->rs->lp) / (double)(u->ls->rq + u->rs->lq),
                       r1 = (double)u->rs->p / (double)u->rs->q,
                       mid_single_l = (double)(u->ls->single_rp + u->rs->lp) / (double)(1 + u->rs->lq),
                       mid_single_r = (double)(u->ls->rp + u->rs->single_lp) / (double)(u->ls->rq + 1),
                       mid_single_lr = (double)(u->ls->single_rp + u->rs->single_lp) / 2;
                double mx = max({l1, mid, r1, mid_single_l, mid_single_r, mid_single_lr});
                if(mid_single_lr == mx){
                    u->p = (u->ls->single_rp + u->rs->single_lp);
                    u->q = 2;
                }else if(mid_single_l == mx){
                    u->p = (u->ls->single_rp + u->rs->lp);
                    u->q = (1 + u->rs->lq);
                }else if(mid_single_r == mx){
                    u->p = (u->ls->rp + u->rs->single_lp);
                    u->q = (u->ls->rq + 1);
                }else if(l1 == mx){
                    u->p = u->ls->p;
                    u->q = u->ls->q;
                }else if(r1 == mx){
                    u->p = u->rs->p;
                    u->q = u->rs->q;
                }else{
                    u->p = (u->ls->rp) + (u->rs->lp);
                    u->q = (u->ls->rq) + (u->rs->lq);
                }

                // update lp, lq
                l1 = (double)u->ls->lp / (double)u->ls->lq,
                r1 = (double)(u->ls->sum + u->rs->lp) /
                     (double)(u->ls->r - u->ls->l + 1 + u->rs->lq),
                mid_single_r = (double)(u->ls->sum + u->rs->single_lp) /
                               (double)(u->ls->r - u->ls->l + 1 + 1);
                if(mid_single_r > l1 && mid_single_r > r1){
                    u->lp = (u->ls->sum + u->rs->single_lp);
                    u->lq = (u->ls->r - u->ls->l + 1 + 1);
                }else if(l1 < r1){
                    u->lp = u->ls->sum + u->rs->lp;
                    u->lq = u->ls->r - u->ls->l + 1 + u->rs->lq;
                }else{
                    u->lp = u->ls->lp;
                    u->lq = u->ls->lq;
                }

                // update rp, rq
                l1 = (double)(u->ls->rp + u->rs->sum) /
                     (double)(u->ls->rq + u->rs->r - u->rs->l + 1),
                r1 = (double)(u->rs->rp) / (double)(u->rs->rq),
                mid_single_l = (double)(u->ls->single_rp + u->rs->sum) /
                               (double)(1 + u->rs->r - u->rs->l + 1);
                if(mid_single_l > l1 && mid_single_l > r1){
                    u->rp = (u->ls->single_rp + u->rs->sum);
                    u->rq = (1 + u->rs->r - u->rs->l + 1);
                }else if(l1 > r1){
                    u->rp = u->ls->rp + u->rs->sum;
                    u->rq = u->ls->rq + u->rs->r - u->rs->l + 1;
                }else{
                    u->rp = u->rs->rp;
                    u->rq = u->rs->rq;
                }
            }

            u->len = true;
            u->sum = u->ls->sum + u->rs->sum;
            u->single_lp = u->ls->single_lp;
            u->single_rp = u->rs->single_rp;
        }

        static void update(Node *u, long long v){
            u->tag += v;
            u->p += v * (u->q);
            u->lp += v * (u->lq);
            u->rp += v * (u->rq);
            u->single_lp += v;
            u->single_rp += v;
            u->sum += v * (u->r - u->l + 1);
        }

        static void push_down(Node *u){
            if(u->tag){
                update(u->ls, u->tag);
                update(u->rs, u->tag);
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
                u->single_lp = u->single_rp = data[l];
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
                if(!x){
                    break;
                }
                tree.add(l, r, x);
                break;
            case 2:
                // debug
                static int i = 0;
                i++;
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

    fclose(stdin);
    fclose(stdout);
}

/*

#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 1000000;

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c)
            {
                if(c == '-')
                {
                    w = -1;
                }
                c = getchar();
            }
            while('0' <= c && c <= '9')
            {
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        }
    };

    class SegTree{
        class Node{
        public:
            int l, r;
            long long mx_of_2, mx_of_3,
                    l_val_of_2, l_val_of_3,
                    r_val_of_2, r_val_of_3,
                    l_val, r_val,
                    tag;
            Node *ls, *rs;

            int size() const {
                return r - l + 1;
            }
        };
        Node node[4 * N + 5]{};

        static void update(Node *u){
            // update l_val & r_val
            u->l_val = u->ls->l_val;
            u->r_val = u->rs->r_val;

            // update mx_of_2
            // 1. ls->mx_2  (size_ls > 1)
            // 2. rs->mx_2  (size_rs > 1)
            // 3. ls->mx_r + rs_l
            u->mx_of_2 = u->ls->r_val + u->rs->l_val;
            u->mx_of_2 = (u->ls->size() > 1) ? max(u->mx_of_2, u->ls->mx_of_2) : u->mx_of_2;
            u->mx_of_2 = (u->rs->size() > 1) ? max(u->mx_of_2, u->rs->mx_of_2) : u->mx_of_2;

            // update l_val_of_2
            // 1. ls->l_val_of_2 (size_ls > 1)
            // 2. ls_val + rs_l_val (size_ls == 1)
            u->l_val_of_2 = (u->ls->size() > 1) ? u->ls->l_val_of_2 : u->ls->l_val + u->rs->l_val;

            // update r_val_of_2
            // same as l_val_of_2
            u->r_val_of_2 = (u->rs->size() > 1) ? u->rs->r_val_of_2 : u->ls->r_val + u->rs->r_val;

            if(u->size() < 3){
                return;
            }
            // update mx_of_3
            // 1. ls->mx_3 (size_ls > 2)
            // 2. rs->mx_3 (size_rs > 2)
            // 3. ls->r_mx_2 + rs->l_val (size_ls > 1)
            // 4. ls->r_val + rs->l_mx_2 (size_rs > 1)
            u->mx_of_3 = (u->ls->size() > 1) ?
                                             u->ls->r_val_of_2 + u->rs->l_val :
                                             u->ls->r_val + u->rs->l_val_of_2; // deal with undefined mx_of_3
            u->mx_of_3 = (u->rs->size() > 1) ? max(u->mx_of_3, u->ls->r_val + u->rs->l_val_of_2) : u->mx_of_3;
            u->mx_of_3 = (u->ls->size() > 2) ? max(u->mx_of_3, u->ls->mx_of_3) : u->mx_of_3;
            u->mx_of_3 = (u->rs->size() > 2) ? max(u->mx_of_3, u->rs->mx_of_3) : u->mx_of_3;

            // update l_val_of_3
            // 1. ls->l_val_of_3 (size_ls > 2)
            // 2. ls->l_val_of_2 + rs->l_val (size_ls == 2)
            // 3. ls->l_val + rs->l_val_of_2 (size_ls == 1)
            switch(u->ls->size()){
                case 1:
                    u->l_val_of_3 = u->ls->l_val + u->rs->l_val_of_2;
                    break;
                case 2:
                    u->l_val_of_3 = u->ls->l_val_of_2 + u->rs->l_val;
                    break;
                default:
                    u->l_val_of_3 = u->ls->l_val_of_3;
            }

            // update r_val_of_3
            // same as l_val_of_3
            switch(u->rs->size()){
                case 1:
                    u->r_val_of_3 = u->ls->r_val_of_2 + u->rs->r_val;
                    break;
                case 2:
                    u->r_val_of_3 = u->ls->r_val + u->rs->r_val_of_2;
                    break;
                default:
                    u->r_val_of_3 = u->rs->r_val_of_3;
            }

        }

        void build(Node *u, int l, int r, const int *data){
            static int cnt = 1;
            u->l = l, u->r = r;
            if(l == r){
                u->l_val = u->r_val = data[l];
                return;
            }
            const int mid = (l+r)/2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid, data);
            build(u->rs, mid+1, r, data);
            update(u);
        }

        static void update(Node *u, long long val){
            switch(u->size() > 3 ? 3 : u->size()){
                case 3:
                    u->mx_of_3 += val * 3;
                    u->l_val_of_3 += val * 3;
                    u->r_val_of_3 += val * 3;
                case 2:
                    u->mx_of_2 += val * 2;
                    u->l_val_of_2 += val * 2;
                    u->r_val_of_2 += val * 2;
                case 1:
                    u->l_val += val;
                    u->r_val += val;
                    u->tag += val;
                    break;
                default:
                    throw exception();
            }
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
            update(u);
        }

        static Node query(Node *u, int l, int r){
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

            Node fa{max(l, u->l), min(r, u->r)};
            fa.ls = &ls, fa.rs = &rs;
            update(&fa);
            return fa;
        }

    public:
        SegTree(int n, const int *data){
            build(&node[1], 1, n, data);
        }

        void add(const int l, const int r, const int val){
            add(&node[1], l, r, val);
        }

        pair<long long, int> query(const int l, const int r){
            static Node res;
            res = query(&node[1], l, r);
            if((double)res.mx_of_2/2.0 >= (double)res.mx_of_3/3.0 || res.size() < 3){
                return {res.mx_of_2, 2};
            }else{
                return {res.mx_of_3, 3};
            }
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
        static int opt, l, r, x;
        static pair<long long, int> ans;
        read(opt), read(l), read(r);
        switch(opt){
            case 1:
                read(x);
                tree.add(l, r, x);
                break;
            case 2:
                ans = tree.query(l, r);
                if(ans.first == 0){
                    ans.second = 1;
                }else if(ans.first % ans.second == 0){
                    ans.first /= ans.second;
                    ans.second = 1;
                }
                printf("%lld/%d\n", ans.first, ans.second);
                break;
            default:
                throw exception();
        }
    }

}

 * */