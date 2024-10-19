//
// Created by kibi on 24-10-8.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

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

using Pos = tuple<int, int, int>;

class Config {
public:
    uint n;
    vector<Pos> arr;
};

uint solve(const Config&);

int main() {
    freopen("hunt.in", "r", stdin);
    freopen("hunt.out", "w", stdout);

    auto n = read<uint>();
    Config config{n, vector<Pos>(n)};
    for (auto &i : config.arr) {
        i = {read<int>(), read<int>(), read<int>()};
    }
    printf("%u\n", solve(config));

    fclose(stdin);
    fclose(stdout);
    return 0;
}

uint solve(const Config& config) {
    // stupid try
    /*uint res = 0;
    for (auto &i : config.arr) {
        for (auto &j : config.arr) {
            auto [x1, y1, z1] = i, [x2, y2, z2] = j;
            if (!(x1 - x2 <= 0 && y1 - y2 <= 0 && z1 - z2 <= 0) &&
                (x1 - x2 >= 0 && y1 - y2 >= 0 && z1 - z2 >= 0)){
                res = max(res, min())
            }
        }
    }*/
    if (true || config.n <= 1'000) {
        vector<tuple<bool, Pos>> arr;
        arr.reserve(config.n);
        for_each(config.arr.begin(), config.arr.end(), [&arr](auto &p) {
            arr.emplace_back(false, p);
        });
        auto check = [&arr] (int k) {
            bool flag = true;
            int x = 0, y = 0, z = 0;
            for (auto &i : arr) {
                get<0>(i) = false;
            }
            while (flag) {
                int mxx = 1'000'000'000, mxy = 1'000'000'000, mxz = 1'000'000'000;
                flag = false;
                for (auto &i : arr) {
                    if (!get<0>(i)) {
                        auto [tx, ty, tz] = get<1>(i);
                        if (max({abs(x - tx), abs(y - ty), abs(z - tz)}) <= k) {
                            get<0>(i) = true;
                            continue;
                        }
                        flag = true;
                        mxx = min(mxx, tx + k);
                        mxy = min(mxy, ty + k);
                        mxz = min(mxz, tz + k);
                    }
                }
                if (flag && x >= mxx && y >= mxy && z >= mxz) {
                    return false;
                }
                x = mxx, y = mxy, z = mxz;
            }
            return true;
        };

        int l = 0, r = 1'000'000'000;
        while (l < r) {
            auto mid = (l + r) >> 1;
            if (check(mid)) {
                r = mid;
            }else {
                l = mid + 1;
            }
        }
        return r;
    }
}