//
// Created by kibi on 23-10-5.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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
    };

    auto read = Tools::read;

    int n;
    read(n);

    bool is_prime[n + 1];
    int phi[n + 1], prime[n + 1], cnt = 0;

    memset(is_prime, 1, sizeof is_prime);

    is_prime[1] = false, phi[1] = 1;
    for(int i = 2; i <= n; i++){
        if(is_prime[i]){
            prime[++cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; j <= cnt && i * prime[j] <= n; j++){
            is_prime[i * prime[j]] = false;
            if(i % prime[j]){
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            }else{
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }

    long long sum_phi[n + 1];
    sum_phi[0] = 0;
    for(int i = 1; i <= n; i++){
        sum_phi[i] = sum_phi[i - 1] + phi[i];
    }

    long long ans = 0;
    for(int i = 1; i <= cnt; i++){
        ans += 2 * sum_phi[n / prime[i]] - 1;
    }

    printf("%lld\n", ans);

}