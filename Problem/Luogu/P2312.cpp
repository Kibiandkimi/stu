//
// Created by kibi on 24-8-10.
//
#include <cstdio>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

using uint = unsigned int;
constexpr int MOD = 1000000007;

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
		s = (s * 10 + c - '0') % MOD;
		c = getchar();
	}
	return w * s;
}

class Config {
public:
	uint m;
	vector<int> a;
};

int calc(const Config &config, const uint x) {
	int res = 0;
	for(auto &i : config.a) {
		res = (res + i) % MOD;
		res = static_cast<int>(static_cast<long long>(res) * x % MOD);
	}
	return res;
}

vector<uint> solve(Config &config) {
	reverse(config.a.begin(), config.a.end());
	int temp = config.a.back();
	config.a.pop_back();

	vector<uint> res;
	for(uint i = 1; i <= config.m; ++i) {
		if(calc(config, i) + temp == 0) {
			res.push_back(i);
		}
	}

	return res;
}

int main() {
	const auto n = read<uint>(), m = read<uint>();

	Config config{m, vector<int>(n + 1)};
	for(auto &i : config.a) {
		i = static_cast<int>(read<long long>());
	}

	auto res = solve(config);
	printf("%lu\n", res.size());
	for(auto &i : res) {
		printf("%u\n", i);
	}
}