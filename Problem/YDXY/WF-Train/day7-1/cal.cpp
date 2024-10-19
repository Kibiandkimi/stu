//
// Created by kibi on 24-10-9.
//
#include <cctype>
#include <cstdio>
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
    ull n;
};

ull solve(const Config&);

int main() {
    freopen("cal.in", "r", stdin);
    freopen("cal.out", "w", stdout);

    auto n = read<ull>();
    auto ans = solve({n});
    printf("%llu\n", ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ull solve(const Config& config) {
    vector<uint> arr;
    auto n = config.n;
    while (n) {
        arr.push_back(n % 10);
        n /= 10;
    }
    ull res = 0;
    const uint mxi = 1 << arr.size();
    vector<bool> flag(arr.size());
    for (uint i = 0; i < mxi; i++) {
        uint temp = i;
        bool pre = false, ava = true;
        for (uint j = 0; j < arr.size(); j++) {
            flag[j] = temp & 1;
            temp >>= 1;
            if (flag[j] && (pre || arr[j] != 1 || j == 0 || arr[j - 1] == 9)) {
                ava = false;
                break;
            }
            pre = flag[j];
        }
        if (!ava) {
            continue;
        }
        ull temp_res = 1;
        for (uint j = 0; j < arr.size(); j++) {
            if (j != arr.size() - 1 && flag[j + 1]) {
                continue;
            }
            if (flag[j]) {
                uint temp = 18 - (10 + arr[j - 1]) + 1;
                temp_res *= temp/* / 2 + temp % 2*/;
            } else {
                uint temp = arr[j] + 1;
                temp_res *= temp/* / 2 + temp % 2*/;
            }
        }
        res += temp_res;
    }
    return res;
}

