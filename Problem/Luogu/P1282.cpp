//
// Created by Lenovo on 24-4-14.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while(c < '0' || '9' < c){
            if(c == '-'){
                w = -1;
            }
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c  - '0';
            c = getchar();
        }
        x = s * w;
    };

    int n;
    read(n);

    int data[n], raw = 0;
    for(auto &i : data){
        int a, b;
        read(a), read(b);
        i = a - b;
        raw += i;
    }

    using Mp = map<int, int>;

    Mp mp;
    mp[raw] = 0;

    for(auto &i : data){
        static Mp nmp; // new map
        nmp = mp; // TODO map copy not good
        for(auto &j : mp){
            auto val = j.first - 2 * i;
            auto res = mp.find(val);
            if(res == mp.end()){ // a-b -> b-a
                auto new_res = nmp.find(val); // new res
                if(new_res == nmp.end()) {
                    nmp[val] = j.second + 1;
                }else{
                    new_res->second = min(new_res->second, j.second + 1);
                }
            }else{
                //                res->second = min(res->second, j.second + 1);
                nmp[val] = min(nmp[val], j.second + 1);
            }
        }
        mp = nmp;
    }

    int now = 1e9, ans = 0;
    for(auto &j : mp){
        if(abs(j.first) < now){
            ans = j.second;
            now = abs(j.first);
        }else if(abs(j.first) == now){
            ans = min(ans, j.second);
        }
    }

    printf("%d\n", ans);
}