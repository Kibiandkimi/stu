//
// Created by Kibi on 24-10-16.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using uint = unsigned int;

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

class OptA {
public:
    uint x, y, c;
};

class OptB {
public:
    uint x1, x2, y1, y2, c;
};

union Opt {
    OptA a;
    OptB b;
};

enum class OptType {
    OptA = 1,
    OptB = 2,
};
//
// using Opt = tuple<>

class Config {
public:
    uint n, m;
    vector<vector<uint>> matrix;
    vector<tuple<OptType, Opt>> opts;
};

vector<uint> solve(const Config&);

int main() {
    auto n = read<uint>(), m = read<uint>();
    decltype(declval<Config>().matrix) matrix(n, vector<uint>(m));
    for (auto &i : matrix) {
        for (auto &j : i) {
            j = read<uint>();
        }
    }
    auto q = read<uint>();
    Config config{n, m, move(matrix), decltype(declval<Config>().opts)(q)};
    for (auto &i : config.opts) {
        auto type = read<uint>();
        type == 1 ? i = {OptType::OptA, {.a = {read<uint>(), read<uint>(), read<uint>()}}} : i = {OptType::OptB, {.b = {read<uint>(), read<uint>(), read<uint>(), read<uint>(), read<uint>()}}};
    }
    auto ans = solve(config);
    for (auto &i : ans) {
        printf("%u\n", i);
    }
    return 0;
}

template<typename Data>
class BIT {
    vector<Data> data;
    size_t n;
public:
    explicit BIT(const size_t n) : data(n + 1), n(n) {}
    BIT(const size_t n, Data data) : data(n + 1, data), n(n) {}

    template<typename T>
    void modify(size_t pos, T val) {
        if (pos == 0) {
            return;
        }
        while (pos <= n) {
            Data::modify(data[pos], val);
            pos += (pos & -pos);
        }
    }

    template<typename T, typename S>
    T query(size_t pos, S information) const {
        T res{};
        while (pos) {
            Data::merge(res, data[pos], information);
            pos -= (pos & -pos);
        }
        return res;
    }
};

class Temp{};

class MyInt {
    int val;

public:
    MyInt() : val(0) {}

    static void modify(MyInt &a, const int &val) {
        a.val += val;
    }

    static void merge(int &a, const MyInt &b, Temp &temp) {
        a += b.val;
    }

    uint get() const {
        return val;
    }
};

class MyBIT {
    BIT<MyInt> bit;

public:
    using Modifier = tuple<uint, int>; // l, r, val
    using Inform = tuple<uint, uint>; // l, r

    explicit MyBIT(const size_t n) : bit(n) {}

    static void modify(MyBIT &a, const Modifier &b) {
        auto &[pos, val] = b;
        a.bit.modify(pos, val);
        // a.bit.modify(r + 1, -val);
    }

    static void merge(int &a, const MyBIT &b, const Inform &information) {
        auto &[l, r] = information;
        a += b.bit.query<int, Temp>(r, {});
        a -= b.bit.query<int, Temp>(l - 1, {});
    }
};

vector<uint> solve(const Config &config) {
    vector<BIT<MyBIT>> bits(100, {config.n, MyBIT{config.m}});
    for (uint i = 0; i < config.n; i++) {
        for (uint j = 0; j < config.m; j++) {
            bits[config.matrix[i][j] - 1].modify<MyBIT::Modifier>(i + 1, {j + 1, 1});
        }
    }

    auto matrix = config.matrix;

    vector<uint> ret;

    for (auto &i : config.opts) {
        switch (get<0>(i)) {
            case OptType::OptA: {
                auto opt = get<1>(i).a;
                bits[matrix[opt.x - 1][opt.y - 1] - 1].modify<MyBIT::Modifier>(opt.x, {opt.y, -1});
                bits[opt.c - 1].modify<MyBIT::Modifier>(opt.x, {opt.y, 1});
                matrix[opt.x - 1][opt.y - 1] = opt.c;
                break;
            }
            case OptType::OptB: {
                auto opt = get<1>(i).b;
                auto res = bits[opt.c - 1].query<int, MyBIT::Inform>(opt.x2, {opt.y1, opt.y2});
                res -= bits[opt.c - 1].query<int, MyBIT::Inform>(opt.x1 - 1, {opt.y1, opt.y2});
                ret.push_back(res);
            }
        }
    }

    return ret;
}
