//
// Created by kibi on 23-10-28.
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
    };

    auto read = Tools::read;

    int n;
    ll T;
    read(n), Tools::read_ll(T);

    int pri[n], num = n, mn = 1e9;
    ll sum = 0;
    for(int &i : pri){
        read(i);
        sum += i;
        mn = min(mn, i);
    }

    ll ans = 0;
    int now = 0;
    while(T >= mn){
        ans += (ll)num * (T / sum);
        T = T % sum;

        bool flag = false;
        for(int i = now; i < n; i++){
            if(pri[i] < 0){
                continue;
            }
            if(T < pri[i]){
                flag = true;
                sum -= pri[i];
                pri[i] = -1;
                now = (i + 1) % n;
                num--;
                break;
            }else{
                T -= pri[i];
                ans++;
            }
        }
        if(flag){
            continue;
        }
        for(int i = 0; i < n; i++){
            if(pri[i] < 0){
                continue;
            }
            if(T < pri[i]){
                sum -= pri[i];
                pri[i] = -1;
                now = (i + 1) % n;
                num--;
                break;
            }else{
                T -= pri[i];
                ans++;
            }
        }
    }

    printf("%lld\n", ans);

}