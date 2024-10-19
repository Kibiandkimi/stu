//
// Created by Kibi on 24-9-29.
//
//
// Created by Kibi on 24-9-29.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using uint = unsigned int;

template<typename T>
T read() {
    T s = 0, w = 1, c = getchar();
    while (!isdigit(c)) {
        if (c == '-') {
            w = -1;
        }
        c = getchar();
    }
    while (isdigit(c)) {
        s = s * 10 + c - '0';
        c = getchar();
    }
    return s * w;
}

class Config {
public:
    uint c, l;
    vector<tuple<uint, uint>> cows, sunscreens;
};

uint solve(const Config&);

int main() {
    auto c = read<uint>(), l = read<uint>();
    Config config{c, l, vector<tuple<uint, uint>>(c), vector<tuple<uint, uint>>(l)};
    for (auto &i : config.cows) {
        i = {read<uint>(), read<uint>()};
    }
    for (auto &i : config.sunscreens) {
        i = {read<uint>(), read<uint>()};
    }
    printf("%u\n", solve(config));
    return 0;
}

uint solve(const Config &config) {
    uint res = 0;
    auto cows = config.cows, sunscreens = config.sunscreens;
    sort(cows.begin(), cows.end(), [](const auto &a, const auto &b) {return get<1>(a) < get<1>(b);});
    sort(sunscreens.begin(), sunscreens.end(), [](const auto &a, const auto &b) {return get<0>(a) < get<0>(b);});
    for(auto &i : cows) {
        for(auto &j : sunscreens) {
            if(get<1>(j) > 0 && get<0>(j) <= get<1>(i) && get<0>(j) >= get<0>(i)) {
                get<1>(j)--;
                res++;
                break;
            }
        }
    }
    return res;
}
