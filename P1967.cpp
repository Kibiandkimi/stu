//
// Created by kibi on 2021/8/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,bc[10005],d[10005],fa[10005][30],w[10005][30],vis[10005];
struct node{
    int v,w;
};
struct side{
    int u,v,w;
};
int find(int x){
    if(bc[x]!=x){
        bc[x] = find(bc[x]);
    }
    return bc[x];
}
vector<side> ra;
vector<node> pa[10005];
bool cmp(const side &a, const side &b){
    return a.w > b.w;
}
void pre(int x, int f, int s){
    d[x] = d[f]+1;
    fa[x][0] = f;
    w[x][0] = s;
    vis[x] = 1;
    for(int i = 0; i <= 20; i++){
        fa[x][i+1] = fa[fa[x][i]][i];
        w[x][i+1] = min(w[x][i],w[fa[x][i]][i]);
    }
    int sa = pa[x].size();
    for(int i = 0; i < sa; i++){
        if(vis[pa[x][i].v])continue;
        pre(pa[x][i].v, x, pa[x][i].w);
    }
}
int lca(int u, int v){
    if(find(u)!=find(v))return -1;
    if(d[u]>d[v]){
        swap(u,v);
    }
    int s = 1e9;
    for(int i = 20; i >= 0; i--){
        if(d[fa[v][i]]>=d[u]){
            s = min(s, w[v][i]);
            v = fa[v][i];
        }
    }
    if(u == v)return s;
    for(int i = 20; i >= 0; i--){
        if(fa[u][i]!=fa[v][i]){
            s = min(s, min(w[u][i], w[v][i]));
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    s = min(s, min(w[u][0], w[v][0]));
    return s;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        ra.push_back({u,v,w});
    }
    for(int i = 1; i <= n; i++){
        bc[i] = i;
    }
    int sr = ra.size();
    sort(ra.begin(), ra.end(), cmp);
    for(int i = 0; i < sr; i++){
        int tu = ra[i].u, tv = ra[i].v;
        if(find(tu)!=find(tv)){
            int tw = ra[i].w;
            pa[tu].push_back({tv, tw});
            pa[tv].push_back({tu, tw});
            bc[find(tu)] = find(tv);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            pre(i, 0, 1e9);
            fa[i][0] = i;
            w[i][0] = 1e9;
        }
    }
    int q;
    cin >> q;
    while(q--){
        int u,v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u,v));
    }
}