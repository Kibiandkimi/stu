//
// Created by kibi on 2021/8/27.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,p[50005],d[50005],fa[50005][30];
vector<int> a[50005];
void pre(int x, int f){
    d[x] = d[f]+1;
    fa[x][0] = f;
    for(int i = 0; fa[x][i]; i++){
        fa[x][i+1] = fa[fa[x][i]][i];
    }
    int sa = a[x].size();
    for(int i = 0; i < sa; i++){
        if(a[x][i]!=f){
            pre(a[x][i], x);
        }
    }
}
int lca(int t1, int t2){
    int u,v;
    u = d[t1]>d[t2]?t2:t1;
    v = t1+t2-u;
    for(int i = 20; i >= 0; i--){
        if(d[u]<=d[v]-(1<<i)){
            v = fa[v][i];
        }
    }
    if(u == v){
        return u;
    }
    for(int i = 20; i >= 0; i--){
        if(fa[u][i]!=fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
int f(int x, int fa){
    int sa = a[x].size();
    int s = 0;
    for(int i = 0; i < sa; i++){
        if(a[x][i]==fa)continue;
        s = max(s, f(a[x][i], x));
        p[x] += p[a[x][i]];
    }
    s = max(s, p[x]);
    return s;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i < n; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    pre(1, 0);
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        int l = lca(u,v);
        p[u]++;
        p[v]++;
        p[l]--;
        p[fa[l][0]]--;
    }
    printf("%d", f(1,0));
}