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

    uint end = read(), n = read(), m = read();

    vector<uint> raw(n);
    for(auto &i : raw){
        i = read();
    }

    auto check = [end, m, &raw](uint k){
        uint lst = 0;
        uint temp = m;
        for(auto &i : raw){
            if(i - lst < k){
                if(temp == 0){
                    return false;
                }
                temp--;
            }else{
                lst = i;
            }
        }
        if(end - lst < k && temp == 0){
            return false;
        }
        return true;
    };

    uint l = 1, r = end;
    while(l <= r){
        auto mid = (l + r) / 2;
        if(check(mid)){
            l = mid + 1;
        }else{
            r = mid - 1;
        }
    }

    printf("%u\n", r);
}