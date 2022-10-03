//
// Created by kibi on 2022/10/3.
//
#include <bits/stdc++.h>
using namespace std;
int n, w[5005], siz[5005];
long long d[5005][5005];
vector<int> g[5005];

void read(int &x);
void f(int u, int fa);

int main(){
    read(n);
    for(int i = 1; i < n; i++){
        read(w[i+1]);
    }
    for(int i = 1; i < n; i++){
        int u, v;
        read(u), read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(d, 0x3f, sizeof d);
    for(int i = 0; i <= n; i++){
        d[i][0] = 0;
    }
    f(1, 0);
    printf("%lld", d[1][n-1]);
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

void f(int u, int fa){
    siz[u] = 1;
    for(auto &i : g[u]){
        if(i != fa){
            f(i, u);
            siz[u] += siz[i];
        }
    }
    if(siz[u] != 1) {
        int sg = g[u].size()+(fa==0);
        long long dd[2][siz[u]], lastMx = 0;
        memset(dd, 0x3f, sizeof dd);
        bool flag = false;
        dd[0][0] = 0;

        for (int i = 0, mxi = (sg-(fa==0)); i < mxi; i++) {
            int &v = g[u][i];
            if (v == fa) {
                flag = true;
                continue;
            }
            int nowP = (i + 1 - flag)%2;
            dd[nowP][0] = 0;
            for (int j = 1, mxj = siz[v] + lastMx; j < mxj; j++) {
                for(int k = 0, mxk = min(siz[v], j+1); k < mxk; k++){
                    dd[nowP][j] = min(dd[nowP][j], dd[nowP^1][j-k] + d[v][k]);
                }
            }
            lastMx += (siz[v]-1);
        }

        d[u][siz[u] - 1] = w[siz[u]];
        for(int i = 1; i < siz[u]; i++){
            d[u][i] = min(dd[(sg - 1)%2][i], d[u][i]);
            d[u][siz[u]-1] = min(d[u][siz[u]-1], d[u][i] + w[siz[u]-i]);
        }
    }
}