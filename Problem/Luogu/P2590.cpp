//
// Created by kibi on 22-8-11.
//
#include <bits/stdc++.h>
using namespace std;
int n;
int siz[30005], son[30005], fa[30005], dep[30005];
int top[30005], id[30005], rnk[30005], cnt;
vector<int> g[30005];
int w[30005];
struct node{
    int l, r, ls, rs, v, mx/*, flag, siz*/;
}tr[240005];

void f1(int u){
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(g[u][i]!=fa[u]){
            fa[g[u][i]] = u;
            dep[g[u][i]] = dep[u]+1;
            f1(g[u][i]);
            siz[u] += siz[g[u][i]];
            son[u] = siz[son[u]] >= siz[g[u][i]] ? son[u] : g[u][i];
        }
    }
    siz[u] += 1;
}

void f2(int u, int t){
    top[u] = t;
    id[u] = ++cnt;
    rnk[cnt] = u;
    if(!son[u]){
        return ;
    }
    f2(son[u], t);
    int sg = g[u].size();
    for(int i = 0; i < sg; i++){
        if(!id[g[u][i]] && fa[u] != g[u][i]){
            f2(g[u][i], g[u][i]);
        }
    }
}

void build(int l, int r, int u){
    tr[u].l = l, tr[u].r = r;
    if(l == r){
        tr[u].v = w[rnk[l]];
        tr[u].mx = w[rnk[l]];
//        tr[u].siz = 1;
        return ;
    }
    int mid = (l+r)/2;
    build(l, mid, u*2);
    build(mid+1, r, u*2+1);
    tr[u].ls = u*2, tr[u].rs = u*2+1;
    tr[u].v = tr[tr[u].ls].v + tr[tr[u].rs].v;
    tr[u].mx = max(tr[tr[u].ls].mx, tr[tr[u].rs].mx);
//    tr[u].siz = tr[tr[u].ls].siz + tr[tr[u].rs].siz;
}

//void push_down(int x){
//    if(tr[x].flag){
//        tr[tr[x].ls].flag += tr[x].flag;
//        tr[tr[x].ls].v += tr[x].flag * tr[tr[x].ls].siz;
//        tr[tr[x].rs].flag += tr[x].flag;
//        tr[tr[x].rs].v += tr[x].flag * tr[tr[x].rs].siz;
//    }
//}

int query_sum(int l, int r, int u){
    if(l<=tr[u].l&&tr[u].r<=r){
        return tr[u].v;
    }
//    push_down(u);
    int ans = 0;
    if(l<=tr[tr[u].ls].r){
        ans += query_sum(l, r, tr[u].ls);
    }
    if(r>=tr[tr[u].rs].l){
        ans += query_sum(l, r, tr[u].rs);
    }
    return ans;
}

int query_mx(int l, int r, int u){
    if(l <= tr[u].l && tr[u].r <= r){
        return tr[u].mx;
    }
    int ans = -1e9;
    if(l <= tr[tr[u].ls].r){
        ans = max(ans, query_mx(l, r, tr[u].ls));
    }
    if(r >= tr[tr[u].rs].l){
        ans = max(ans, query_mx(l, r, tr[u].rs));
    }
    return ans;
}

void change(int x, int v, int u){
    if(tr[u].l == tr[u].r){
        tr[u].v = v;
        tr[u].mx = v;
        return ;
    }
    int mid = (tr[u].l+tr[u].r)/2;
    if(x <= mid){
        change(x, v, tr[u].ls);
    }else{
        change(x, v, tr[u].rs);
    }
    tr[u].v = tr[tr[u].ls].v + tr[tr[u].rs].v;
    tr[u].mx = max(tr[tr[u].ls].mx, tr[tr[u].rs].mx);
}

int sum(int x, int y){
    int ans = 0, fx = top[x], fy = top[y];
    while(fx != fy){
        if(dep[fx] >= dep[fy]){
            ans += query_sum(id[fx], id[x], 1);
            x = fa[fx];
            fx = top[x];
        }else{
            ans += query_sum(id[fy], id[y], 1);
            y = fa[fy];
            fy = top[y];
        }
    }
    if(dep[y] <= dep[x]){
        ans += query_sum(id[y], id[x], 1);
    }else{
        ans += query_sum(id[x], id[y], 1);
    }
    return ans;
}

int mx(int x, int y){
    int ans = -1e9, fx = top[x], fy = top[y];
    while(fx != fy){
        if(dep[fx] >= dep[fy]){
            ans = max(ans, query_mx(id[fx], id[x], 1));
            x = fa[fx];
            fx = top[x];
        }else{
            ans = max(ans, query_mx(id[fy], id[y], 1));
            y = fa[fy];
            fy = top[y];
        }
    }
    if(dep[y] <= dep[x]){
        ans = max(ans, query_mx(id[y], id[x], 1));
    }else{
        ans = max(ans, query_mx(id[x], id[y], 1));
    }
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    dep[1] = 1;
    f1(1);
    f2(1, 1);
    build(1, cnt, 1);
    int Q;
    scanf("%d", &Q);
    while(Q--){
        char opt[10];
        int u, v;
        scanf("%s %d %d", opt, &u, &v);
        if(opt[0] == 'C'){
            change(id[u], v, 1);
        }else if(opt[1] == 'M'){
            printf("%d\n", mx(u, v));
        }else{
            printf("%d\n", sum(u, v));
        }
    }
}