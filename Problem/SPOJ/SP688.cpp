//
// Created by Kibi on 24-8-3.
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
    uint n, k, p;
    vector<uint> id;
};

uint solve(Config &config);

int main() {
    auto T = read<uint>();
    // int T = 1;
    while(T--) {
        auto n = read<uint>(), k = read<uint>(), p = read<uint>();
        Config config{n, k, p, vector<uint>(p)};

        for(auto &i : config.id) {
            i = read<uint>() - 1;
        }

        auto ans = solve(config);
        printf("%u\n", ans);
    }
}

class Id {
public:
    uint id, nxt;

    bool operator < (const Id &b) const {
        return nxt < b.nxt;
    }

    Id(uint id, uint nxt):id(id), nxt(nxt){}
};

uint solve(Config &config) {
    auto [n, k, p, _] = config;
    vector<uint> pre(n, p);
    vector<Id> ids(p, {0, p});

    for(uint i = 0; i < p; ++i) {
        ids[i].id = config.id[i];
    }

    for(uint i = 0; i < p; ++i) {
        ids[i].id = config.id[i];
        if(pre[ids[i].id] != p) {
            ids[pre[ids[i].id]].nxt = i;
        }
        pre[ids[i].id] = i;
    }

    uint res = 0;

    vector<bool> flag(n, false);
    priority_queue<Id> q;
    for(uint i = 0; i < p; ++i) {
        if(!flag[ids[i].id]){
            if(q.size() == k) {
                flag[q.top().id] = false;
                q.pop();
            }
            ++res;
            q.emplace(ids[i]);
            flag[ids[i].id] = true;
        }else {
            k++;
            q.emplace(ids[i]);
        }
    }

    return res;
}