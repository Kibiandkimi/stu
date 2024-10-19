//
// Created by Kibi on 24-8-5.
//
#include <bits/stdc++.h>
using namespace std;

using uint = unsigned int;
using ull = unsigned long long;

template<typename T>
T read() {
    T s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    return s * w;
}

class Config {
public:
    uint n, k;
    vector<vector<uint>> arr;
};

ull solve(Config &config);

int main() {
    auto n = read<uint>(), k = read<uint>();

    Config config{n, k, vector<vector<uint>>(n)};
    for(auto &i : config.arr) {
        auto siz = read<uint>();
        i = vector<uint>(siz);
        for(auto &j : i) {
            j = read<uint>();
        }
    }

    auto ans = solve(config);
    printf("%llu\n", ans);
}

class Item {
public:
    uint siz;
    ull val;
};

class Bag{
public:
    vector<ull> f;
};

ull calc(Bag &bag, vector<Item>::iterator it, uint len, vector<vector<uint>>::iterator it2) {
    if(len == 1){
        ull res = bag.f.back();
        ull pre = 0;
        for(auto i = it2->begin(); i != it2->end() && i - it2->begin() < bag.f.size() - 1; ++i) {
            pre += *i;
            res = max(res, *(bag.f.end() - (i - it2->begin()) - 2) + pre);
        }
        return res;
    }
    uint mid_len = len / 2;
    Bag new_bag = bag;

    for(auto i = it; i - it < mid_len; ++i) {
        for(auto j = new_bag.f.end() - 1; j - new_bag.f.begin() >= i->siz; --j) {
            *j = max(*j, *(j - i->siz) + i->val);
        }
    }

    auto res1 = calc(new_bag, it + mid_len, len - mid_len, it2 + mid_len);

    new_bag = bag;

    for(auto i = it + mid_len; i - it < len; ++i) {
        for(auto j = new_bag.f.end() - 1; j - new_bag.f.begin() >= i->siz; --j) {
            *j = max(*j, *(j - i->siz) + i->val);
        }
    }

    auto res2 = calc(new_bag, it, mid_len, it2);

    return max(res1, res2);
}

ull solve(Config &config) {
    vector<Item> item(config.n);
    for(auto i = 0; i < config.n; ++i) {
        for(auto &j : config.arr[i]) {
            item[i].val += j;
        }
        item[i].siz = config.arr[i].size();
    }

    Bag bag{vector<ull>(config.k + 1)};

    return calc(bag, item.begin(), config.n, config.arr.begin());
}