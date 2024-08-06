//
// Created by Kibi on 24-8-2.
//
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read(){
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
    uint n, m;
    vector<long long> u;
};

long long run(Config &config);

int main(){
    auto n = read<uint>(), m = read<uint>();

    Config config{n, m, vector<long long>(n)};
    for(auto &i : config.u) {
        i = read<int>() * 2;
    }
    for(int i = 0; i < m; ++i) {
        auto u = read<uint>() - 1, v = read<uint>() - 1;
        auto w = read<int>();
        config.u[u] += w;
        config.u[v] += w;
    }

    auto ans = run(config) / 2;

    printf("%lld\n", ans);
}

long long run(Config &config) {
    sort(config.u.begin(), config.u.end(), greater<>());

    long long res = 0, flag = 1;
    for(auto &i : config.u) {
        res = res + flag * i;
        flag = -flag;
    }

    return res;
}

