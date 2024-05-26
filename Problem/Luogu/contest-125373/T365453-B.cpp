//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int P = 100, Mod = 998244353;

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

        static int pow(int a, int p, int mod){
            int res = 1;
            while(p){
                if(p & 1){
                    res = (int)((long long)res * a % mod);
                }
                a = (int)((long long)a * a % mod);
                p >>= 1;
            }
            return res;
        }

        static int calc(int c, int n, const int mod){
            /*
            static int pow_c[100005];
            int res = 0, now_add = 1, now_decrease = 1;
            init_pow(c, n-1, mod, pow_c);
            for(int i = 0; i < n; i++){
                int now = now_add - now_decrease;
                now = now < 0 ? now + mod : now;
                res = (int)(((long long)res + (long long)pow_c[n-1-i] * now % mod) % mod);
                now_add = (int)((long long)now_add * (c+1) % mod);
                now_decrease = (int)((long long)now_decrease * (c-1) % mod);
            }
            return res;
            */ // 75pts -> 100pts
            return (int)((((long long)pow(c+1, n, mod) - (long long)2*pow(c, n, mod) + pow(c-1, n, mod)) % mod + mod) % mod);
        }
    };

    auto read = Tools::read;

    int T;
    read(T);

    while(T--){
        int n, g, l;
        read(n), read(g), read(l);

        if(l % g != 0){ // 0pts -> 75pts
            printf("0\n");
            continue;
        }

        l /= g;

        static int p[P + 5], num[P + 5];
        int cnt = 0;

        for(int i = 2; i <= l; i++){
            if(l % i == 0){
                p[++cnt] = i;
                num[cnt] = 0;
                while(l % i == 0){
                    l /= i;
                    num[cnt]++;
                }
            }
        }

        int ans = 1;

        for(int i = 1; i <= cnt; i++){
            int c = num[i];
            ans = (int)((long long)ans * Tools::calc(c, n, Mod) % Mod);
        }

        printf("%d\n", ans);
    }
}