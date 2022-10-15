//
// Created by kibi on 2022/10/15.
//
#include <bits/stdc++.h>
using namespace std;
int head[1005], nxt[30005], to[30005];
bool g[1005][1005];
int val[1005];
void read(int &x);
void addEdge(int u, int v);

int main(){
    static int n, m, p, q;
    read(n), read(m), read(p), read(q);

    //    for subtask1
    if((long long)n * p <= q){
        printf("1");
        return 0;
    }

    //    memset(g, -1, sizeof g);
    for(int i = 1; i <= m; i++){
        static int u, v;
        read(u), read(v);
        addEdge(u, v);
    }

    //    for subtask2
    for(int i = 1; i <= n; i++){
        g[i][i] = true;
        bool flag = true;
        for(int j = 1; j <= n; j++){
            if(!g[i][j]){
                flag = false;
            }
        }
        if(flag){
            printf("%.7lf", (double)p*(n-1)/(q-p));
            return 0;
        }
    }


}

void addEdge(int u, int v){
    g[u][v] = g[v][u] = true;
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