//
// Created by kimi on 24-8-5.
//
#include <bits/stdc++.h>
using namespace std;

using uint = unsigned int;
using ull = unsigned long long;

template<typename T>
T read() {
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

class Config {
public:
    uint n, k;
    vector<vector<uint>> arr;
};

ull solve(Config &config);

int main() {
    auto n = read<uint>(), k = read<uint>();

    Config config{n, k, vector<vector<uint>>(n)};
    for(auto &i : config.arr) {
        auto siz = read<uint>();
        i = vector<uint>(siz);
        for(auto &j : i) {
            j = read<uint>();
        }
    }

    auto ans = solve(config);
    printf("%llu\n", ans);
}

ull solve(Config &config) {
    vector<ull> sum(config.n);
    for(auto i = 0; i < config.n; ++i) {
        for(auto &j : config.arr[i]) {
            sum[i] += j;
        }
    }
}