//
// Created by kibi on 24-8-26.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <vector>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(!isdigit(c)) {
		if(c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while('0' <= c && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

class Config {
public:
	vector<uint> arr;
};

uint solve(const Config&);

int main() {
	auto n = read<uint>();
	Config config{vector<uint>(n)};
	// all_of(config.arr.begin(), config.arr.end(), [n](uint &x){static uint i = n;
	// x = i--;
	// return true;});
	for (auto &i : config.arr) {
		i = read<uint>();
	}

	const auto ans = solve(config);
	printf("%d\n", ans);

	return 0;
}

uint solve(const Config &config) {
	uint res = 0;
	vector<uint> arr(config.arr.size());
	for (auto &i : arr) {
		static uint k = 0;
		i = k++;
	}

	stable_sort(arr.begin(), arr.end(), [&config](const auto &a, const auto &b){return config.arr[a] < config.arr[b];});

	for (const auto &i : arr){
		static uint k = 0;
		res = max(res, i > k ? i - k : 0);
		k++;
	}

	return res + 1;
}
