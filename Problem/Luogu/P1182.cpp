//
// Created by kibi on 24-7-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
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

    uint n = read(), m = read();

    uint l = 0, r = 0;

    vector<uint> raw(n);
    for(auto &i : raw){
        i = read();
        l = max(l, i);
        r += i;
    }

    auto check = [m, &raw](uint k){
        uint lst = k;
        uint temp = m;
        for(auto &i : raw){
            if(lst + i <= k){
                lst += i;
            }else{
                if(temp == 0){
                    return false;
                }
                temp--;
                lst = i;
            }
        }
        return true;
    };

    while(l < r){
        auto mid = (l + r) / 2;
        if(check(mid)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }

    printf("%d\n", l);

}