//
// Created by kibi on 2022/10/28.
//
#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;
int head[200005], nxt[400005], to[400005], val[200005];

void read(int &x);
void addEdge(int, int);

int main(){
    int n;
    read(n);
    for(int i = 1; i < n; i++){
        static int u, v;
        read(u), read(v);
        addEdge(u, v);
    }
    for(int i = 1; i <= n; i++){
        read(val[i]);
    }
    int ans = 0, mx = 0;
    for(int i = 1; i <= n; i++){
        static int s1, s2, mx1, mx2;
        s1 = s2 = mx1 = mx2 = 0;
        for(int now = head[i]; now; now = nxt[now]){
            static int v;
            v = to[now];
            s1 = (s1 + val[v]) % mod;
            s2 = (s2 + val[v] * val[v]) % mod;
            if(mx1 < val[v]){
                mx2 = mx1;
                mx1 = val[v];
            }else if(mx2 < val[v]){
                mx2 = val[v];
            }
        }
        ans = (int)(((long long)s1 * s1 - s2 + mod + ans) % mod);
        mx = max(mx, mx1 * mx2);
    }
    printf("%d %d", mx, ans);
}

void addEdge(int u, int v){
    static int cnt = 0;
    nxt[++cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt;
    nxt[++cnt] = head[v];
    to[cnt] = u;
    head[v] = cnt;
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