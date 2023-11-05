//
// Created by kibi on 23-11-5.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static auto read_ = [](initializer_list<int*> x){
        static auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

    static int n, m;
    read_({&n, &m});

    using ll = long long;
    ll dis[n][n], raw[n][n];
    memset(dis, 0x3f, sizeof dis);
    memset(raw, 0x3f, sizeof raw);
    for(int i = 0; i < m; i++){
        int u, v, w;
        read_({&u, &v, &w});
        u--, v--;
        raw[u][v] = raw[v][u] = dis[u][v] = dis[v][u] = min(dis[u][v], (ll)w);
    }

    ll ans = -1;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < k; i++){
            for(int j = i + 1; j < k; j++){
                ll val = dis[i][j] + raw[i][k] + raw[k][j];
                ans = min(ans < 0 ? val : ans, val);
            }
        }

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dis[j][i] = dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
            }
        }
    }

    ans < 0 || ans > 5 * 100000000 ? printf("No solution.\n") : printf("%lld\n", ans);
}