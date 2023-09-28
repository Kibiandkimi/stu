//
// Created by kibi on 23-9-28.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){

    class Test{
        class Data{
        public:
            long long p, q;
            bool flag;

            bool operator != (const Data &b) const{
                return (b.p != p) || (b.q != q) || (b.flag != flag);
            }
        };

        class Func1{
        public:
            static Data run(long long n, long long d, long long e){
                class Tools{
                public:
                    static long long sqrt(long long x){
                        long long l = 1, r = x;
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

                long long sum = n + 2 - e * d;
                long long delta = sum * sum - 4 * n;
                long long sqrt_delta = Tools::sqrt(delta);

                if(sqrt_delta > 0){
                    long long q = sum + sqrt_delta, p = sum - sqrt_delta;
                    if(p > 0 && q > 0 && !(p & 1) && !(q & 1)){
                        p >>= 1;
                        q >>= 1;
                        return {p, q, true};
                    }
                }

                return {0, 0, false};
            }
        };

        class Func2{
        public:
            static Data run(long long n, long long d, long long e) {
                long long PsubQ = sqrt((n - e * d + 2) * (n - e * d + 2) - (n * 4));
                long long PaddQ = n - e * d + 2;
                long long P = (PsubQ + PaddQ) / 2;
                long long Q = PaddQ - P;
                if (P * Q == n && e * d == (P - 1) * (Q - 1) + 1 && P && Q) {
                    return {min(P, Q), max(P, Q), true};
                }else {
                    return {0, 0, false};
                }
            }
        };

        static long long deal(long long mx){
            mt19937 rnd(random_device{}());
            return (long long)((rnd() % mx + mx) % mx) + 1;
        }

    public:
        Test(){
            long long n, d, e;
            while(true){
                n = deal(1000000000000000000), d = deal(1000000000), e = deal(1000000000);
                if(n - e * d + 2 > 1000000000){
                    continue;
                }
                Data a = Func1::run(n, d, e), b = Func2::run(n, d, e);
                if(a != b){
                    printf("%lld %lld %lld\n", n, d, e);
                    printf("%lld %lld %d\n", a.p, a.q, a.flag);
                    printf("%lld %lld %d\n", b.p, b.q, b.flag);
                    return;
                }
            }
        }
    };

    Test();

}