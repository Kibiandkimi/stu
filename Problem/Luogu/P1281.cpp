//
// Created by Kibi on 24-9-22.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
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
    uint k;
    vector<uint> length;
};

vector<uint> solve(const Config&);

int main() {
    auto m = read<uint>(), k = read<uint>();
    Config config{k, vector<uint>(m)};
    for (auto &i : config.length) {
        i = read<uint>();
    }

    auto ans = solve(config);
    uint now = 0;
    for (auto &i : ans) {
        printf("%u %u\n", now + 1 - (i ? 0 : 1), now + i);
        now += i;
    }
    return 0;
}

vector<uint> solve(const Config& config) {
    uint l = 0, r = 0;
    for (auto &i : config.length) {
        l = max(l, i);
        r += i;
    }

    auto check = [&](uint k) {
        uint res = 0, lst = 0;
        for (auto &i : config.length) {
            if (lst + i > k) {
                lst = i;
                res++;
            }else {
                lst += i;
            }
        }
        res += lst ? 1 : 0;
        return res <= config.k;
    };

    while (l < r) {
        auto mid = (l + r) / 2;
        if (!check(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }

    auto length = config.length;
    reverse(length.begin(), length.end());
    vector<uint> res;
    uint lst = 0, num = 0;
    for (auto &i : length) {
        if (lst + i > l) {
            res.push_back(num);
            lst = i;
            num = 1;
        }else {
            lst += i;
            num++;
        }
    }
    num ? res.push_back(num) : static_cast<void>(0);

    while (res.size() < config.k) {
        res.push_back(0);
    }

    reverse(res.begin(), res.end());

    return res;
}