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

    int T;
    read(T);

    vector<int> logn(3);
    logn[2] = 1;

    while(T--){
        int n;
        read(n);

        while(logn.size() < n){
            logn.emplace_back(logn[logn.size() / 2] + 1);
        }

        ll raw_data[n];
        for(ll &i : raw_data){
            read_ll(i);
        }

        ll inc[n];
        //        inc[0] = raw_data[0];
        for(int i = 1; i < n; i++){
            inc[i] = abs(raw_data[i] - raw_data[i - 1]);
        }

        ll f[n][21];
        for(int i = 1; i < n; i++){
            f[i][0] = inc[i];
        }

        for(int j = 1; j < 21; j++){
            for(int i = 1; i + (1 << j) - 1 < n; i++){
                f[i][j] = gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
            }
        }

        auto query = [&](int l, int r){
            int s = logn[r - l + 1];
            return gcd(f[l][s], f[r - (1 << s) + 1][s]);
        };

        int ans = 0;
        for(int i = 1, l, r, res; i < n; i++){
            l = i, r = n - 1, res = l;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(query(i, mid) == 1){
                    r = mid - 1;
                }else{
                    res = mid;
                    l = mid + 1;
                }
            }
            if(inc[i] != 1){
                ans = max(ans, res - i + 1);
            }
        }

        printf("%d\n", ans + 1);
    }

}