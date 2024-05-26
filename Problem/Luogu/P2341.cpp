//
// Created by kibi on 2021/8/19.
//
#include <bits/stdc++.h>
using namespace std;
int n,m,num = 1, nc = 1;
int dfn[10005], low[10005], vis[10005], c[10005], sc[10005], d[10005];
stack<int> st;
vector<int> a[10005];
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
    if(low[x] == dfn[x]){
        c[x] = nc;
        sc[nc]++;
        while(st.top()!=x){
            c[st.top()] = nc;
            sc[nc]++;
            st.pop();
        }
        nc++;
        st.pop();
    }
    return 0;
}
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
    }
    // int num = 1;
    for(int i = 1; i <= n; i++){
        if(!dfn[i]){
            t(i);
        }
    }
    for(int i = 1; i <= n; i++){
        int sa = a[i].size();
        for(int j = 0; j < sa; j++){
            if(c[i] != c[a[i][j]])d[c[i]]++;
        }
    }
    int s = 0,ss = 0;
    for(int i = 1; i < nc; i++){
        if(!d[i]){
            s = sc[i];
            ss++;
        }
    }
    if(ss==1){
        cout << s;
    }else{
        cout << 0;
    }
}
