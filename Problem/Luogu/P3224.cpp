//
// Created by Kibi on 24-6-23.
//

// TODO 数据过水？没用启发式合并也过了

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(random_device{}());

class FhqTreeNode{
    using Node = FhqTreeNode;

    unsigned int rnk, siz;
    Node *ls, *rs, *fa;

    FhqTreeNode(int id, int val):rnk(rnd()), siz(1), ls(nullptr), rs(nullptr), fa(nullptr), id(id), val(val){}

public:
    int id;
    const int val;

    bool operator < (Node &v) const {
        return rnk < v.rnk;
    }

    static Node* new_node(int id, int val){
        return new Node(id, val);
    }

    static unsigned int size(Node* u){
        return u ? u->siz : 0;
    }

    void upd_size(){
        siz = size(ls) + size(rs) + 1;
    }

    void split(int k, Node *&l, Node *&r){
        if(val <= k){
            l = this;
            rs ? rs->split(k, rs, r) : (void)(r = nullptr);
            rs ? rs->fa = this : nullptr;
        }else{
            r = this;
            ls ? ls->split(k, l, ls) : (void)(l = nullptr);
            ls ? ls->fa = this : nullptr;
        }
        upd_size();
    }

    static Node* merge(Node *ls, Node *rs){
        if((!ls) || (!rs)){
            return ls ? ls : rs;
        } else if(*ls < *rs){
            ls->rs = merge(ls->rs, rs);
            ls->rs->fa = ls;
            ls->upd_size();
            return ls;
        }else {
            rs->ls = merge(ls, rs->ls);
            rs->ls->fa = rs;
            rs->upd_size();
            return rs;
        }
    }

    Node* query_by_rnk(unsigned int k){
        if(k == size(ls) + 1){
            return this;
        }else if(k <= size(ls)){
            return ls->query_by_rnk(k);
        }else {
            return rs->query_by_rnk(k - size(ls) - 1);
        }
    }

    Node* get_rt(){
        return fa ? fa->get_rt() : this;
    }
};

int main(){
    using Node = FhqTreeNode;

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

    auto readChar = [](int &x){
        int c = getchar();
        while(c != 'Q' && c != 'B'){
            c = getchar();
        }
        x = c;
    };

//    freopen("../IO/Luogu/P3224/P3224_10.in", "r", stdin);

    int n, m;
    read(n), read(m);

    static vector<Node*> node(n);
    for (auto &i : node){
        int val;
        read(val);
        i = Node::new_node((int)(&i - &node[0]), val);
    }

    auto merge = [](Node *u, Node *v){
        auto lrt = u->get_rt(), rrt = v->get_rt();
        if(lrt == rrt){
            return;
        }else if(Node::size(lrt) < Node::size(rrt)){
            swap(lrt, rrt);
        }
        Node *a, *b;
        lrt->split(rrt->val, a, b);
        Node::merge(Node::merge(a, rrt), b);
    };

    auto query = [](Node *u, unsigned int k){
        auto rt = u->get_rt();
        return Node::size(rt) >= k ? rt->query_by_rnk(k)->id : -2;
    };

    while(m--){
        int u, v;
        read(u), read(v);
        if(!u || !v){
            continue;
        }
        u--, v--;
        merge(node[u], node[v]);
    }

    int q;
    read(q);

    while(q--){
        int op, x, y;
        readChar(op), read(x), read(y);
        switch (op){
            case 'B':
                x--, y--;
                merge(node[x], node[y]);
                break;
            case 'Q':
                x--;
                printf("%d\n", query(node[x], y) + 1);
                break;
            default:
                throw runtime_error("Error op!");
        }
    }

//    fclose(stdin);
}