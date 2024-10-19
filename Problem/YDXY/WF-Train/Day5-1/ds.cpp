//
// Created by kibi on 24-10-7.
//
//
// Created by kibi on 24-10-7.
//
//
// Created by kibi on 24-10-7.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <system_error>
#include <tuple>
#include <vector>
using namespace std;

using ull = unsigned long long;

template<typename T>
T read () {
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

using Tp = tuple<uint, uint>;

class Config {
public:
    uint n;
    vector<Tp> tps;
};

vector<uint> solve(const Config &);

int main() {
    freopen("ds.in", "r", stdin);
    freopen("ds.out", "w", stdout);

    auto n = read<uint>();
    Config config{n, vector<Tp>(n)};
    for (auto &i : config.tps) {
        i = {read<uint>(), read<uint>()};
    }
    auto ans = solve(config);
    for (auto &i : ans) {
        printf("%u ", i);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

using MyTp = tuple<uint, Tp>;

vector<uint> solve(const Config &config) {
    if (all_of(config.tps.begin(), config.tps.end(), [](const Tp &t) {
        return get<0>(t) == 0 || get<1>(t) == 1'000'000'000;
    })) {
        vector<uint> res;
        vector<MyTp> l, r;
        uint cnt = 0;
        for (auto &i : config.tps) {
            if (get<0>(i) == 0) {
                l.emplace_back(++cnt, i);
            }else {
                r.emplace_back(++cnt, i);
            }
        }
        sort(l.begin(), l.end(), [](const MyTp &a, const MyTp &b) {
            return get<1>(get<1>(a)) < get<1>(get<1>(b));
        });
        sort(r.begin(), r.end(), [](const MyTp &a, const MyTp &b) {
            return get<0>(get<1>(a)) > get<0>(get<1>(b));
        });
        auto it_l = l.begin(), it_r = r.begin();
        uint l_pos = 0, r_pos = 1'000'000'001;
        auto len = [&l_pos, &r_pos](Tp &tp) {
            return max(0,
                static_cast<int>(min(r_pos - 1, get<1>(tp))) -
                    static_cast<int>(max(l_pos, get<0>(tp)))
            );
        };

        bool l_sorted = false , r_sorted = false;

        auto sort_r = [&r_sorted](const auto it, const auto end) {
            r_sorted = true;
            sort(it, end, [](const MyTp &a, const MyTp &b) {return get<0>(a) < get<0>(b); });
        };
        auto sort_l = [&l_sorted](const auto it, const auto end) {
            l_sorted = true;
            sort(it, end, [](const MyTp &a, const MyTp &b) {return get<0>(a) < get<0>(b); });
        };

        while (it_l != l.end() && it_r != r.end()) {
            if (len(get<1>(*it_l)) < len(get<1>(*it_r))) {
                res.push_back(get<0>(*it_l));
                l_pos = max(l_pos, get<1>(get<1>(*it_l)));
                ++it_l;
            } else if (len(get<1>(*it_r)) < len(get<1>(*it_l))) {
                res.push_back(get<0>(*it_r));
                r_pos = min(r_pos, get<0>(get<1>(*it_r)) + 1);
                ++it_r;
            } else if (get<0>(*it_l) < get<0>(*it_r)) {
                res.push_back(get<0>(*it_l));
                l_pos = max(l_pos, get<1>(get<1>(*it_l)));
                ++it_l;
            } else {
                res.push_back(get<0>(*it_r));
                r_pos = min(r_pos, get<0>(get<1>(*it_r)) + 1);
                ++it_r;
            }
            if (!r_sorted && l_pos > get<0>(get<1>(*it_r))) {
                sort_r(it_r, r.end());
            }
            if (!l_sorted && r_pos <= get<1>(get<1>(*it_l))) {
                sort_l(it_l, l.end());
            }
        }
        while (it_l != l.end()) {
            res.push_back(get<0>(*it_l));
            l_pos = max(l_pos, get<1>(get<1>(*it_l)));
            ++it_l;
            if (!l_sorted && r_pos <= get<1>(get<1>(*it_l))) {
                sort_l(it_l, l.end());
            }
        }
        while (it_r != r.end()) {
            res.push_back(get<0>(*it_r));
            r_pos = min(r_pos, get<0>(get<1>(*it_r)));
            ++it_r;
            if (!r_sorted && l_pos >= get<0>(get<1>(*it_r))) {
                sort_r(it_r, r.end());
            }
        }
        return res;
    }
}