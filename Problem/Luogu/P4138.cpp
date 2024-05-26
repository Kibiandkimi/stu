//
// Created by kibi on 23-7-5.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 2000;

void read(int &x);

class node{
public:
    int w, v;
    static bool cmp(node a, node b){
        return a.w != b.w ? a.w > b.w: a.v > b.v;
    }
};

int main(){
    static int n, f[N+5][N+5];
    static node a[N+5];
    read(n);
    for(int i = 1; i <= n; i++){
        read(a[i].w), read(a[i].v);
    }
    sort(a+1, a+1+n, node::cmp);
    memset(f, 0xc0, sizeof f);
    f[0][1] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= n; j++){
            //            i: 物品 j：挂钩
            f[i][j] = max(f[i-1][j], f[i-1][max(j-a[i].w, 0)+1] + a[i].v);
        }
    }
    int ans = 0;
    for(int j = 0; j <= n; j++){
        ans = max(ans, f[n][j]);
    }
    printf("%d", ans);
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