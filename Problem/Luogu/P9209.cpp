//
// Created by kibi on 23-9-30.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static const int N = 100000;
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
    };

    auto read = Tools::read;
    auto read_ll = Tools::read_ll;

    int n;
    read(n);

    static ll w[N + 5], l[N + 5], r[N + 5];
    for(int i = 1; i <= n; i++){
        read_ll(w[i]);
    }
    for(int i = 1; i <= n; i++){
        read_ll(l[i]);
    }
    for(int i = 1; i <= n; i++){
        read_ll(r[i]);
    }

    static ll ans;
    for(int i = 1; i <= n; i++){
        ans += w[i] - max(l[i], r[i]) * (n - i);
    }

    printf("%lld\n", ans);

}