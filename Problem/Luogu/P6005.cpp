//
// Created by kibi on 23-7-16.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1000, M = 2000;

void read(int &x);

class Graph{
    int head[N+5], to[M+5], nxt[M+5], cnt;

public:

    void add_edge(int u, int v){
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    int begin(int x){
        return head[x];
    }

    int next(int x){
        return nxt[x];
    }

    int get(int x){
        return to[x];
    }
};

int main(){
    int n, m, c, ans = 0;
    int v[N+5] = {0};
    static Graph graph;
    static int f[1005][N+5];

    read(n), read(m), read(c);

    for(int i = 1; i <= n; i++){
        read(v[i]);
    }

    for(int i = 1; i <= m; i++){
        int a, b;
        read(a), read(b);
        graph.add_edge(b, a);
    }

    memset(f, 0xc0, sizeof f);

    f[0][1] = 0;

    for(int i = 1; i <= 1000; i++){
        for(int j = 1; j <= n; j++){
            int now = graph.begin(j), to = graph.get(now);
            while(now){
                f[i][j] = max(f[i][j], v[j] + f[i-1][to]);
                now = graph.next(now);
                to = graph.get(now);
            }
        }
        ans = max(ans, f[i][1] - c * i * i);
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