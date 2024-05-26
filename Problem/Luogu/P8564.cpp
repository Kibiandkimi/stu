//
// Created by kibi on 2022/10/5.
//
//
// Created by kibi on 2022/10/3.
//
#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int n, w[5005], siz[5005];
long long d[5005][5005];
vector<int> g[5005];

void read(int &x);
void f(int u, int fa, bool tem = true);

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
    //    memset(d, 0x3f, sizeof d);
    //    for(int i = 0; i <= n; i++){
    //        d[i][0] = 0;
    //    }
    f(1, 0, false);
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

void f(int u, int fa, bool tem){
    if(tem){
        for (int i=1;i<siz[u];i++) {
            d[u][i] = INF;
        }
        d[u][siz[u] - 1] = 0;
    }else {
        siz[u] = 1;
    }
    for(auto &i : g[u]){
        if(i != fa){
            f(i, u, tem);
            if(!tem) {
                siz[u] += siz[i];
            }
        }
    }
    //    for (int i=1;i<siz[u];i++) {
    //        d[u][i] = INF;
    //    }
    //    d[u][siz[u] - 1] = 0;
    if(!tem){
        return ;
    }
    if(siz[u] != 1) {
        int sg = g[u].size();
        int lastMx = 0;
        bool flag = false;
        for (int i = 0, mxi = sg; i < mxi; i++) {
            int &v = g[u][i];
            if(v == fa){
                flag = true;
                continue;
            }
            for (int j = siz[u] - (lastMx + 1), mxj = siz[u] - (i + 1 - flag); j <= mxj; j++) {
                //                j = siz - t
                //                siz - j = siz - siz + t = t
                for(int k = 1, mxk = siz[v]; k <= mxk; k++){
                    d[u][j - k] = min(d[u][j - k], d[u][j] + d[v][siz[v] - k]);
                }
                d[u][j] = INF;
            }
            lastMx += siz[v];
            for(int j = siz[u] - (i + 1 - flag); j <= siz[u]-1; j++){
                d[u][j] = INF;
            }
        }

        d[u][siz[u] - 1] = w[siz[u]];
        for(int i = 0; i <= siz[u] - sg; i++){
            //            d[u][i] = min(dd[(sg - 1)%2][i], d[u][i]);
            d[u][siz[u]-1] = min(d[u][siz[u]-1], d[u][i] + w[siz[u]-i]);
        }
    }
}