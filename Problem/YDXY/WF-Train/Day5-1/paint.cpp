//
// Created by kibi on 24-10-7.
//
//
// Created by kibi on 24-10-7.
//
#include <algorithm>
#include <array>
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

uint readc() {
    uint c = getchar();
    while (c != 'R' && c != 'G' && c != 'B') {
        c = getchar();
    }
    return c == 'R' ? 0 : c == 'G' ? 1 : 2;
}

enum Color{
    red = 0,
    blue = 1,
    green = 2,
};

using Limit = tuple<uint, Color, uint, Color>;

class Config {
public:
    uint n, m;
    vector<Limit> limits;
};

auto trans = [](uint u) {
    return
    u == 0 ? Color::red :
    u == 1 ? Color::blue :
    u == 2 ? Color::green :
    throw runtime_error("Invalid input!");
};

ull solve(const Config&);

int main () {
    // freopen("paint.in", "r", stdin);
    // freopen("paint.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<Limit>(m)};
    for (auto &i : config.limits) {
        i = {read<uint>() - 1, trans(readc()), read<uint>() - 1, trans(readc())};
    }
    printf("%llu\n", solve(config));

    fclose(stdin);
    fclose(stdout);
    return 0;
}

template<typename T>
auto pow = [] (T a, T p) {
    T res = 1;
    while (p--) {
        res *= a;
    }
    return res;
};

ull solve(const Config& config) {
    if (false && config.n <= 13) {
        ull res = 0;

        const uint mxi = pow<uint>(3, config.n);
        vector<Color> col(config.n);
        for (uint i = 0; i < mxi; i++) {
            auto temp = i;
            for (auto &j : col) {
                j = trans(temp % 3);
                temp /= 3;
            }
            bool flag = true;
            for (auto &j : config.limits) {
                if (col[get<0>(j)] == get<1>(j) && col[get<2>(j)] == get<3>(j)) {
                    flag = false;
                    break;
                }
            }
            res += flag;
        }
        return res;
    }
    if (false && all_of(config.limits.begin(), config.limits.end(), [](const auto &x){
        return get<1>(x) == 0 && get<3>(x) == 0;
    })) {
        ull res = 0;
        const uint mxi = 1 << config.n;
        vector<bool> col(config.n);
        for (uint i = 0; i < mxi; i++) {
            auto temp = i;
            ull num = 0;
            for (uint j = 0; j < config.n; j++) {
                col[j] = temp & 1;
                num += col[j];
                temp >>= 1;
            }
            bool flag = true;
            for (auto &j : config.limits) {
                if (col[get<0>(j)] && col[get<2>(j)]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                num = config.n - num;
                res += 1 << num;
            }
        }
        return res;
    }

    // using MyLimit = tuple<uint, Color, uint, Color, bool>;

    // vector<MyLimit> limits(config.m);
    // for (uint i = 0; i < config.m; i++) {
    //     limits[i] = {
    //         get<0>(config.limits[i]),
    //         get<1>(config.limits[i]),
    //         get<2>(config.limits[i]),
    //         get<3>(config.limits[i]),
    //         false
    //     };
    // }

    auto limits = config.limits;

    using DestMap = vector<array<array<vector<bool*>, 3>, 2>>;

    DestMap dest(config.n);

    for (auto &i : limits) {
        if (get<0>(i) > get<2>(i)) {
            swap(get<0>(i), get<2>(i));
            swap(get<1>(i), get<3>(i));
        }
        auto flag = new bool{true};
        dest[get<0>(i)][0][get<1>(i)].emplace_back(flag);
        dest[get<2>(i)][1][get<3>(i)].emplace_back(flag);
    }

    auto dfs = [&config, &dest](uint u, auto &&dfs) -> ull {
        if (u == config.n) {
            return 1;
        }
        uint flag = 7; // 7 -> 111
        for (uint col = 0; col < 3; col++) {
            for (auto i : dest[u][1][col]) {
                if (!*i) {
                    flag &= 111 ^ 1 << col;
                    break;
                }
            }
        }
        if (!flag) {
            return 0;
        }
        if (dest[u][0][0].empty() && dest[u][0][1].empty() && dest[u][0][2].empty()) {
            return ((flag & 1) + (flag >> 1 & 1) + (flag >> 2 & 1)) * dfs(u + 1, dfs);
        }
        if (dest[u][0][0].empty() + dest[u][0][1].empty() + dest[u][0][2].empty() == 2) {
            ull res = 0;
            uint cnt = 0;
            for (uint col = 0; col < 3; col++) {
                if (1 << col & flag) {
                    if (!dest[u][0][col].empty()) {
                        for (auto i : dest[u][0][col]) {
                            *i = false;
                        }
                        res += dfs(u + 1, dfs);
                        for (auto i : dest[u][0][col]) {
                            *i = true;
                        }
                    }else {
                        cnt++;
                    }
                }
            }
            res += cnt ? cnt * dfs(u + 1, dfs) : 0;
            return res;
        }
        ull res = 0;
        for (uint col = 0; col < 3; col++) {
            if (1 << col & flag) {
                for (auto i : dest[u][0][col]) {
                    *i = false;
                }
                res += dfs(u + 1, dfs);
                for (auto i : dest[u][0][col]) {
                    *i = true;
                }
            }
        }
        return res;
    };

    return dfs(0, dfs);
}