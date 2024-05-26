//
// Created by kibi on 22-8-9.
//
#include <bits/stdc++.h>
using namespace std;
int n, m, cnt, root;
int val[100005], rnk[100005], son[100005][2], siz[100005];
bool flag[100005];

void update(int x){
    siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
}

void push_down(int x){
    if(flag[x]){
        swap(son[x][0], son[x][1]);
        flag[son[x][0]] ^= 1;
        flag[son[x][1]] ^= 1;
        flag[x] = false;
    }
}

int new_node(int x){
    val[++cnt] = x;
    rnk[cnt] = rand();
    siz[cnt] = 1;
    return cnt;
}

void split(int &x, int &y, int k, int pos){
    if(!pos){
        x = y = 0;
    }else{
        push_down(pos);
        if(siz[son[pos][0]] >= k){
            y = pos;
            split(x, son[pos][0], k, son[pos][0]);
            update(y);
        }else{
            x = pos;
            split(son[pos][1], y, k-siz[son[pos][0]]-1, son[pos][1]);
            update(x);
        }
    }
}

int merge(int x, int y){
    if(!(x&&y)){
        return x+y;
    }else{
        if(rnk[x] < rnk[y]){
            push_down(x);
            son[x][1] = merge(son[x][1], y);
            update(x);
            return x;
        }else{
            push_down(y);
            son[y][0] = merge(x, son[y][0]);
            update(y);
            return y;
        }
    }
}

void f(int pos){
    push_down(pos);
    if(son[pos][0]){
        f(son[pos][0]);
    }
    printf("%d ", val[pos]);
    if(son[pos][1]){
        f(son[pos][1]);
    }
}


int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++){
        root = merge(root, new_node(i));
    }
    for(int i = 1; i <= m; i++){
        // f(root);
        int l, r;
        scanf("%d %d", &l, &r);
        int x, y, z;
        split(x, y, l-1, root);
        split(y, z, r-l+1, y);
        flag[y] ^= 1;
        root = merge(x, merge(y, z));
        // printf("\n");
    }
    f(root);
}



/* 2023 - 7 - 5
 *
#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(random_device{}());
const int N = 100000, M = 100000;

void read(int &x);

class fhq_treap{
    int val[N+5], rnk[N+5], ls[N+5], rs[N+5], siz[N+5], size;
    bool flag[N+5];
    void update(int u){
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    }
    void push_down(int u){
        if(flag[u]){
            swap(ls[u], rs[u]);
            flag[ls[u]] ^= 1;
            flag[rs[u]] ^= 1;
            flag[u] = false;
        }
    }
public:
    int new_node(int v){
        val[++size] = v;
        rnk[size] = (int)rnd();
        siz[size] = 1;
        return size;
    }

    void split(int &x, int &y, int k, int rt){
        if(!rt){
            x = y = 0;
            return ;
        }
        push_down(rt);
        if(siz[ls[rt]] >= k){
            y = rt;
            split(x, ls[rt], k, ls[rt]);
            update(y);
        }else{
            x = rt;
            split(rs[rt], y, k-siz[ls[rt]]-1, rs[rt]);
            update(x);
        }
    }

    int merge(int x, int y){
        if(!(x&&y)){
            return x+y;
        }
        if(rnk[x] < rnk[y]){
            push_down(x);
            rs[x] = merge(rs[x], y);
            update(x);
            return x;
        }else{
            push_down(y);
            ls[y] = merge(x, ls[y]);
            update(y);
            return y;
        }
    }

    void reverse(int u){
        flag[u] ^= 1;
    }

    void work_out(int u){
        push_down(u);
        if(siz[ls[u]]){
            work_out(ls[u]);
        }
        printf("%d ", val[u]);
        if(siz[rs[u]]){
            work_out(rs[u]);
        }
    }
};

int main(){
    int n, m, root;
    static fhq_treap tree;

    read(n), read(m);

    root = 0;
    for(int i = 1; i <= n; i++){
        root = tree.merge(root, tree.new_node(i));
    }

    while(m--){
        int l, r;
        read(l), read(r);
        int x, y, z;
        tree.split(x, y, l-1, root);
        tree.split(y, z, r-l+1, y);
        tree.reverse(y);
        root = tree.merge(x, tree.merge(y, z));
    }

    tree.work_out(root);
}

void read(int &x){
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

 * */