//
// Created by kibi on 24-7-29.
//
// TODO not correct
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ull = unsigned long long;

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

    auto read_ll = [](){
        ull s = 0, c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        return s;
    };

    using E = tuple<uint, uint>;

    uint T = read();

    while(T--){
        uint n = read(); ull s = read_ll(); vector<E> emp(n);

        for(auto &i : emp){
            i = {read(), read()};
            s -= get<0>(i);
        }

        sort(emp.begin(), emp.end(), [](const E &a, const E &b){return get<0>(a) < get<0>(b);});

        uint pos = n / 2, num = 1, mn = get<1>(emp[n / 2]), now = get<0>(emp[n / 2]);
        while(s > 0 && mn > now && ++pos < n){
            if(mn < get<0>(emp[pos]) || s < (ull)num * (get<0>(emp[pos]) - now)){
                break;
            }else{
                s -= (ull)num * (get<0>(emp[pos]) - now);
                now = get<0>(emp[pos]);
                mn = min(mn, get<1>(emp[pos]));
            }
        }

        printf("%llu\n", min((ull)mn, s / num + now));
    }
}