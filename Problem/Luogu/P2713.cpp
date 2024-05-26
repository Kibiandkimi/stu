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

    auto read_str = [](int &x){
        auto judge = [](int c){
            return c == 'M' || c == 'K';
        };
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        x = c;
    };

    class LeftistTree{
    public:
        class Node{
        public:
            int id{}, val{}, dis{1};
            Node *ls{nullptr}, *rs{nullptr};
            bool vis{false};
        };

        static Node* merge(Node *x, Node *y){
            if(!x || !y){
                return x ? x : y;
            }
            if(x->vis || y->vis){
                throw runtime_error("LeftistTree::Error within a recursive call chain in merge!");
            }
            if(x->val > y->val){
                swap(x, y);
            }
            x->vis = true;
            x->rs = merge(x->rs, y);
            x->vis = false;
            if(!x->ls || x->rs->dis > x->ls->dis){
                swap(x->ls, x->rs);
            }
            x->dis = x->rs ? x->rs->dis + 1 : 1;
            return x;
        }

        static Node* del_rt(Node *x){
            auto ret = merge(x->ls, x->rs);
            //            delete x;
            return ret;
        }
    };

    class DSU{
    public:
        //        int id;
        LeftistTree::Node node;
        DSU *fa{this};
        bool vis{false};

        DSU* find(){
            if(vis){
                throw runtime_error("DSU::Error within a recursive call chain in find fa!");
            }
            vis = true;
            if(fa != this){
                fa = fa->find();
            }
            vis = false;
            return fa;
        }
    };

    int n;
    read({&n});

    DSU dsu[n];
    for(int i = 0; i < n; i++){
        read({&dsu[i].node.val});
        dsu[i].node.id = i;
    }

    //    DSU died{-1};
    bool died[n];
    memset(died, 0, sizeof died);

    int m;
    read({&m});

    while(m--){
        int opt, x, y;
        LeftistTree::Node* res;
        read_str(opt);
        switch(opt){
            case 'M':
                read({&x, &y});
                x--, y--;
                if(died[dsu[x].node.id] || died[dsu[y].node.id] || x == y || dsu[x].find()->node.id == dsu[y].find()->node.id){
                    continue;
                }
                res = LeftistTree::merge(&dsu[x].find()->node, &dsu[y].find()->node);
                if(res == &dsu[x].find()->node){
                    dsu[y].find()->fa = dsu[x].find();
                }else{
                    dsu[x].find()->fa = dsu[y].find();
                }
                break;
            case 'K':
                read({&x});
                x--;
                if(died[dsu[x].node.id]){
                    printf("0\n");
                    continue;
                }
                printf("%d\n", dsu[x].find()->node.val);
                res = LeftistTree::del_rt(&dsu[x].find()->node);
                died[dsu[x].find()->node.id] = true;
                if(!res){
                    continue;
                }
                dsu[x].find()->fa = &dsu[res->id];
                dsu[res->id].fa = &dsu[res->id];
                break;
            default:
                throw runtime_error("Error operation code!");
        }
    }
}