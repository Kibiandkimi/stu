//
// Created by kibi on 24-11-2.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stack>
#include <sys/types.h>
#include <tuple>
#include <vector>

// TODO
// WA + TLE

template<typename T>
using vec = std::vector<T>;
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

class Config {
public:
    vec<uint> str;
};

uint solve(const Config&);

int main() {
    uint T = read<uint>();
    while (T--) {
        vec<uint> str;
        uint c = getchar();
        while (!isalpha(c)) {
            c = getchar();
        }
        while (isalpha(c)) {
            str.push_back(c - 'a');
            c = getchar();
        }
        printf("%u\n", solve({move(str)}));
    }
}

ull quick_pow(ull base, uint exp) {
    ull result = 1;
    while (exp) {
        if (exp & 1) {
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}

uint solve(const Config &config) {
    constexpr ull P = 1812433253UL;
    const uint n = config.str.size();
    vec<ull> hash_val(n), alpha_num(n);
    auto now = P;
    hash_val[0] = config.str[0] * P;
    alpha_num[0] = (1 << config.str[0]);
    for (uint i = 1; i < n; i++) {
        now *= P;
        hash_val[i] = hash_val[i - 1] + now * config.str[i];
        alpha_num[i] = alpha_num[i - 1] ^ (1 << config.str[i]);
    }

    auto get_hash = [&hash_val, n, P](uint l, uint r) {
        auto hash = hash_val[r] - (l ? hash_val[l - 1] : 0);
        return hash * quick_pow(P, n - r - 1);
    };

    vec<uint> num_of_single_in_a;
    for (uint length_a = 1; length_a < n; length_a++) {
        uint temp = alpha_num[length_a - 1];
        num_of_single_in_a.push_back(0);
        while (temp) {
            if (temp & 1) {
                num_of_single_in_a.back()++;
            }
            temp >>= 1;
        }
    }

    vec<tuple<uint, uint>> queries;

    ull res = 0;

    for (uint length = 2; length < n; length++) {
        ull val = get_hash(0, length - 1);
        for (uint j = 0; j + length < n; j += length) {
            if (get_hash(j, j + length - 1) == val) {
                uint num_of_single_in_c = 0;
                uint temp = alpha_num.back() ^ alpha_num[j + length - 1];
                while (temp) {
                    if (temp & 1) {
                        num_of_single_in_c++;
                    }
                    temp >>= 1;
                }
                queries.emplace_back(num_of_single_in_c, length - 2);
            } else {
                break;
            }
        }
    }

    using std::get;

    std::sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) {
        return get<0>(a) == get<0>(b) ? get<1>(a) < get<1>(b) : get<0>(a) < get<0>(b);
    });

    const uint mxi = queries.size();
    uint lst_pos = 0;
    for (uint i = 0; i < mxi; i++) {
        while ((i + 1) < mxi && get<0>(queries[i + 1]) == get<0>(queries[i])) {
            i++;
        }
        uint cnt = i - lst_pos + 1;
        uint num_of_single_in_c = get<0>(queries[i]);
        for (uint j = 0; j < n - 2; j++) {
            while (lst_pos <= i && get<1>(queries[lst_pos]) < j) {
                lst_pos++;
                cnt--;
            }
            if (num_of_single_in_c >= num_of_single_in_a[j]) {
                res += cnt;
            }
        }
        lst_pos = i + 1;
    }

    return res;
}
