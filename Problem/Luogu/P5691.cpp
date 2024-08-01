//
// Created by kibi on 24-7-27.
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
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    };

    int n, m;
    read(n), read(m);

    if(n == 1){
        printf("0\n");
    }else if(n == 2){

    }

    int pre = n / 2;
    int suc = n - pre;

    map<int, uint> mp;

    vector<tuple<int, int>> x(n);

    for(auto &i : x){
        read(get<0>(i)), read(get<1>(i));
    }

    vector<int> val(pre);
    stack<tuple<int, int>> stk;
    stk.emplace(1, 1);
    while(!stk.empty()){
        auto [u, step] = stk.top();
        if(step + 1 == pre){

        }
    }
}