//
// Created by kibi on 2021/8/10.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,vis[100005];
double s[100005];
double ans;
struct node{
    int v,w;
};
vector<node> a[100005];
int dfs(int x, double s){
    // if(x == n){
    //     // s[x] += s/(double)a[x].size();
    //     return 0;
    // }
    s /= a[x].size();
    for(int i = 0; i < a[x].size(); i++){
        ans += s*a[x][i].w;
        dfs(a[x][i].v, s);
    }
    return 0;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v,w;
        scanf("%d %d %d", &u, &v, &w);
        a[u].push_back((node){v,w});
    }
    dfs(1,1);
    // while()
    printf("%.2lf", ans);
    return 0;
}