//
// Created by kibi on 2021/8/20.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,num = 1,f;
int dfn[20005],low[20005],c[20005];
vector<int> a[20005];
int t(int x){
    dfn[x] = low[x] = num++;
    int sa = a[x].size();
    int ch = 0;
    for(int i = 0; i < sa; i++){
        if(!dfn[a[x][i]]){
            t(a[x][i]);
            low[x] = min(low[x], low[a[x][i]]);
            if(x != f&&low[a[x][i]]>=dfn[x]){
                c[x] = 1;
            }
            ch++;
        }
        low[x] = min(low[x], dfn[a[x][i]]);
    }
    if(x == f&ch>=2){
        c[x] = 1;
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        f = i;
        if(!dfn[i])t(i);
    }
    int s = 0;
    for(int i = 1; i <= n; i++){
        s += c[i];
    }
    cout << s << endl;
    for(int i = 1; i <= n; i++){
        c[i]?printf("%d ", i):0;
    }
}