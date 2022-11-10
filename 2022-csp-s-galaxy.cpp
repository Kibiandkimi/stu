//
// Created by kibi on 2022/11/6.
//
#include <bits/stdc++.h>
using namespace std;

static const int MaxN = 500005;

mt19937 rnd(random_device{}());

vector<int> g[MaxN];

int in[MaxN], out[MaxN];
long long te[MaxN], su[MaxN];

unsigned int h[MaxN];

long long Ans, now;

void read(int &x);
void addEdge(int u, int v);

int main(){
    int n, m;
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        h[i] = rnd();
        Ans += h[i];
    }
    for(int i = 1; i <= m; i++){
        static int u, v;
        read(u), read(v);
        addEdge(u, v);
        now += h[u];
        su[v] += h[u];
    }
    int q;
    read(q);
    while(q--){
        int opt;
        read(opt);
        if(opt == 1){
            static int u, v;
            read(u), read(v);
            //            ch[u]++;
            now -= h[u];
            te[v] += h[u];
        }else if(opt == 2){
            static int u;
            read(u);
            now -= su[u] - te[u];
            te[u] = su[u];
        }else if(opt == 3){
            static int u, v;
            read(u), read(v);
            //            ch[u]--;
            now += h[u];
            te[v] -= h[u];
        }else if(opt == 4){
            static int u;
            read(u);
            now += te[u];
            te[u] = 0;
        }

        if(now == Ans){
            printf("YES\n");
        }else{
            printf("NO\n");
        }

    }
}

void addEdge(int u, int v){
    in[v]++;
    out[u]++;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
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
