//
// Created by Kibi on 24-9-29.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <deque>
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
    uint k, n;
    vector<uint> arr;
};

uint solve(const Config&);

int main() {
    auto k = read<uint>(), n = read<uint>();
    Config config{k, n, vector<uint>(n)};
    for (auto &i : config.arr) {
        i = read<uint>();
    }
    printf("%u\n", solve(config));
    return 0;
}

uint solve(const Config &config) {
    deque<tuple<uint, uint>> qmx, qmn;
    uint cnt = 0, res = 0;
    uint pre = 0;
    for (auto &i : config.arr) {
        while (!qmx.empty() && get<0>(qmx.back()) < i) {
            qmx.pop_back();
        }
        qmx.emplace_back(i, cnt);
        while (!qmn.empty() && get<0>(qmn.back()) > i) {
            qmn.pop_back();
        }
        qmn.emplace_back(i, cnt++);
        while (get<0>(qmx.front()) - get<0>(qmn.front()) > config.k) {
            if (get<1>(qmx.front()) > get<1>(qmn.front())) {
                pre = get<1>(qmn.front()) + 1;
                qmn.pop_front();
            } else {
                pre = get<1>(qmx.front()) + 1;
                qmx.pop_front();
            }
        }
        res = max(cnt - pre, res);
    }
    return res;
}
