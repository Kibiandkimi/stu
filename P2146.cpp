//
// Created by kibi on 2022/6/24.
//
//树链刨分
#include <bits/stdc++.h>
using namespace std;
struct Node{
    //    bool f;
    int sum, lazy, l, r, ls, rs;
}node[200005];
int n, q, d[100005], f[100005], size[100005], son[100005], top[100005], id[100005], rk[100005], cnt, rt;
vector<int> e[100005];
void f1(int u, int dep, int fa){
    d[u] = dep;
    f[u] = fa;
    size[u] = 1;
    int se = e[u].size();
    for(int i = 0; i < se; i++){
        int v = e[u][i];
        if(v == fa){
            continue;
        }
        f1(v, dep+1, u);
        size[u] += size[v];
        if(size[v] > size[son[u]]||!son[u]){
            son[u] = v;
        }
    }
}
void f2(int u, int t){
    top[u] = t;
    id[u] = ++cnt;
    rk[cnt] = u;
    if(!son[u]){
        return ;
    }
    f2(son[u], t);
    int se = e[u].size();
    for(int i = 0; i < se; i++){
        int v = e[u][i];
        if(v!=son[u] && v!=f[u]){
            f2(v, v);
        }
    }
}

void push_up(int cur){
    node[cur].sum = node[node[cur].ls].sum + node[node[cur].rs].sum;
    node[cur].l = node[node[cur].ls].l;
    node[cur].r = node[node[cur].rs].r;
}
void build(int l, int r, int cur){
    if(l == r){
        node[cur].lazy = node[cur].ls = node[cur].rs = -1;
        node[cur].l = node[cur].r = l;
        return;
    }
    node[cur].ls = cnt++;
    node[cur].rs = cnt++;
    int mid = (l+r)/2;
    build(l, mid, node[cur].ls);
    build(mid+1, r, node[cur].rs);
    push_up(cur);
}
void push_down(int cur){
    int ls = node[cur].ls, rs = node[cur].rs;
    node[ls].sum = node[cur].lazy * (node[ls].r - node[ls].l + 1);
    node[rs].sum = node[cur].lazy * (node[rs].r - node[rs].l + 1);
    node[ls].lazy = node[rs].lazy = node[cur].lazy;
    node[cur].lazy = -1;
}
void update(int l, int r, int cur, bool fl){
    if(l <= node[cur].l && node[cur].r <= r){
        node[cur].sum = fl * (node[cur].r - node[cur].l + 1);
        node[cur].lazy = fl;
        return;
    }
    if(node[cur].lazy != -1){
        push_down(cur);
    }
    int mid = (node[cur].l + node[cur].r)/2;
    if(l <= mid){
        update(l, r, node[cur].ls, fl);
    }
    if(mid < r){
        update(l, r, node[cur].rs, fl);
    }
    push_up(cur);
}
int query(int l, int r, int cur){
    if(l <= node[cur].l && node[cur].r <= r){
        return node[cur].sum;
    }
    if(node[cur].lazy != -1){
        push_down(cur);
    }
    int tot = 0;
    int mid = (node[cur].l + node[cur].r)/2;
    if(l <= mid){
        tot += query(l, r, node[cur].ls);
    }
    if(mid < r){
        tot += query(l, r, node[cur].rs);
    }
    return tot;
}

int sum(int x){
    int tot = 0;
    int fx = top[x];
    while(fx){
        tot += id[x]-id[fx]- query(id[fx], id[x], rt) + 1;
        update(id[fx], id[x], rt, true);
        x = f[fx], fx = top[x];
    }
    tot += id[x] - id[0] - query(id[0], id[x], rt) + 1;
    update(id[0], id[x], rt, true);
    return tot;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        int x;
        scanf("%d", &x);
        e[x].push_back(i);
        e[i].push_back(x);
    }
    cnt = 0;
    f1(0, 1, -1);
    f2(0, 0);
    cnt = 0;
    rt = cnt++;
    build(1, n, rt);
    scanf("%d", &q);
    while(q--){
        char c[20];
        int x;
        scanf("%s", c);
        scanf("%d", &x);
        if(c[0]=='i'){
            printf("%d\n", sum(x));
        }else if(c[0] == 'u'){
            printf("%d\n", query(id[x], id[x]+size[x]-1, rt));
            update(id[x], id[x]+size[x]-1, rt, false);
        }
    }
}