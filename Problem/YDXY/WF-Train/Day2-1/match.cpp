//
// Created by kibi on 24-10-4.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <numeric>
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
    class Query {
    public:
        enum QueryType{
            modify = 1,
            query = 2,
        };

        QueryType type;
        uint x, y;
    };

    uint n, q;
    vector<uint> arr;
    vector<Query> queries;
};

vector<uint> solve(const Config&);

int main() {
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);

    auto n = read<uint>(), q = read<uint>();
    Config config{n, q, vector<uint>(n), vector<Config::Query>(q)};
    for_each(config.arr.begin(), config.arr.end(), [](auto &x){x = read<uint>();});
    for_each(config.queries.begin(), config.queries.end(), [](auto &x){
        x = Config::Query{
            read<uint>() == 1 ? Config::Query::modify : Config::Query::query,
            read<uint>(),
            read<uint>()
    };});
    auto ans = solve(config);
    for (auto &i : ans) {
        printf("%u\n", i);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

vector<uint> solve(const Config& config) {
    if (config.n <= 1'000 && config.q <= 1'000) {
        auto arr = config.arr;
        vector<uint> res;

        auto pow = [](uint a, uint p) {
            uint res = 1;
            while (p--) {
                res *= a;
            }
            return res;
        };

        auto calc = [&arr, pow] (uint l, uint k) {
            vector<uint> a(arr.begin() + l - 1, arr.begin() + l + pow(2, k) - 1), b(pow(2, k));
            while (k--) {
                for (uint i = 0; i < pow(2, k); i++) {
                    b[i] = a[i * 2] > a[i * 2 + 1] ? a[i * 2] - a[i * 2 + 1] : a[i * 2 + 1] - a[i * 2];
                }
                swap(a, b);
            }
            return a.front();
        };

        for (auto &i : config.queries) {
            switch (i.type) {
                case 1:
                    arr[i.x - 1] = i.y;
                break;
                case 2:
                    res.push_back(calc(i.x, i.y));
            }
        }
        return res;
    }
}