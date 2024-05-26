//
// Created by kibi on 2022/10/2.
//
#include <bits/stdc++.h>
using namespace std;

void read(int &x);

int main() {
    static int n, m, t1[(1 << 15) + 5][15], t2[(1 << 15) + 5] = {0};
    static vector<int> g[15];
    read(n), read(m);
    for (int i = 0; i < n; i++) {
        g[i].resize(20);
        for (int j = 0; j < n; j++) {
            g[i][j] = 1e9;
        }
        g[i][i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        read(u), read(v), read(w);
        u--, v--;
        g[v][u] = g[u][v] = min(g[u][v], w);
    }
    const int al = (1 << n) - 1;
    memset(t1, 0x3f, sizeof t1);
    for (int i = 1; i <= al; i++) {
        for (int j = 0; j < n; j++) {
            if (((1 << j) | i) == i) {
                //                g[j][j] = 0;
                for (int k = 0; k < n; k++) {
                    if (g[j][k] != 1e9) {
                        t2[i] |= (1 << k);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        t1[1 << i][0] = 0;
    }
    for (int i = 2; i <= al; i++) {
        for (int s0 = i - 1; s0; s0 = (s0 - 1) & i) {
            if((t2[s0] | i) == t2[s0]){
                int sum = 0, ss = s0 ^ i;
                for(int k = 0; k < n; ++k){
                    if((1 << k) & ss){
                        int tem = 1e9;
                        for(int h = 0; h < n; h++){
                            if((1 << h) & s0){
                                tem = min(tem, g[h][k]);
                            }
                        }
                        sum += tem;
                    }
                }
                for(int j = 1; j < n; ++j){
                    if(t1[s0][j - 1] != 1e9){
                        t1[i][j] = min(t1[i][j], t1[s0][j-1] + sum * j);
                    }
                }
            }
        }
    }
    int ans = 1e9;
    for(int i = 0; i < n; ++i){
        ans = min(ans, t1[al][i]);
    }
    printf("%d\n", ans);
    return 0;
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