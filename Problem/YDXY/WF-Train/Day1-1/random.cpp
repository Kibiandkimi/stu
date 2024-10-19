//
// Created by kibi on 24-10-3.
//
#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <map>
#include <random>
#include <set>
#include <sys/types.h>
#include <vector>
using namespace std;

using ull = unsigned long long;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(!isdigit(c)) {
		if (c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while(isdigit(c)) {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

class Config {
public:
    uint n;
    vector<uint> arr;
};

mt19937 rnd(random_device{}());

vector<uint> solve (const Config&);

int main() {
    freopen("random.in", "r", stdin);
    freopen("random.out", "w", stdout);

    auto n = read<uint>();
    Config config{n, vector<uint>(n)};

    for (auto &i : config.arr) {
        i = read<uint>();
    }
    auto ans = solve(config);
    printf("%lu ", ans.size());
    for (auto &i : ans) {
        printf("%u ", i);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

class Node {
public:
    uint id;
    uint val;
};

class Set {
public:
    vector<uint> id;
    uint sum{0};
};

vector<uint> solve(const Config &config) {
    vector<Node> nodes(config.n);
    uint cnt = 0;
    for_each(nodes.begin(), nodes.end(), [&](Node &u){u = {cnt, config.arr[cnt]}; cnt++;});
    shuffle(nodes.begin(), nodes.end(), rnd);

    while (true) {
        vector<Set> a, b;
        for (uint i = 0; i < 1000; i++) {
            Set now;
            for (uint j = 0; j < config.n / 2; j++) {
                if (rnd() & 1) {
                    now.id.push_back(nodes[j].id);
                    now.sum += nodes[j].val;
                }
            }
            a.push_back(now);
        }
        for (uint i = 0; i < 1000; i++) {
            Set now;
            for (uint j = config.n / 2; j < config.n; j++) {
                if (rnd() & 1) {
                    now.id.push_back(nodes[j].id);
                    now.sum += nodes[j].val;
                }
            }
            b.push_back(now);
        }

        for (auto &i : a) {
            for (auto &j : b) {
                if (i.sum + j.sum == 1'000'000'000) {
                    vector<uint> res;
                    for (auto &k : i.id) {
                        res.push_back(k + 1);
                    }
                    for (auto &k : j.id) {
                        res.push_back(k + 1);
                    }
                    return res;
                }
            }
        }
    }
}