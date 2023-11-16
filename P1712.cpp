//
// Created by kibi on 23-11-16.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

    class Interval{
    public:
        int l, r, mpl, mpr;
    };

    class SegTree{
        class Node{
        public:
            int l, r, sum, tag;
            Node *ls, *rs;
        };

        using ns = pair<Node*, int>;

        Node *rt{nullptr};

        static void update(Node *u){
            u->sum = max(u->ls->sum, u->rs->sum) + u->tag;
        }

    public:
        explicit SegTree(int n){
            rt = new Node{1, n};
            stack<ns> stk;
            stk.emplace(rt, 1);
            while(!stk.empty()){
                auto now = stk.top();
                stk.pop();
                auto u = now.first;
                auto sta = now.second;
                switch(sta){
                    case 1:
                        if(u->l == u->r){
                            u->sum = u->tag = 0;
                        }else{
                            stk.emplace(u, 2);
                            u->ls = new Node{u->l, (u->l + u->r) >> 1};
                            u->rs = new Node{((u->l + u->r) >> 1) + 1, u->r};
                            stk.emplace(u->ls, 1);
                            stk.emplace(u->rs, 1);
                        }
                        break;
                    case 2:
                        update(u);
                        break;
                    default:
                        throw runtime_error("Error status code!");
                }
            }
        }

        static void update(Node *u, int val){
            u->tag += val;
            u->sum += val;
        }

        void modify(int l, int r, int val){
            stack<ns> stk;
            stk.emplace(rt, 1);
            while(!stk.empty()){
                auto now = stk.top();
                stk.pop();
                auto u = now.first;
                auto stat = now.second;
                switch(stat){
                    case 1:
                        if(l <= u->l && u->r <= r){
                            update(u, val);
                        }else{
                            stk.emplace(u, 2);
                            if(l <= u->ls->r){
                                stk.emplace(u->ls, 1);
                            }
                            if(r >= u->rs->l){
                                stk.emplace(u->rs, 1);
                            }
                        }
                        break;
                    case 2:
                        update(u);
                        break;
                    default:
                        throw runtime_error("Error status code!");
                }
            }
        }

        int query_(){
            return rt->sum;
        }
    };

    int n, m;
    read({&n, &m});

    vector<pair<int, int>> tem;
    Interval interval[n];
    for(auto &i : interval){
        read({&i.l, &i.r});
    }

    for(int i = 0; i < n; i++){
        tem.emplace_back(interval[i].l, i);
        tem.emplace_back(interval[i].r, i + n);
    }

    int cnt = 0;
    sort(tem.begin(), tem.end());
    for(auto &i : tem){
        static int lst = -1;
        if(i.first != lst){
            if(i.second >= n){
                interval[i.second - n].mpr = ++cnt;
            }else{
                interval[i.second].mpl = ++cnt;
            }
            lst = i.first;
        }else {
            if (i.second >= n) {
                interval[i.second - n].mpr = cnt;
            } else {
                interval[i.second].mpl = cnt;
            }
        }
    }

    sort(interval, interval + n, [](const Interval &x, const Interval &y){
        return x.r - x.l < y.r - y.l;
    });

    int ans = -1;
    SegTree tree(cnt);
    for(int l = 0, r = -1; r + 1 < n;){
        while(r + 1 < n && tree.query_() < m){
            ++r;
            tree.modify(interval[r].mpl, interval[r].mpr, 1);
        }
        if(tree.query_() < m){
            break;
        }
        while(tree.query_() >= m && l <= r){
            tree.modify(interval[l].mpl, interval[l].mpr, -1);
            l++;
        }
        int res = interval[r].r - interval[r].l - interval[l - 1].r + interval[l - 1].l;
        ans = (ans == -1 ? res : min(res, ans));
    }

    printf("%d\n", ans);
}