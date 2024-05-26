//
// Created by kibi on 23-10-31.
//
#include <bits/stdc++.h>
using namespace std;

// TODO not understand complex dp

int main(){

    const int Mod = 998244353;

    class Tools{
    public:
        static void read(int &x){
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

        static int popcnt(int x){
            int res = 0;
            while(x){
                res += x & 1;
                x >>= 1;
            }
            return res;
        }

        static void add(int &x, int val){
            x = (x + val) % Mod;
        }
    };

    auto read = Tools::read;
    auto popcnt = Tools::popcnt;
    auto add = Tools::add;

    int n, m, k;
    read(n), read(m), read(k);

    using ll = long long;
    int c[n + 1][n + 1];
    memset(c, 0, sizeof c);
    for(int i = 0; i <= n; i++){
        c[i][0] = 1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;
        }
    }

    int raw_data[m + 1];
    for(auto &i : raw_data){
        read(i);
    }

    int p[m + 1][n + 1];
    for(int i = 0; i <= m; i++){
        p[i][0] = 1;
        for(int j = 1; j <= n; j++){
            p[i][j] = (int)(((ll)p[i][j - 1] * raw_data[i]) % Mod);
        }
    }

    int ans = 0;

    int f[m + 2][n + 2][k + 2][(n >> 1) + 2];
    memset(f, 0, sizeof f);
    f[0][0][0][0] = 1;
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            for(int r = 0; r <= k; r++){
                for(int s = 0; s <= (n >> 1); s++){
                    for(int t = 0; t <= n - j; t++){
                        add(f[i + 1][j + t][r + ((t + s) & 1)][(t + s) >> 1],
                            (int)(((ll)f[i][j][r][s] * p[i][t] % Mod) * c[n - j][t] % Mod));
                    }
                }
            }
        }
    }

    for(int r = 0; r <= k; r++){
        for(int s = 0; s <= (n >> 1); s++){
            if(r + popcnt(s) <= k){
                add(ans, f[m + 1][n][r][s]);
            }
        }
    }

    printf("%d\n", ans);
}