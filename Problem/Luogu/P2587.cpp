//
// Created by kimi on 24-8-2.
//
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read(){
    T s = 0, w = 1, c = getchar();
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
    return s * w;
}

class Config{
public:
    int n;
    vector<uint> u, v;
};

uint run(Config &config);

int main(){
    auto n = read<int>();

    Config config{n, vector<uint>(n), vector<uint>(n)};

    for(auto &i : config.u){
        i = read<uint>();
    }
    for(auto &i : config.v){
        i = read<uint>();
    }

    sort(config.u.begin(), config.u.end());
    sort(config.v.begin(), config.v.end());

    auto mx = run(config);

    swap(config.u, config.v);
    auto mn = 2 * n - run(config);

    printf("%u %u\n", mx, mn);
}

uint run(Config &config){

    uint res = 0;
    auto ul = config.u.begin(), ur = config.u.end() - 1,
         vl = config.v.begin(), vr = config.v.end() - 1;
    while(ul <= ur){
        if(*ul > *vl) {
            res += 2;
            ++ul;
            ++vl;
        }else if(*ur > *vr) {
            res += 2;
            --ur;
            --vr;
        }else {
            res += (*ul == *vr);
            ++ul;
            --vr;
        }
    }
    return res;
}