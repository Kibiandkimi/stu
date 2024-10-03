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

    /*int seq[n / 2 + 1]; //seq[1],seq[2],...,seq[n] 为生成的序列
    int sum = 1e9;
    for(int i=1;i<n / 2;i++)
    {
        int R=sum/(n / 2-i+1)*2;
        seq[i] = rnd() % R; // 在 0 到 R 之间均匀随机选择一个整数作为 seq[i]
        sum-=seq[i];
    }
    seq[n / 2]=sum;

    for (uint i = 0; i < n / 2; i++) {
        config.arr[i] = seq[i + 1];
    }

    sum = 1e9;
    for(int i=1;i<n / 2;i++)
    {
        int R=sum/(n/2-i+1)*2;
        seq[i] = rnd() % R; // 在 0 到 R 之间均匀随机选择一个整数作为 seq[i]
        sum-=seq[i];
    }
    seq[n/2]=sum;

    for (uint i = n / 2; i < n; i++) {
        config.arr[i] = seq[i - n / 2 + 1];
    }*/
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

vector<uint> solve(const Config &config) {
    // a stupid trying

    vector<Node> temp(config.n);
    for (uint i = 0; i < config.n; ++i) {
        temp[i] = {i, config.arr[i]};
    }

    sort(temp.begin(), temp.end(), [](const Node &a, const Node &b) {return a.val < b.val;});

	uint cnt = 0;
	vector<uint> a(config.n / 2), b(config.n / 2);
	for_each(a.begin(), a.end(), [&cnt](auto &u){
		u = cnt++;
		cnt++;
	});
	cnt = 1;
	for_each(b.begin(), b.end(), [&cnt](auto &u){
		u = cnt++;
		cnt++;
	});

	uint now = 0;
	for (auto &i : a) {
		now += config.arr[i];
	}

    for (uint i = 0; i < config.n / 2; ++i) {
        for (uint j = 0; j < config.n / 2; ++j) {
            if (now + config.arr[b[j]] - config.arr[a[i]] == 1'000'000'000) {
                swap(a[i], b[j]);
                for_each(a.begin(), a.end(), [](auto &u){++u;});
                return a;
            }
        }
    }

	uint k = config.n / 2;

	while (now != 1'000'000'000) {
		uint l = rnd() % k, r = rnd() % k;
		swap(a[l], b[r]);
		now += config.arr[b[r]];
		now -= config.arr[a[l]];
	}

	for_each(a.begin(), a.end(), [](auto &u){++u;});
	return a;
}