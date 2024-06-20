//
// Created by kibi on 2022/8/5.
//
//old在上面, new在下面, details看git, twice在最下

/*
#include <bits/stdc++.h>
using namespace std;
int n, root;
int val[100005], rnk[100005], siz[100005], son[100005][2], cnt, num[100005];

int new_node(int x){
    val[++cnt] = x;
    rnk[cnt] = rand();
    siz[cnt] = 1;
    num[cnt] = 1;
    return cnt;
}

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

void splite(int &x, int &y, int k, int pos){
    if(!pos){
        x = 0, y = 0;
    }else{
        if(val[pos] <= k){
            x = pos;
            splite(son[pos][1], y, k, son[pos][1]);
        }else{
            y = pos;
            splite(x, son[pos][0], k, son[pos][0]);
        }
        update(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else{
        if(rnk[x] < rnk[y]){
            son[x][1] = merge(son[x][1], y);
            update(x);
            return x;
        }else{
            son[y][0] = merge(x, son[y][0]);
            update(y);
            return y;
        }
    }
}

void insert(int x){
    int l, r;
    splite(l, r, x, root);
    int tl = 0, tr = 0;
    splite(tl, tr, x-1, l);
    if(!tr){
        //        merge(merge(l, new_node(x)), r);
        root = merge(merge(tl, new_node(x)), r);
    }else{
        num[tr]++;
        update(tr);
        root = merge(merge(tl, tr), r);
    }

}

void del(int x){
    int l, r;
    splite(l, r, x, root);
    int tl = 0, tr = 0;
    splite(tl, tr, x-1, l);
    if(num[tr]>1){
        num[tr]--;
        update(tr);
        merge(tl, tr);
    }else{
        if(l == tr){
            l = 0;
        }

    }
}

int query_rk(int x){

}

int query_x(int x){

}

int query_pre(int x){

}

int query_nxt(int x){

}

int main(){
    srand((unsigned)time(nullptr));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int op, x;
        scanf("%d %d", &op, &x);
        switch (op) {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                printf("%d\n", query_rk(x));
                break;
            case 4:
                printf("%d\n", query_x(x));
                break;
            case 5:
                printf("%d\n", query_pre(x));
                break;
            case 6:
                printf("%d\n", query_nxt(x));
        }
    }
}
*/

/*
#include <bits/stdc++.h>
using namespace std;
int n, root;
int val[100005], rnk[100005], siz[100005], son[100005][2], cnt, num[100005];

int new_node(int x){
    val[++cnt] = x;
    rnk[cnt] = rand();
    siz[cnt] = 1;
    num[cnt] = 1;
    return cnt;
}

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

void splite(int &x, int &y, int k, int pos){
    if(!pos){
        x = 0, y = 0;
    }else{
        if(val[pos] <= k){
            x = pos;
            splite(son[pos][1], y, k, son[pos][1]);
        }else{
            y = pos;
            splite(x, son[pos][0], k, son[pos][0]);
        }
        update(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else{
        if(rnk[x] < rnk[y]){
            son[x][1] = merge(son[x][1], y);
            update(x);
            return x;
        }else{
            son[y][0] = merge(x, son[y][0]);
            update(y);
            return y;
        }
    }
}

void insert(int x){
    int l, r;
    splite(l, r, x, root);
    root = merge(merge(l, new_node(x)), r);
}

void del(int x){
    int l, r, t;
    splite(l, t, x, root);
    splite(l, r, x-1, l);
    r = merge(son[r][0], son[r][1]);
    root = merge(merge(l, r), t);
}

int query_rk(int x){
    int l, r;
    splite(l, r, x-1, root);
    int res = siz[l]+1;
    merge(l, r);
    return res;
}

int query_x(int x){
    int pos = root;
    while(true){
        if(siz[son[pos][0]] >= x){
            pos = son[pos][0];
        }else{
            if(siz[son[pos][0]] + 1 == x){
                return pos;
            }else{
                x -= siz[son[pos][0]] + 1;
                pos = son[pos][1];
            }
        }
    }
}

int query_pre(int x){
    int l, r;
    splite(l, r, x-1, root);
    int t = root;
    root = l;
    int res = val[query_x(siz[l])];
    root = t;
    root = merge(l, r);
    return res;
}

int query_nxt(int x){
    int l, r;
    splite(l, r, x, root);
    int t = root;
    root = r;
    int res = val[query_x(1)];
    root = t;
    root = merge(l, r);
    return res;
}

int main(){
    srand((unsigned)time(nullptr));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int op, x;
        scanf("%d %d", &op, &x);
        switch (op) {
            case 1:
                insert(x);
                break;
            case 2:
                del(x);
                break;
            case 3:
                printf("%d\n", query_rk(x));
                break;
            case 4:
                printf("%d\n", val[query_x(x)]);
                break;
            case 5:
                printf("%d\n", query_pre(x));
                break;
            case 6:
                printf("%d\n", query_nxt(x));
        }
    }
}
*/

/*
#include <bits/stdc++.h>
using namespace std;
int n, val[100005], son[100005][2], siz[100005], rnk[100005], root, cnt;

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

void splite(int &x, int &y, int k, int pos){
    if(!pos){
        x = 0, y = 0;
    }else{
        if(val[pos] <= k){
            x = pos;
            splite(son[pos][1], y, k, son[pos][1]);
        }else{
            y = pos;
            splite(x, son[pos][0], k, son[pos][0]);
        }
        update(pos);
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }
    if(rnk[x] < rnk[y]){
        son[x][1] = merge(son[x][1], y);
        update(x);
        return x;
    }else{
        son[y][0] = merge(x, son[y][0]);
        update(y);
        return y;
    }
}

int new_node(int x){
    val[++cnt] = x;
    siz[cnt] = 1;
    rnk[cnt] = rand();
    return cnt;
}

int qrk(int k, int pos){
    //    int pos = root;
    while(true){
        if(siz[son[pos][0]] >= k){
            pos = son[pos][0];
        }else if(siz[son[pos][0]]+1==k){
            return pos;
        }else{
            k -= siz[son[pos][0]] + 1;
            pos = son[pos][1];
        }
    }
}

int main(){
    srand((unsigned)time(nullptr));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        int opt, x;
        scanf("%d %d", &opt, &x);
        int l, r, t;
        switch (opt) {
            case 1:
                splite(l, r, x, root);
                root = merge(merge(l, new_node(x)), r);
                break;
            case 2:
                //                int l, t, r;
                splite(l, t, x, root);
                splite(l, r, x-1, l);
                r = merge(son[r][0], son[r][1]);
                root = merge(merge(l, r), t);
                break;
            case 3:
                splite(l, r, x-1, root);
                printf("%d\n", siz[l]+1);
                root = merge(l, r);
                break;
            case 4:
                printf("%d\n", val[qrk(x, root)]);
                break;
            case 5:
                splite(l, r, x-1, root);
                printf("%d\n", val[qrk(siz[l], l)]);
                root = merge(l, r);
                break;
            case 6:
                splite(l, r, x, root);
                printf("%d\n", val[qrk(1, r)]);
                root = merge(l, r);
                break;
        }
    }
}
 */

// 24-6-20

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(random_device{}());

// TODO 24-6-20
class FhqTreapNode {
    using Node = FhqTreapNode;

    unsigned int rnk;
    FhqTreapNode *ls, *rs;
    int siz;

    FhqTreapNode(unsigned int rnk, int val, int id) : rnk(rnk), ls(nullptr), rs(nullptr), val(val), siz(1), id(id) {}

public:
    int id;
    const int val;

    static Node *new_node(int id, int val) {
        return new Node{rnd(), val, id};
    }

    void upd_siz() {
        siz = 1 + (ls ? ls->siz : 0) + (rs ? rs->siz : 0);
    }

    bool operator<=(const int &t) const {
        return val <= t;
    }

    bool operator<(const Node &t) const {
        return rnk < t.rnk;
    }

    static int size(Node *u) {
        return u ? u->siz : 0;
    }

    void split(int k, Node *&l, Node *&r) {
        if (val <= k) {
            l = this;
            rs ? rs->split(k, rs, r) : (void) (r = nullptr);
        } else {
            r = this;
            ls ? ls->split(k, l, ls) : (void) (l = nullptr);
        }
        upd_siz();
    }

    void split_(int k, Node *&l, Node *&r) {
        stack<tuple<Node *, Node *&, Node *&>> stk;
        stack<Node *> changed;
        stk.emplace(this, l, r);
        while (!stk.empty()) {
            auto [now, tl, tr] = stk.top();
            changed.emplace(now);
            stk.pop();
            if (*now <= k) {
                tl = now;
                now->rs ? stk.emplace(now->rs, now->rs, tr) : (void) (tr = nullptr);
            } else {
                tr = now;
                now->ls ? stk.emplace(now->ls, tl, now->ls) : (void) (tl = nullptr);
            }
        }
        while (!changed.empty()) {
            changed.top()->upd_siz();
            changed.pop();
        }
    }

    static Node *merge(Node *l, Node *r) {
        if (!(l && r)) {
            return l ? l : r;
        } else if (l < r) {
            l->rs = merge(l->rs, r);
            l->upd_siz();
            return l;
        } else {
            r->ls = merge(l, r->ls);
            r->upd_siz();
            return r;
        }
    }

    static Node *merge_(Node *&l, Node *&r) {
        stack<tuple<Node *&, Node *&, Node *&>> stk;// l, r, res
        stack<Node *> changed;
        Node *res = nullptr;
        stk.emplace(l, r, res);
        while (stk.empty()) {
            auto [tl, tr, tres] = stk.top();
            stk.pop();
            if (!(tl && tr)) {
                tres = tl ? tl : tr;
            } else if (tl < tr) {
                stk.emplace(tl->rs, tr, tl->rs);
                changed.emplace(tl);
                tres = tl;
            } else {
                stk.emplace(tl, tr->ls, tr->ls);
                changed.emplace(tr);
                tres = tr;
            }
        }
        return res;
    }

    Node *query_by_rnk(int k) {
        if (size(ls) == k - 1) {
            return this;
        } else if (ls && size(ls) > k - 1) {
            return ls->query_by_rnk(k);
        } else {
            return rs->query_by_rnk(k - size(ls) - 1);
        }
    }

    Node *query_by_rnk_(int k) {
        auto now = this;
        while (k - 1 != size(ls)) {
            if ((ls ? ls->siz : 0) > k - 1) {
                now = ls;
            } else {
                k -= size(ls) + 1;
                now = rs;
            }
        }
        return now;
    }

    Node *separate_son(){
        Node *tl = ls, *tr = rs;
        ls = nullptr, rs = nullptr, siz = 1;
        return merge(tl, tr);
    }
};

class FhqTreapTools{
    using Node = FhqTreapNode;
public:
    static Node* add_node(Node *rt, Node* node){
        if(!rt){
            return node;
        }
        Node *a = nullptr, *b = nullptr;
        rt->split(node->val, a, b);
        a = Node::merge(a, node);
        return Node::merge(a, b);
    }

    static Node* remove_node(Node *&rt, int k){
        Node *a = nullptr, *b = nullptr, *res = nullptr;
        rt->split(k, a, b);
        a->split(k - 1, a, res);
        a = Node::merge(a, res->separate_son());
        rt = Node::merge(a, b);
        return res;
    }

    static int query_rnk(Node *rt, int k){
        Node *a = nullptr, *b = nullptr;
        rt->split(k - 1, a, b);
        int res = Node::size(a) + 1;
        Node::merge(a, b);
        return res;
    }

    static Node* query_pre(Node *rt, int k){
        Node *a = nullptr, *b = nullptr;
        rt->split(k - 1, a, b);
        Node *res = a->query_by_rnk(Node::size(a));
        Node::merge(a, b);
        return res;
    }

    static Node* query_suc(Node *rt, int k){
        Node *a = nullptr, *b = nullptr;
        rt->split(k, a, b);
        Node *res = b->query_by_rnk(1);
        Node::merge(a, b);
        return res;
    }
};

int main(){
    using FTN = FhqTreapNode;
    using FTT = FhqTreapTools;

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

    int n;
    read(n);

    FTN *rt = nullptr;

    int temp = 0;

    while(n--){
        int opt, x;
        read(opt), read(x);
        switch(opt){
            case 1:
                rt = FTT::add_node(rt, FTN::new_node(n, x));
                assert(FTN::size(rt) == ++temp);
                break;
            case 2:
                FTT::remove_node(rt, x);
                assert(FTN::size(rt) == --temp);
                break;
            case 3:
                printf("%d\n", FTT::query_rnk(rt, x));
                break;
            case 4:
                printf("%d\n", rt->query_by_rnk(x)->val);
                break;
            case 5:
                printf("%d\n", FTT::query_pre(rt, x)->val);
                break;
            case 6:
                printf("%d\n", FTT::query_suc(rt, x)->val);
                break;
            default:
                throw runtime_error("Error opt!");
        }
    }

}