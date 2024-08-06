//
// Created by kibi on 24-7-29.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using uint = unsigned int;

    auto read = [](){
        uint s = 0, c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        return s;
    };

    using U = tuple<uint, uint>;

    auto T = read();

    while(T--){
        auto n = read();
        vector<uint> req(n), pri(n);
        vector<U> dist(n);

        for(auto &i : req){
            i = read();
        }
        for(auto &i : pri){
            i = read();
        }

        bool flag = true;

        for(int i = 0; i < n - 1; i++){
            if(req[i + 1] <= pri[i]){
                pri[i] -= (get<0>(dist[i + 1]) = req[i + 1]);
            }else if(req[i + 1] <= pri[i] + pri[i + 1]){
                pri[i] -= (get<0>(dist[i + 1]) = pri[i]);
                pri[i + 1] -= (get<1>(dist[i + 1]) = req[i + 1] - get<0>(dist[i + 1]));
            }else{
                flag = false;
                break;
            }
        }

        if(!flag){
            printf("NO\n");
            continue;
        }

        if(req[0] <= pri[n - 1]){
            printf("YES\n");
            continue;
        }

        req[0] -= pri[n - 1];

        for(uint i = n - 2; i > 0; i--){
            if(pri[i] > 0){
                pri[i - 1] += min(pri[i], get<0>(dist[i]));
            }
        }

        if(pri[0] >= req[0]){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
}