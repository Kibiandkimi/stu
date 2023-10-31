//
// Created by kibi on 23-10-31.
//
#include <bits/stdc++.h>
using namespace std;

// si - sj
// si - sj - (sa - sb) (i >= a >= b >= j)
// si - sa + sb - sj

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
    auto read_ll = Tools::read_ll;

    int n, d;
    ll p;
    read(n), read_ll(p), read(d);

    int raw_data[n];
    for(auto &i : raw_data){
        read(i);
    }

    ll sum[n + 1];
    sum[0] = 0;
    sum[1] = raw_data[0];
    for(int i = 2; i <= n; i++){
        sum[i] = sum[i - 1] + raw_data[i - 1];
    }

    int ans = d;
    int i = d, j = 1;
    deque<pair<int, ll>> q;
    q.emplace_back(1, sum[d]);
    while(!q.empty() && q.back().second <= sum[i + 1] - sum[i - d + 1]){
        q.pop_back();
    }
    q.emplace_back(2, sum[d + 1] - sum[1]);
    while(i < n){
        while(sum[i + 1] - sum[j - 1] - q.front().second <= p && i < n){
            i++;
            while(!q.empty() && q.back().second <= sum[i + 1] - sum[i + 1 - d]){
                q.pop_back();
            }
            q.emplace_back(i - d + 2, sum[i + 1] - sum[i + 1 - d]);
        }
        ans = max(ans, i - j + 1);
        j++;
        while(!q.empty() && q.front().first < j){
            q.pop_front();
        }
    }

    printf("%d\n", ans);
}