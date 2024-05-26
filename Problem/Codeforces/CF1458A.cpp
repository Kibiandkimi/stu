//
// Created by kibi on 23-10-5.
//
#include <bits/stdc++.h>
using namespace std;

int main(){

    using ll = long long;

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

        static void read_ll(ll &x){
            ll s = 0, w = 1, c = getchar();
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

        static ll gcd(ll a, ll b){
            if(!b){
                return a;
            }
            return gcd(b, a % b);
        }

    };

    auto read = Tools::read;
    auto read_ll = Tools::read_ll;
    auto gcd = Tools::gcd;

    int n, m;
    read(n), read(m);

    ll a[n], b[m];
    for(ll &i : a){
        read_ll(i);
    }
    for(ll &i : b){
        read_ll(i);
    }

    if(n == 1){
        for(ll &i : b){
            printf("%lld ", i + a[0]);
        }
        return 0;
    }

    ll base = a[1] - a[0];
    for(int i = 2; i < n; i++){
        base = gcd(base, abs(a[i] - a[i - 1]));
    }

    for(ll &i : b){
        printf("%lld ", gcd(base, a[0] + i));
    }
}