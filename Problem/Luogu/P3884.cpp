//
// Created by kibi on 22-9-12.
//
#include <bits/stdc++.h>
using namespace std;
int n, mxDep, mxWed, dep[105], wed[105], fa[105];
vector<int> g[105];

void read(int &x);
void f1(int u);
int f2(int u, int v);

int main(){
    read(n);
    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int u, v;
    read(u), read(v);
    f1(1);
    printf("%d\n%d\n%d", mxDep, mxWed, f2(u, v));
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}

void f1(int u){
    dep[u] = dep[fa[u]]+1;
    mxDep = max(mxDep, dep[u]);
    wed[dep[u]]++;
    mxWed = max(mxWed, wed[dep[u]]);
    int sg = g[u].size();
    for(auto i : g[u]){
        if(i != fa[u]){
            fa[i] = u;
            f1(i);
        }
    }
}

int f2(int u, int v){
    int ans = 0;
    while(u != v){
        if(dep[u] > dep[v]){
            ans += 2;
            u = fa[u];
        }else{
            ans++;
            v = fa[v];
        }
    }
    return ans;
}