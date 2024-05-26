//
// Created by kibi on 23-10-3.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int Mod = 1000000007;

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
    };

    class Question{
    public:
        int n, m;
    };

    auto read = Tools::read;

    int T, mxn = 1, mxm = 1;
    read(T);

    Question q[T];
    for(int i = 0; i < T; i++){
        read(q[i].n), read(q[i].m);
        mxn = max(mxn, max(q[i].n, q[i].m));
        mxm = max(mxm, min(q[i].n, q[i].m));
    }

    const int rd = 500;

    int f[rd + 1][mxn + 1];

    f[0][0] = 1;

    for(int i = 1; i <= rd; i++){
        for(int j = 0; j <= i * (i + 1) / 2 && j <= mxm; j++){
            f[i][j] = f[i - 1][j];
            if(j >= i){
                f[i][j] += f[i - 1][j - i];
                if(f[i][j] > Mod){
                    f[i][j] -= Mod;
                }
            }
        }
    }

    for(int i = 0; i <= rd; i++){
        for(int j = 1; j <= i * (i + 1) / 2 && j <= mxm; j++){
            f[i][j] += f[i][j - 1];
            if(f[i][j] > Mod){
                f[i][j] -= Mod;
            }
        }
    }

    for(int i = 0; i < T; i++){
        int ans = 0;
        int n = min(q[i].n, q[i].m), m = max(q[i].n, q[i].m);
        for(int j = 1; j <= rd; j++){
            int l = max(j * (j + 1) / 2 - m, 0), r = min(j * (j + 1) / 2, n);
            if(l > r){
                break;
            }
            ans += f[j][r];
            if(l != 0){
                ans -= f[j][l - 1];
            }
            if(ans > Mod){
                ans -= Mod;
            }else if(ans < 0){
                ans += Mod;
            }
        }
        printf("%d\n", ans);
    }

}