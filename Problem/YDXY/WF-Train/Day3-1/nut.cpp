//
// Created by kibi on 24-10-5.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using ull = unsigned long long;

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
    uint n, m, k;
    vector<uint> h;
};

ull solve(const Config&);

int main() {
    freopen("nut.in", "r", stdin);
    freopen("nut.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>(), k = read<uint>();
    Config config{n, m, k, vector<uint>(n)};
    for (auto &i : config.h) {
        i = read<uint>();
    }
    printf("%llu\n", solve(config));

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ull solve(const Config& config) {

    auto check = [&config](ull u) {
        static vector<ull> pos(config.n);
        ull now = 1, sum = 0, cnt = 0, lst_cnt = 0;
        for (auto &i : config.h) {
            if (sum + i <= u) {
                sum += i;
                pos[cnt++] = now; // add
                now++;
                if (now > config.k && now - config.k == pos[lst_cnt]) { // check if trans
                    sum -= config.h[lst_cnt];
                    lst_cnt++;
                }
            } else {
                // force to trans
                while (sum + i > u) {
                    now += pos[lst_cnt] + config.k - now;
                    sum -= config.h[lst_cnt];
                    lst_cnt++;
                }
                // add
                sum += i;
                pos[cnt++] = now;
                now++;
            }
        }
        return pos.back() <= config.m;
    };

    ull l = 0, r = 0;
    for_each(config.h.begin(), config.h.end(), [&l, &r](uint i) {
        r += i;
        l = max(l, static_cast<ull>(i));
    });
    ull sum = r;
    while (l < r) {
        ull mid = (l + r) / 2;
        if (!check(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return sum - l;
}