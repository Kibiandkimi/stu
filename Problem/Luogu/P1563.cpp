//
// Created by kibi on 24-11-3.
//
#include <cctype>
#include <cstdio>
#include <string>
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

using People = tuple<bool, std::string>;
using Opt = tuple<bool, uint>;

class Config {
public:
    uint n, m;
    vec<People> peoples;
    vec<Opt> opts;
};

std::string solve(const Config&);

int main() {
    u32 n = read<uint>(), m = read<uint>();
    Config config{n, m, vec<People>(n), vec<Opt>(m)};
    for (auto &i : config.peoples) {
        auto type = read<uint>();
        uint c = getchar();
        while (!isalpha(c)) {
            c = getchar();
        }
        std::string str;
        while (isalpha(c)) {
            str.push_back(c);
            c = getchar();
        }
        i = {type, move(str)};
    }
    for (auto &i : config.opts) {
        u32 type = read<uint>(), num = read<uint>();
        i = {type, num};
    }
    auto ans = solve(config);
    printf("%s\n", ans.c_str());
}

std::string solve(const Config &config) {
    uint now = 0;
    for (auto &i : config.opts) {
        auto [type, num] = i;
        if (type ^ std::get<0>(config.peoples[now])) {
            now = (now + num) % config.n;
        } else {
            now = (now + config.n - num) % config.n;
        }
    }
    return std::get<1>(config.peoples[now]);
}
