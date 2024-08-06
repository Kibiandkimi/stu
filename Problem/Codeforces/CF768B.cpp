//
// Created by Kibi on 24-8-4.
//
#include <bits/stdc++.h>
using namespace std;

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

using ull = unsigned long long;

class Config{
public:
    ull n, l, r;
};

uint solve(const Config &config);

int main(){
    auto n = read<ull>(), l = read<ull>(), r = read<ull>();

    Config config{n, l, r};

    auto ans = solve(config);

    printf("%u\n", ans);
}

uint solve(const Config &config) {
    if(config.r < config.l) {
        return 0;
    }
    if(config.n == 1) {
        return 1;
    }
    if(config.n == 0) {
        return 0;
    }

    auto siz = (static_cast<ull>(1) << static_cast<ull>(log2(config.n)) + 1) - 1;

    auto mid = (siz + 1) / 2;

    if(config.r < mid) {
        Config t = { config.n / 2, config.l, config.r};
        return solve(t);
    }
    if(config.l > mid) {
        Config t = {config.n / 2, config.l - mid, config.r - mid};
        return solve(t);
    }
    if(config.l == mid) {
        Config t = {config.n / 2, 1, config.r - mid};
        return solve(t) + (config.n & 1);
    }
    if(config.r == mid) {
        Config t = {config.n / 2, config.l, mid - 1};
        return solve(t) + (config.n & 1);
    }
    Config t1 = {config.n / 2, config.l, mid - 1}, t2 = {config.n / 2, 1, config.r - mid};
    return solve(t1) + (config.n & 1) + solve(t2);
}