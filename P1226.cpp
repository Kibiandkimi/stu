//
// Created by kibi on 23-8-25.
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

        static long long pow(long long a, long long b, long long p){
            long long res = 1;
            while(b){
                if(b & 1){
                    res = res * a % p;
                }
                a = a * a % p;
                b >>= 1;
            }
            return res;
        }
    };

    auto read = Tools::read;

    long long a, b, p;
    read(a), read(b), read(p);

    long long ans = Tools::pow(a, b, p);

    printf("%lld^%lld mod %lld=%lld\n", a, b, p, ans);

}