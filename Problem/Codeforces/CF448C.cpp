//
// Created by kimi on 24-8-5.
//
#include <bits/stdc++.h>
using namespace std;

using uint = unsigned int;

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

class Config{
public:
    uint n;
    vector<uint> h;
};

uint solve(Config &config);

int main() {
    auto n = read<uint>();

    Config config{n, vector<uint>(n)};
    for(auto &i : config.h) {
        i = read<uint>();
    }

    auto ans = solve(config);
    printf("%u\n", ans);
}

uint calc(vector<uint>::iterator it, uint len) {
    if(len == 1 && *it == 0) {
        return 0;
    }
    if(len == 1) {
        return 1;
    }

    uint mn = *it, pos = 0;
    for(auto i = it + 1; i - it < len; ++i) {
        if(*it < mn) {
            mn = *it;
            pos = i - it;
        }
    }

    for(auto i = it; i - it < len; ++i) {
        *it -= mn;
    }

    return min(calc(it, pos + 1) + calc(it + pos + 1, len - pos - 1) + mn, len);
}

uint solve(Config &config) {
    return min(config.n, calc(config.h.begin(), config.n));
}