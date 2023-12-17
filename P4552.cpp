//
// Created by kibi on 23-11-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;

    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
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
        };

        for(auto &i : x){
            read(*i);
        }
    };

    auto read_ll = [](initializer_list<ll*> x){
        auto read_ll = [](ll &x){
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
        };

        for(auto &i : x){
            read_ll(*i);
        }
    };

    int n;
    read({&n});

    ll a[n];
    for(ll &i : a){
        read_ll({&i});
    }

    ll p = 0, q = 0;

    ll dec[n];
    dec[0] = 0;
    for(int i = 1; i < n; i++){
        dec[i] = a[i] - a[i - 1];
        if(dec[i] > 0){
            p += dec[i];
        }else{
            q -= dec[i];
        }
    }

    printf("%lld\n%lld\n", max(p, q), abs(p - q) + 1);

}