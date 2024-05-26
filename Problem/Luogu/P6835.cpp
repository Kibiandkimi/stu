//
// Created by kibi on 23-7-21.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 1000000, M = 1000000, Mod = 998244353;

void read(int&);

int main(){

    class Graph{
        int head[N + 5], nxt[M + 5], to[M + 5], cnt;
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

    int id, n, m;
    static int e[N + 5], sum[N + 5];
    static Graph graph;

    read(id), read(n), read(m);

    for(int i = 1; i <= m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v);
    }

    for(int i = 1; i <= n; i++){
        int x = 0;
        for(int j = graph.begin(i); j; j = graph.next(j)){
            int v = graph.get(j);
            x++;
            e[i] = (int)(((long long)e[i] + sum[i-1] - sum[v-1] + Mod) % Mod);
        }
        e[i] = (e[i] + x + 1) % Mod;
        sum[i] = (sum[i-1] + e[i]) % Mod;
    }

    printf("%d\n", sum[n]);

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