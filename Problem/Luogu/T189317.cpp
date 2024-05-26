//
// Created by kibi on 2021/7/31.
//
#include <bits/stdc++.h>
using namespace std;
int n,m;
struct node{
    int v,i;
    bool f;
};
//node a[200005];
vector<node> a[200005];
int vis[200005],s[200005],max_dep,fat[200005];
vector<int> d[200005];
int f(int x, int dep){
    max_dep = max(max_dep, dep);
    d[dep].push_back(x);
    for(int i = 0; i < a[x].size(); i++){
        vis[x] = 1;
        if(!vis[a[x][i].v]) {
            fat[a[x][i].v] = x;
            a[x][i].f = true;
            a[a[x][i].v][a[x][i].i].f = true;
            f(a[x][i].v, dep + 1);
        }else{
            if(!a[x][i].f) {
                a[x][i].f = true;
                a[a[x][i].v][a[x][i].i].f = true;
                s[x]++;
                printf("%d %d\n", x, a[x][i].v);
            }
        }
    }
    return 0;
}
int main(){
    cin >> n >> m;
    if(m%2){
        printf("-1");
        return 0;
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        int t1 = int(a[v].size()), t2 = int(a[u].size());
        a[u].push_back(node({v, t1, false}));
        a[v].push_back(node({u, t2, false}));
    }
    f(1,1);
    for(int i = max_dep; i > 1; i--){
        for(int j = 0; j < d[i].size(); j++){
            if(s[d[i][j]]%2){
                printf("%d %d\n", d[i][j], fat[d[i][j]]);
            }else{
                printf("%d %d\n", fat[d[i][j]], d[i][j]);
                s[fat[d[i][j]]]++;
            }
        }
    }
}