//
// Created by kibi on 24-10-3.
//
#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <random>
#include <sys/types.h>
#include <tuple>
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
    uint n, m;
    vector<tuple<uint, uint>> edges;
};

uint solve (const Config&);

int main() {
    freopen("npc.in", "r", stdin);
    freopen("npc.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    Config config{n, m, vector<tuple<uint, uint>>(m)};


    for (auto &i : config.edges) {
        i = { read<uint>() - 1, read<uint>() - 1};
    }

    printf("%u\n", solve(config));

    fclose(stdin);
    fclose(stdout);
    return 0;
}

uint solve(const Config &config) {
    if (config.n == 1) {
        return 1;
    }
    if (config.n == 2) {
        return 2 + config.m;
    }
    if (config.n == 3) {
        return 3 + config.m + (config.m == 3);
    }

    if (config.n <= 18) {
        auto pow = [](uint a, uint p) {
            uint res = 1;
            while (p--) {
                res *= a;
            }
            return res;
        };

        vector<vector<bool>> edge(config.n, vector<bool>(config.n));
        for (auto &i : config.edges) {
            edge[get<0>(i)][get<1>(i)] = true;
            edge[get<1>(i)][get<0>(i)] = true;
        }

        for (uint i = 0; i < config.n; i++) {
            edge[i][i] = true;
        }

        vector<uint> list(config.n);
        uint res = 0;
        for (uint i = 1, mxi = pow(2, config.n); i < mxi; i++) {
            uint temp = i << 1, cnt = -1, num = 0;
            bool flag = true;
            while (temp && flag) {
                cnt++;
                temp >>= 1;
                if (temp & 1) {
                    for (uint j = 0; j < num; j++) {
                        if (!edge[cnt][list[j]]) {
                            flag = false;
                            break;
                        }
                    }
                    list[num] = cnt;
                    num++;
                }
            }
            res += flag;
        }
        return res;
    }

    if (config.m <= 100) {
        vector<vector<uint>> graph(config.n);
        vector<vector<bool>> edge(config.n, vector<bool>(config.n));
        vector<uint> w(config.n);
        for (auto &i : config.edges) {
            edge[get<0>(i)][get<1>(i)] = true;
            edge[get<1>(i)][get<0>(i)] = true;
            w[get<0>(i)]++;
            w[get<1>(i)]++;
        }

        auto pow = [](uint a, uint p) {
            uint res = 1;
            while (p--) {
                res *= a;
            }
            return res;
        };


        for (uint i = 0; i < config.n; i++) {
            edge[i][i] = true;
        }

        vector<uint> id(config.n);
        uint cnt = 0;
        for_each(id.begin(), id.end(), [&cnt](uint &i) {i = cnt++;});
        sort(id.begin(), id.end(), [&w](uint a, uint b) {return w[a] < w[b];});

        vector<bool> vis(config.n);

        vector<uint> list(config.n);

        uint res = 0;

        for (uint i = 0; i < config.n; i++) {
            vis[id[i]] = true;
            for (uint j = 0; j < config.n; j++) {
                if (!vis[j] && edge[id[i]][j]) {
                    graph[id[i]].push_back(j);
                }
            }
            for (uint j = 0, mxj = pow(2, graph[id[i]].size()); j < mxj; j++) {
                uint temp = j << 1, cnt = -1, num = 0;
                bool flag = true;
                while (temp && flag) {
                    cnt++;
                    temp >>= 1;
                    if (temp & 1) {
                        for (uint k = 0; k < num; k++) {
                            if (!edge[graph[id[i]][cnt]][list[k]]) {
                                flag = false;
                                break;
                            }
                        }
                        list[num++] = cnt;
                    }
                }
                res += flag;
            }
        }

        return res;
    }
}