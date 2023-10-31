//
// Created by kibi on 23-10-31.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;
    class Tools{
    public:
        static int void read(int &x){
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
    };

    class SegTree{
        class Node{
        public:
            int dep;
            ll lmx, rmx, mx, sum;
            Node *ls, *rs;
        };

        Node *rt;
        int n;

        void update(){
            u->lmx = max(u->ls->lmx, u->ls->sum + u->rs->lmx);
            u->rmx = max(u->rs->rmx, u->rs->sum + u->ls->rmx);
            u->mx = max({u->ls->mx, u->rs->mx, u->ls->rmx + u->rs->lmx});
            u->sum = u->ls->sum + u->rs->sum;
        }

        void build(Node *u, int dep, int l, int *data){
            u->dep = dep;
            if(dep == n){
                u->lmx = u->rmx = u->mx = u->sum = data[l];
                return ;
            }

            u->ls = new Node, u->rs = new Node;
            build(u->ls, dep + 1, l, data);
            build(u->rs, dep + 1, l + (1 << (n - dep - 1)), data);
            u->update();
        }

    public:
        SegTree(int n, int *data):n(n){
            rt = new Node{1, 0, 0, 0, 0, nullptr, nullptr};
            build(rt, 2, 1, data);
        }


    };

    auto read = Tools::read;

    int n;
    read(n);

    int raw_data[(1 << n)];
    for(auto &i : raw_data){
        read(i);
    }


}