//
// Created by kibi on 24-8-21.
//
#include <cctype>
#include <cstdio>
#include <sys/types.h>
#include <vector>
using namespace std;

template <typename T>
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
	vector<uint> pos;
};

vector<uint> solve(const Config&);

int main() {
	auto n = read<uint>();

	Config config{vector<uint>(n)};
	for (auto &i : config.pos) {
		i = read<uint>();
	}

	auto ans = solve(config);
	for (auto &i : ans) {
		printf("%d\n", i);
	}

	return 0;
}

class BIT{
	uint n;
	vector<uint> value;
public:
	explicit BIT(uint n) : n(n), value(n + 1) {}

	void add(uint pos, uint val) {
		while (pos <= n) {
			value[pos] = max(value[pos], val);
			pos += pos & -pos;
		}
	}

	uint query(uint pos) const {
		uint res = 0;
		while (pos) {
			res = max(res, value[pos]);
			pos -= pos & -pos;
		}
		return res;
	}
};

vector<uint> solve(const Config &config) {
	vector<uint> res(config.pos.size());
	vector<uint> arr;

	for (uint i = 0; i < config.pos.size(); i++) {
		arr.insert(arr.begin() + config.pos[i], i + 1);
	}

	BIT bit(config.pos.size());
	for (auto i : arr) {
		res[i - 1] = bit.query(i) + 1;
		bit.add(i, res[i - 1]);
	}

	for (uint i = 1; i < config.pos.size(); i++) {
		res[i] = max(res[i], res[i - 1]);
	}

	return move(res);
}
