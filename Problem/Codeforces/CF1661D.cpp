//
// Created by kibi on 23-9-30.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;
    const int N = 300000;

    class Tools{
    public:
        static void read(ll &x){
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

    ll n, k;
    read(n), read(k);

    static ll aim[N + 5];
    for(int i = 1; i <= n; i++){
        read(aim[i]);
    }

    static ll inc[N + 5], sum[N + 5], sum_sum[N + 5], ans;
    for(int i = (int)n; i >= k; i--){
        sum[i] = sum[i + 1] + inc[i];
        sum_sum[i] = sum_sum[i + 1] + sum[i];
        if(sum_sum[i] < aim[i]){
            ll dec = aim[i] - sum_sum[i];
            ll ex = dec / k + (bool)(dec % k);
            inc[i] += k * ex;
            inc[i - 1] -= (k + 1) * ex;
            if(i > k){
                inc[i - k - 1] += ex;
            }
            sum[i] += k * ex;
            sum_sum[i] += k * ex;
            ans += ex;
        }
    }

    ll extra = 0;
    for(int i = (int)k - 1; i >= 1; i--){
        sum[i] = sum[i + 1] + inc[i];
        sum_sum[i] = sum_sum[i + 1] + sum[i];
        if(sum_sum[i] < aim[i]) {
            extra = max(extra, (aim[i] - sum_sum[i]) / i + (bool) ((aim[i] - sum_sum[i]) % i));
        }
    }
    ans += extra;

    printf("%lld\n", ans);
}