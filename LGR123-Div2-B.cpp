//
// Created by kibi on 2022/10/15.
//
#include <bits/stdc++.h>
using namespace std;
vector<int> g[1000005];
int val[1000005], mx[1000005], mn[1000005], ans[1000005];

void read(int &x);
int dfs(int u, int l, int fa);

int main(){
    static int n;
    read(n);
    for(int i = 1; i < n; i++){
        static int u, v;
        read(u), read(v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs(1, 1, 0);
    for(int i = 1; i <= n; i++){
        printf("%d ", val[i]);
    }
}

int dfs(int u, int l, int fa){
    val[u] = l++;
    for(auto &i : g[u]){
        if(i != fa){
            l = dfs(i, l, u);
        }
    }
    return l;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}