//
// Created by kibi on 2021/8/20.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,num = 1, cl = 1, as[10005], bs[10005];
int dfn[10005], low[10005], c[10005], sc[10005], vis[10005];
stack<int> st;
vector<int> a[10005],b[10005];
int t(int x){
    dfn[x] = low[x] = num++;
    st.push(x);
    int sa = a[x].size();
    for(int i = 0; i < sa; i++){
        if(!dfn[a[x][i]]){
            t(a[x][i]);
            low[x] = min(low[x], low[a[x][i]]);
        }else if(!c[a[x][i]]){
            low[x] = min(low[x], dfn[a[x][i]]);
        }
    }
    if(dfn[x] == low[x]){
        c[x] = cl;
        sc[cl] += as[x];
        // sc[cl]++;
        while(st.top()!=x){
            c[st.top()] = cl;
            // sc[cl]++;
            sc[cl]+= as[st.top()];
            st.pop();
        }
        cl++;
        st.pop();
    }
    return 0;
}
int f(int x){
    if(vis[x]){
        return bs[x];
    }
    int sb = b[x].size();
    vis[x] = 1;
    int mx = 0;
    for(int i = 0; i < sb; i++){
        mx = max(mx, f(b[x][i]));
    }
    mx += sc[x];
    bs[x] = mx;
    return bs[x];
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        scanf("%d", &as[i]);
    }
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
    }
    for(int i = 1; i <= n; i++){
        if(!dfn[i])t(i);
    }
//    for(int i = 1; i < cl; i++){
//        bs[i] = sc[i];
//    }
    for(int i = 1; i <= n; i++){
        int sa = a[i].size();
        for(int j = 0; j < sa; j++){
            if(c[i]!=c[a[i][j]])b[c[i]].push_back(c[a[i][j]]);
        }
    }
    int mx = 0;
    for(int i = 1; i < cl; i++){
        mx = max(f(i), mx);
    }
    cout << mx;
}