//
// Created by Lenovo on 24-10-20.
//
//
// Created by Lenovo on 24-10-20.
//
#include <array>
#include <cctype>
#include <cstdio>
#include <numeric>
#include <sys/types.h>
#include <tuple>
#include <vector>

using ull = unsigned long long;
using ll = long long;
using uint = unsigned int;

template<typename T>
using vec = std::vector<T>;

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
    uint c, n, m;
    vec<std::array<bool, 2>> mp;
};

uint solve(const Config &);

int main() {
    // freopen(R"(C:\Users\Lenovo\AppData\Local\Temp\summer4.in)", "r", stdin);

    auto c = read<uint>(), T = read<uint>();
    while (T--) {
        auto n = read<uint>(), m = read<uint>();
        Config config{c, n, m, .mp{n, {false, false}}};
        auto temp = getchar();
        while (temp != '0' && temp != '1') {
            temp = getchar();
        }
        for (auto &i : config.mp) {
            i[0] = temp - '0';
            temp = getchar();
        }
        while (temp != '0' && temp != '1') {
            temp = getchar();
        }
        for (auto &i : config.mp) {
            i[1] = temp - '0';
            temp = getchar();
        }
        auto ans = solve(config);
        printf("%u\n", ans);
    }
}

uint solve(const Config &config) {
    if (config.c >= 12 && config.c <= 13) { // A
        vec<int> sum(config.n);
        vec<int> temp;
        temp.reserve(config.n);
        for (auto &i : config.mp) {
            temp.push_back(i[0] ? 2 : -1);
        }
        std::partial_sum(temp.begin(), temp.end(), sum.begin());
        int mn = 0;
        int res = 0;
        for (auto &i : sum) {
            mn = std::min(mn, i);
            res = std::max(res, i - mn);
        }
        return res;
    }
    if (config.c >= 14 && config.c <= 15) { // B & C
        uint cnt = 0;
        bool flag_down = true, flag_up = true;
        for (auto &i : config.mp) {
            if (i[0] && flag_up) {
                cnt++;
                // flag_up = true;
                flag_down = false;
            }else if (i[1] && flag_down) {
                cnt++;
                flag_up = false;
                // flag_down = true
            } else {
                flag_up = flag_down = true;
            }
        }
        if (cnt >= config.m * 2) {
            cnt -= config.m * 2;
        }else {
            cnt = 0;
        }
        return cnt;
    }
    if (config.c >= 18 && config.c <= 19) {
        uint cnt = 0, cnt2 = 0;
        bool flag_down = true, flag_up = true;
        for (auto &i : config.mp) {
            if(i[0] && i[1]) {
                cnt2++;
                flag_down = flag_up = true;
            }else if (i[0] && flag_up) {
                cnt++;
                // flag_up = true;
                flag_down = false;
            }else if (i[1] && flag_down) {
                cnt++;
                flag_up = false;
                // flag_down = true
            } else {
                flag_up = flag_down = true;
            }
        }
        if (cnt >= config.m * 2) {
            return cnt - config.m * 2 + cnt2 * 2;
        }
        return cnt2 * 2;
        // cnt = cnt2 = 0;
        // for (auto &i : config.mp) {
        //     if (i[0] && i[1]) {
        //         cnt2++;
        //     } else {
        //         cnt = max(cnt, cnt2);
        //         cnt2 = 0;
        //     }
        // }
    }
}
