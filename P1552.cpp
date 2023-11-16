//
// Created by kibi on 23-11-16.
//

// TODO not finish

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

    class Data{
    public:
        int id, b, c, l, siz;
    };

    class LeftistTree{
    public:
        class Node : public Data{
        public:
            int dis{1};
            Node *ls{nullptr}, *rs{nullptr}, *rt{this};
        };

        static Node* merge(Node *x, Node *y){
            if(!x || !y){
                return x ? x : y;
            }
            if(x->c > y->c){
                swap(x, y);
            }
            x->rs = merge(x->rs, y);
            if(!x->ls || x->rs->dis > x->ls->dis){
                swap(x->ls, x->rs);
            }
            x->dis = x->rs ? x->rs->dis + 1 : 1;
            return x;
        }
    };

    int n, m;
    read({&n, &m});

    LeftistTree::Node node[n];

    for(int i = 0; i < n; i++){
        read({&node[i].b, &node[i].c, &node[i].l});
        node[i].b--;
        node[i].id = i;
    }

    for(int i = n - 1; i >= 0; i--){
        LeftistTree::merge(&node[i], &node[node[i].b]);
        node[node[i].b].siz += node[i].siz;

    }
}