//
// Created by kibi on 24-11-2.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using u32 = const unsigned int;
using u64 = const unsigned long long;
using ull = unsigned long long;

using std::tuple;

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
    uint n;
    vec<uint> d;
};

u64 solve(const Config&);

int main() {
    u32 n = read<uint>();
    Config config{n, vec<uint>(n)};
    for (auto &i : config.d) {
        i = read<uint>();
    }
    printf("%llu\n", solve(config));
    return 0;
}

std::tuple<ull, uint> calc(uint st, uint aim, const vec<uint> &d) { // return {step, r};
    ull res = 0;
    uint now = d[st];
    for (uint i = st + 1; i < d.size(); i++) {
        if (d[i] < aim) {
            return {res + now - aim, i - 1};
        }
        if (d[i] > now) {
            auto [temp_res, r] = calc(i, now, d);
            res += temp_res;
            i = r;
        } else if (d[i] < now) {
            res += now - d[i];
            now = d[i];
        }
    }
    return {res + now - aim, d.size() - 1};
}

u64 solve(const Config &config) {
    return std::get<0>(calc(0, 0, config.d));
}
