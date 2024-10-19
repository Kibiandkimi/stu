//
// Created by kibi on 24-10-9.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <numeric>
#include <set>
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

using Int = long long; // no range were given!

using Event = tuple<Int, Int>;

class Config {
public:
    uint n;
    vector<Event> events;
};

long long solve(const Config&);

int main() {
    freopen("coin.in", "r", stdin);
    freopen("coin.out", "w", stdout);

    auto n = read<uint>();
    Config config{n, vector<Event>(n)};
    for (auto &i : config.events) {
        i = {read<Int>(), read<Int>()};
    }
    long long ans = solve(config);
    printf("%lld\n", ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}

long long solve(const Config& config) {
    auto events = config.events;
    sort(events.begin(), events.end(), [](const Event &a, const Event &b){
        return get<0>(a) < get<0>(b);
    });

    Int lst_time = get<0>(events.back()), cnt = 0;
    for (auto &i : events) {
        if (get<0>(i) == lst_time) {
            cnt++;
        }
        if (cnt >= 3) {
            return -1;
        }
    }

    auto check = [&events](Int k) {
        set<Event> st; // t, x
        bool flag = true;
        Event lst = {get<0>(*events.begin()) - 1, get<1>(*events.begin())};
        for (auto &i : events) {
            auto [lst_t, lst_x] = lst;
            auto [now_t, now_x] = i;
            if (flag && abs(lst_x - now_x) <= k * (now_t - lst_t)) {
                lst = i;
            } else if (flag){
                flag = false;
                st.insert(lst);
                lst = i;
            } else {
                bool flag = false;
                for (auto &j : st) {
                    auto [lst_t, lst_x] = j;
                    if (abs(lst_x - now_x) <= k * (now_t - lst_t)) {
                        flag = true;
                        break;
                    }
                }
                if (abs(lst_x - now_x) <= k * (now_t - lst_t)) {
                    flag ? static_cast<void>(st.insert(lst)) : static_cast<void>(0);
                } else if (!flag) {
                    return false;
                } else {
                    st.clear();
                    st.insert(lst);
                }
                lst = i;
            }
        }

        return true;
    };

    Int l = 0, r = 1'000'000'000ll;
    while (l < r) {
        auto mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return r;
}

