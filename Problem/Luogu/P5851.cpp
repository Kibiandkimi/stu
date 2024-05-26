//
// Created by kibi on 23-11-4.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    auto read_ = [](initializer_list<int*> x){
        auto read = [](int &x){
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

    class Cow{
    public:
        int w, l, r;
    };

    int n, m;
    read_({&n, &m});

    Cow cow[m];
    int p[n][n][n];
    memset(p, 0, sizeof p);
    for(auto &now : cow){
        read_({&now.w, &now.l, &now.r});
        now.l--, now.r--;
        for(int i = now.l; i <= now.r; i++){
            p[i][now.l][now.r] = now.w;
        }
    }

    for(int len = 2; len <= n; len++){
        for(int i = 0; i <= n - len; i++){
            int j = i + len - 1;
            for(int k = i; k <= j; k++){
                p[k][i][j] = max({p[k][i][j - 1], p[k][i + 1][j], p[k][i][j]});
            }
        }
    }

    int f[n][n];

    for(int len = 1; len <= n; len++){
        for(int i = 0; i <= n - len; i++){
            int j = i + len - 1;
            if(len == 1) {
                f[i][j] = p[i][i][i];
            }else{
                f[i][j] = max(f[i + 1][j] + p[i][i][j], f[i][j - 1] + p[j][i][j]);
                for(int k = i + 1; k < j; k++){
                    f[i][j] = max(f[i][j], f[i][k - 1] + p[k][i][j] + f[k + 1][j]);
                }
            }
        }
    }

    printf("%d\n", f[0][n - 1]);
}