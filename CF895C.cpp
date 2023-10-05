//
// Created by kibi on 23-10-4.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
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

    auto read = Tools::read;

    int n;
    read(n);

    static int stuck[71];
    for(int i = 0; i < n; i++){
        static int tem;
        read(tem);
        stuck[tem]++;
    }

    using ll = long long;

    ll h[n + 1];
    static ll f1[1 << 19], f2[1 << 19];
    f1[0] = 1, h[0] = 1;
    for(int i = 1; i <= n; i++){
        h[i] = (h[i - 1] << 1) % Mod;
    }
    for(int i = 1; i <= 70; i++){
        if(!stuck[i]){
            continue;
        }
        swap(f1, f2);
        memset(f1, 0, sizeof f1);
        for(int m = 0; m < (1 << 19); m++){
            int m1 = m, x = i;
            for(int j = 0; j < 19 && x >= p[j]; j++){
                while(x % p[j] == 0){
                    x /= p[j];
                    m1 ^= (1 << j);
                }
            }
            f1[m1] = (f1[m1] + f2[m] * h[stuck[i] - 1]) % Mod;
            f1[m] = (f1[m] + f2[m] * h[stuck[i] - 1]) % Mod;
        }
    }

    printf("%lld\n", (f1[0] - 1 + Mod) % Mod);
}