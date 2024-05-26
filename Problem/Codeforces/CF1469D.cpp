//
// Created by kibi on 23-11-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    int T;
    read({&T});

    while(T--){
        static vector<pair<int, int>> ans;
        int n;
        read({&n});

        ans.clear();

        if(n <= 8){
            for(int i = 3; i < n; i++){
                ans.emplace_back(i, i + 1);
            }
            int t = n;
            while(t > 1){
                ans.emplace_back(n, 2);
                t = t / 2 + t % 2;
            }
        }else{
            for(int i = 8 + 1; i < n; i++){
                ans.emplace_back(i, i + 1);
            }
            int t = n;
            while(t > 1){
                ans.emplace_back(n, 8);
                t = t / 8 + (bool)(t % 8);
            }
            for(int i = 3; i < 8; i++){
                ans.emplace_back(i, i + 1);
            }
            for(int i = 0; i < 3; i++){
                ans.emplace_back(8, 2);
            }
        }
        printf("%d\n", (int)ans.size());
        for(auto &i : ans){
            printf("%d %d\n", i.first, i.second);
        }
    }
}