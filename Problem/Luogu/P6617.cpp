//
// Created by kibi on 23-8-15.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int N = 500000;

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

        static int pre(int w, int x, const set<int> *s, const int *r){
            auto it1 = s[r[x]].lower_bound(x), it2 = s[w-r[x]].lower_bound(x);
            if(it2 == s[w-r[x]].begin()){
                return 0;
            }else if(it1 == s[r[x]].begin()){
                return *(--it2);
            }else if(*(--it1) > *(--it2)){
                return 0;
            }else{
                return *it2;
            }
        }

        static void calc_need_update(int w, int pos, int &cnt, int *change, const int *raw, const set<int> *s){
            auto it = s[raw[pos]].upper_bound(pos);
            if(it != s[raw[pos]].end()){
                change[cnt++] = *it;
            }
            it = s[w - raw[pos]].upper_bound(pos);
            if(it != s[w - raw[pos]].end()){
                change[cnt++] = *it;
            }
        }
    };

    class SegTree{
        class Node{
        public:
            int l, r, val;
            Node *ls, *rs;
        };
        Node node[4 * N]{};

        static void update(Node *u) {
            u->val = max(u->ls->val, u->rs->val);
        }

        void build(Node *u, int l, int r, const int *data){
            static int cnt = 1;
            u->l = l, u->r = r;
            if(l == r){
                u->val = data[l];
                return;
            }
            const int mid = (l+r)/2;
            u->ls = &node[++cnt], u->rs = &node[++cnt];
            build(u->ls, l, mid, data);
            build(u->rs, mid+1, r, data);
            update(u);
        }

        static int query(Node *u, const int l, const int r){
            if(l <= u->l && u->r <= r){
                return u->val;
            }
            int res = 0;
            if(l <= u->ls->r){
                res = max(res, query(u->ls, l, r));
            }
            if(r >= u->rs->l){
                res = max(res, query(u->rs, l, r));
            }
            return res;
        }

    public:

        SegTree(int n, const int *data){
            build(&node[1], 1, n, data);
        }

        void modify(int x, int v){
            Node *u = &node[1];
            static Node *past[N + 5];
            int cnt = 0;
            while(u->l < u->r){
                past[cnt++] = u;
                if(x <= u->ls->r){
                    u = u->ls;
                }else{
                    u = u->rs;
                }
            }
            u->val = v;
            while(cnt){
                u = past[--cnt];
                update(u);
            }
        }

        int query(const int l, const int r){
            return query(&node[1], l, r);
        }

    };

    auto read = Tools::read;

    int n, m, w;

    read(n), read(m), read(w);

    static int raw_data[N + 5];
    for(int i = 1; i <= n; i++){
        read(raw_data[i]);
    }

    static set<int> set_of_pos[N + 5];

    static int data[N + 5];
    for(int i = 1; i <= n; i++){
        data[i] = Tools::pre(w, i, set_of_pos, raw_data);
        set_of_pos[raw_data[i]].insert(i);
    }

    static SegTree tree(n, data);

    int cnt_of_yes = 0;

    while(m--){
        int opt;
        read(opt);
        switch(opt){
            case 1:
                int pos, val;
                read(pos), read(val);

                static int change[5], cnt_of_change;
                cnt_of_change = 0;

                {
                    auto s = set_of_pos;

                    Tools::calc_need_update(w, pos, cnt_of_change, change, raw_data, s);

                    s[raw_data[pos]].erase(pos);
                    raw_data[pos] = val;
                    s[raw_data[pos]].insert(pos);
                    change[cnt_of_change++] = pos;

                    Tools::calc_need_update(w, pos, cnt_of_change, change, raw_data, s);

                    for (int i = 0; i < cnt_of_change; i++) {
                        tree.modify(change[i], Tools::pre(w, change[i], s, raw_data));
                    }
                }

                break;

            case 2:
                int l, r;
                read(l), read(r);
                l ^= cnt_of_yes, r ^= cnt_of_yes;
                if(tree.query(l, r) >= l){
                    printf("Yes\n");
                    ++cnt_of_yes;
                } else{
                    printf("No\n");
                }
                break;

            default:
                throw exception();
        }
    }

}