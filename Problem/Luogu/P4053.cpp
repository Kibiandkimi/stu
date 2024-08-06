//
// Created by kibi on 24-8-4.
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

using ull = unsigned long long;

class B {
public:
    ull w, limit;

    class PriorityCmp {
    public:
        bool operator () (const B &a, const B &b) {
            return a.w < b.w;
        }
    };

    B(ull w, ull limit):w(w), limit(limit){}
    B() = default;
};

class Config{
public:
    uint n;
    vector<B> buildings;
};

uint solve(Config &config);

int main(){
    auto n = read<uint>();

    Config config{n, vector<B>(n)};
    for(auto &i : config.buildings){
        i = {read<ull>(), read<ull>()};
    }

    auto ans = solve(config);
    printf("%u\n", ans);
}

uint solve(Config &config) {
    auto &b = config.buildings;

    sort(b.begin(), b.end(), [](const B &a, const B &b){return a.limit < b.limit;});

    ull time = 0;
    priority_queue<B, vector<B>, B::PriorityCmp> q;
    for(auto &i : b) {
        q.emplace(i);
        time += i.w;
        if(time > i.limit) {
            time -= q.top().w;
            q.pop();
        }
    }

    auto res = (uint)q.size();

    return res;
}