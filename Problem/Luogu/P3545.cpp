//
// Created by Kibi on 24-10-15.
//
#include <cctype>
#include <cstdio>
#include <queue>
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
    uint n;
    vector<uint> a, b;
};

tuple<uint, vector<uint>> solve(const Config&);

int main() {
    auto n = read<uint>();
    Config config{n, vector<uint>(n), vector<uint>(n)};
    for (auto &i : config.a) {
        i = read<uint>();
    }
    for (auto &i : config.b) {
        i = read<uint>();
    }
    auto [num, ans] = solve(config);
    printf("%u\n", num);
    for (auto &i : ans) {
        printf("%u ", i);
    }
    return 0;
}

tuple<uint, vector<uint>> solve(const Config& config) {
    priority_queue<tuple<uint, uint>> pq;
    unsigned long long now = 0;
    for (uint i = 0; i < config.n; i++) {
        now += config.a[i];
        if (now < config.b[i]) {
            if (!pq.empty() && get<0>(pq.top()) > config.b[i]) {
                now += get<0>(pq.top()) - config.b[i];
                pq.pop();
                pq.emplace(config.b[i], i);
            }
        }else {
            now -= config.b[i];
            pq.emplace(config.b[i], i);
        }
    }
    uint siz = pq.size();
    vector<uint> res;
    while (!pq.empty()) {
        res.push_back(get<1>(pq.top()) + 1);
        pq.pop();
    }
    // res.sort()
    return {siz, res};
}

