//
// Created by kibi on 23-9-28.
//

#include <bits/stdc++.h>
using namespace std;

int main(){
    class Tools{
    public:
        static void read(long long &x){
            long long s = 0, w = 1, c = getchar();
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

        static long long sqrt(long long x){
            long long l = 0, r = min(x, (long long)1000000000);
            while(l <= r){
                long long mid = (l + r) >> 1;
                if(mid * mid > x){
                    r = mid - 1;
                }else if(mid * mid < x){
                    l = mid + 1;
                }else{
                    return mid;
                }
            }
            return -1;
        }
    };

    auto read = Tools::read;

    long long k;
    read(k);

    while(k--){
        long long n, d, e;
        read(n), read(d), read(e);

        long long sum = n + 2 - e * d;
        long long delta = sum * sum - 4 * n;
        long long sqrt_delta = Tools::sqrt(delta);

        if(sqrt_delta >= 0){
            long long q = sum + sqrt_delta, p = sum - sqrt_delta;
            if(p > 0 && q > 0 && p % 2 == 0 && q % 2 == 0){
                p >>= 1;
                q >>= 1;
                printf("%lld %lld\n", p, q);
                continue;
            }
        }

        printf("NO\n");

    }
}