//
// Created by kibi on 23-11-4.
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

    int n, k;
    read(n), read(k);

    using ll = long long;
    ll sum = 0;
    int e[n];
    for(auto &i : e){
        read(i);
        sum += i;
    }

    //    int f[n + 1];
    deque<pair<int, ll>> q;
    q.emplace_back(-1, 0);
    q.emplace_back(0, e[0]);
    for(int i = 1; i < n; i++){
        while(!q.empty() && q.front().first < i - k - 1){
            q.pop_front();
        }
        ll now = q.front().second + e[i];
        while(!q.empty() && q.back().second >= now){
            q.pop_back();
        }
        q.emplace_back(i, now);
    }
    while(!q.empty() && q.front().first < n - k - 1){
        q.pop_front();
    }
    ll res = q.front().second;

    printf("%lld\n", sum - res);
}