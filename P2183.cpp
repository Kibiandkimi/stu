//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    const int M = 5;

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

        static int pow(int x, int p, int mod){
            int res = 1;
            while(p){
                if(p & 1){
                    res = (int)((long long)res * x % mod);
                }
                x = (int)((long long)x * x % mod);
                p >>= 1;
            }
            return res;
        }

        static int factorial(int n, int p, int pk){ // n! % p_i ^ c_i, p -> p_i, pk -> p_i ^ c_i
            if(!n){
                return 1;
            }

            int ans = 1;

            for(int i = 2; i <= pk; i++){
                if(i % p){
                    ans = (int)((long long)ans * i % pk);
                }
            }

            ans = pow(ans, n/pk, pk);

            for(int i = 2; i <= n%pk; i++){
                if(i%p){
                    ans = (int)((long long)ans * i % pk);
                }
            }

            return (int)((long long)ans * factorial(n/p, p, pk) % pk);
        }

        static int exgcd(int a, int b, int &x, int &y){
            if(!b){
                x = 1, y = 0;
                return a;
            }
            int d = exgcd(b, a % b, x, y);
            int t = x;
            x = y;
            y = t - a/b * y;
            return d;
        }

        static int inv(int k, int p){
            if(!k){
                return 0;
            }
            int x, y, a = k, b = p;
            exgcd(a, b, x, y);
            x = (x % b + b) % b;
            if(!x){
                x += b;
            }
            return x;
        }

        static int calc_C(int n, int m, int mod, int p, int pk){
            if(m > n){
                return 0;
            }

            int a = factorial(n, p, pk), b = factorial(m, p, pk), c = factorial(n-m, p, pk), k = 0;

            for(int i = n; i; i /= p){
                k += i / p;
            }
            for(int i = m; i; i /= p){
                k -= i / p;
            }
            for(int i = n-m; i; i /= p){
                k -= i / p;
            }

            int ans = (int)((long long)a * inv(b, pk) % pk * inv(c, pk) % pk * pow(p, k, pk) % pk);

            return (int)((long long)ans * (mod / pk) % mod * inv(mod / pk, pk) % mod);
        }
    };

    auto read = Tools::read;

    int mod, n, m;
    static int w[M + 5];

    long long sum = 0;

    read(mod), read(n), read(m);
    for(int i = 1; i <= m; i++){
        read(w[i]);
        sum += w[i];
    }

    if(sum > n){
        printf("Impossible\n");
        return 0;
    }

    int ans = 1;

    for(int k = 1; k <= m; k++){
        int now = 0, p = mod;
        for(int i = 2; i * i <= mod; i++){
            if(!(p%i)){
                int pk = 1;
                while(!(p%i)){
                    pk *= i;
                    p /= i;
                }
                now = (int)(((long long)now + Tools::calc_C(n, w[k], mod, i, pk)) % mod);
            }
        }
        if(p > 1){
            now = (int)(((long long)now + Tools::calc_C(n, w[k], mod, p, p)) % mod);
        }
        ans = (int)((long long)ans * now % mod);
        n -= w[k];
    }

    printf("%d\n", ans);

}