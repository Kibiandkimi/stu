//
// Created by kibi on 23-8-10.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int K = 10;

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

        static void multi_read(int l, int *data){
            for(int i = 0; i < l; i++){
                read(data[i]);
            }
        }

        static long long mul(long long a, long long b, long long Mod){
            long long res = 0;
            while(b){
                if(b & 1){
                    res = (res + a) % Mod;
                }
                a = (a + a) % Mod;
                b >>= 1;
            }
            return res;
        }

        static void exgcd(long long a, long long b, long long &x, long long &y){
            if(b == 0){
                x = 1, y = 0;
                return;
            }
            exgcd(b, a%b, x, y);
            long long t = x;
            x = y;
            y = t - a/b * y;
        }

        static long long crt(int k, int *a, int *b){
            long long ans = 0, lcm = 1, x, y;

            for(int i = 1; i <= k; i++){
                lcm *= b[i];
            }

            for(int i = 1; i <= k; i++){
                long long t = lcm/b[i];
                exgcd(t, b[i], x, y);
                x = (x % b[i] + b[i]) % b[i];
                ans = (ans + mul(mul(t, x, lcm), a[i], lcm)) % lcm;
            }
            return (ans + lcm) % lcm;
        }
    };

    auto read = Tools::read;
    auto multi_read = Tools::multi_read;

    int k;
    read(k);

    static int a[K + 5], b[K + 5];

    multi_read(k, a+1), multi_read(k, b+1);

    for(int i = 1; i <= k; i++){
        a[i] = (a[i] % b[i] + b[i]) % b[i];
    }

    long long ans = Tools::crt(k, a, b);

    printf("%lld\n", ans);
}