//
// Created by kibi on 24-8-28.
//
// TODO Problem.md:157
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <vector>
using namespace std;

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
	uint n, k, p;
};

uint solve(const Config&);

int main() {
	auto T = read<uint>();
	while (T--) {
		Config config{read<uint>(), read<uint>(), read<uint>()};
		auto ans = solve(config);
		printf("%u\n", ans);
	}
}

uint solve(const Config &config) {
	auto add = [&](auto &a, const auto &b) {
		a = a + b >= config.p ? a + b - config.p : a + b;
	};

	auto sub = [&](const auto &a, const auto &b) {
		return a * b % config.p;
	};

	auto dec = [&](const auto &a, const auto &b) {
		return a < b ? a + config.p - b : a - b;
	};

	if(config.k == 1) {
		return 1;
	}

	vector<vector<uint>> f(config.k * (config.n + 1) + 1, vector<uint>(config.k + 1));
	f[0][0] = 1;
	for(uint i = 1; i <= config.k * (config.n + 1); i++) {
		for (uint j = 1; j <= min(config.k, i); j++) {
			add(f[i][j], f[i - j][j - 1]);
			add(f[i][j], f[i - j][j]);
			if (i >= (config.n + 1) * 2) {
				f[i][j] = dec(f[i][j], f[i - (config.n + 1) * 2][j - 1]);
			}
		}
	}

	return f[(config.n + 1) * config.k][config.k];
}
