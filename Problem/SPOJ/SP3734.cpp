//
// Created by kibi on 24-8-22.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <vector>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while (!isdigit(c)) {
		if(c == '-') {
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
	uint k;
	vector<uint> height;
};

uint solve(const Config&);

int main() {
	auto n = read<uint>(), k = read<uint>();
	Config config{k, vector<uint>(n)};
	for (auto &i : config.height) {
		i = read<uint>();
	}

	auto ans = solve(config);
	printf("%u\n", ans);

	return 0;
}

uint solve(const Config &config) {
	// TODO
}