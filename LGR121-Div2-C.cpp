//
// Created by kibi on 2022/9/24.
//
//Not done(not complete)
#include <bits/stdc++.h>
using namespace std;
int fa[200005], dfn[200005];
vector<int> g[200005];

void read(int &x);
int f1(int u, int cnt);
int f2(int u, int l, int r);

int main(){
    int T;
    read(T);
    while(T--) {
        int n;
        read(n);
        for(int i = 1; i < n; i++){
            int u, v;
            read(u), read(v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        f1(1, 1);
        f2(n, 1, n);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0'<=c && c<='9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;

}

int f1(int u, int cnt){
    dfn[u] = cnt;
    for(auto &i : g[u]){
        if(i == fa[u]){
            continue;
        }
        fa[i] = u;
        cnt = f1(i, cnt + 1);
    }
    return cnt;
}

int f2(int u, int l, int r){

}