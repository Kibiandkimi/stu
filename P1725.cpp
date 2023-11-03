//
// Created by kibi on 23-11-3.
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

    int n, l, r;
    read(n), read(l), read(r);

    int raw_data[n + 1];
    for(auto &i : raw_data){
        read(i);
    }

    int f[n + r + 1];
    memset(f, 0xc0, sizeof f);
    f[0] = 0;
    deque<pair<int, int>> q;
    for(int i = 1; i <= n + r; i++){
        if(i - l >= 0){
            while(!q.empty() && q.back().second < f[i - l]){
                q.pop_back();
            }
            q.emplace_back(i - l, f[i - l]);
        }
        while(!q.empty() && q.front().first < i - r){
            q.pop_front();
        }
        if(!q.empty()){
            f[i] = q.front().second + (i <= n ? raw_data[i] : 0);
        }
    }

    int ans = f[n + 1];
    for(int i = n + 2; i <= n + r; i++){
        ans = max(ans, f[i]);
    }
    printf("%d\n", ans);
}