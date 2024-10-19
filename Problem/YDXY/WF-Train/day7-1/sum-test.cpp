//
// Created by kibi on 24-10-9.
//
//
// Created by kibi on 24-10-9.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <numeric>
#include <random>
#include <sys/types.h>
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
    uint n;
    vector<int> arr;
};

ull solve(const Config&);
ull bomb(const Config&);

Config gen();

int main() {
    freopen("temp.in", "r", stdin);
    freopen("temp.out", "w", stdout);

    // auto n = read<uint>();
    // Config config{n, vector<int>(n)};
    // for (auto &i : config.arr) {
    //     i = read<int>();
    // }

    while (true) {
        Config config = gen();

        ull my_ans = solve(config);
        ull bomb_ans = bomb(config);

        if (my_ans != bomb_ans) {
            printf("Wrong answer\nYour: %llu, Bomb:%llu\n", my_ans, bomb_ans);
            for (auto &i : config.arr) {
                printf("%llu\n", i);
            }
            return 0;
        }

        if (my_ans != 0)
        printf("Correct answer\nN: %u, Answer: %llu\n", config.n, my_ans);

        // printf("%llu\n", ans);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

mt19937 rnd(random_device{}());

Config gen() {
    const unsigned long rng = 10;
    uint n = 100;
    Config config{n, vector<int>(n)};
    for (auto &i : config.arr) {
        i = rnd() % rng;
        i = (rnd() & 1 ? -i : i);
    }
    return config;
}

ull solve(const Config& config) {

    auto b = config.arr;

    sort(b.begin(), b.end());

    uint n = b.size();

    // get mxi
    uint mxi = n;
    for (uint i = 0; i < n; i++) {
        if (b[i] > 0) {
            mxi = i;
            break;
        }
    }

    ull res = 0;
    for (uint i = 0; i < mxi; i++) {
        // for (uint j = i + 1; j < mxi; j++) {
        //
        // }

        // stupid solution, complex
        auto it = lower_bound(b.begin() + mxi - 1, b.end(), (-b[i]) / 2 + 1);
        auto it2 = it - 1;

        if (*it + *it2 + b[i] > 0) {
            --it;
            --it2;
        }
        if (*it * 2 + b[i] == 0) {
            uint num = 0;
            for (auto j = it; j < b.end() && *j == *it; ++j) {
                num++;
            }
            it = it + num;
            for (auto j = it - 1 - num; j > b.begin() + i && *j == *(it - 1); --j) {
                num++;
            }
            it2 = it - num - 1;
            res += num * (num - 1) / 2;
        }
        while (it2 > b.begin() + i && it < b.end()) {
            if (*it + *it2 + b[i] == 0) {
                uint num1 = 0, num2 = 0, val1 = *it, val2 = *it2;
                while (it < b.end() && *it == val1) {
                    num1++;
                    ++it;
                }
                while (it2 > b.begin() + i && *it2 == val2) {
                    num2++;
                    --it2;
                }
                res += num1 * num2;
                // --it2;
                // ++it;
            } else {
                if (*it + *it2 + b[i] > 0) {
                    --it2;
                } else{
                    ++it;
                }
            }
        }
    }
    return res;
}

ull bomb(const Config& config) {
    ull res = 0;
    for (uint i = 0; i < config.arr.size(); i++) {
        for (uint j = i + 1; j < config.arr.size(); j++) {
            for (uint k = j + 1; k < config.arr.size(); k++) {
                if (config.arr[i] + config.arr[j] + config.arr[k] == 0) {
                    res++;
                }
            }
        }
    }
    return res;
}