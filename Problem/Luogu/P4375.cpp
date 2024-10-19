//
// Created by kibi on 24-8-26.
//
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

class BIT {
	vector<uint> value;
public:
	explicit BIT(const uint n) : value(n + 1) {}

	void update(uint pos, const uint val) {
		while (pos < value.size()) {
			value[pos] += val;
			pos += pos & -pos;
		}
	}

	uint query(uint pos) const {
		uint res = 0;
		while (pos) {
			res += value[pos];
			pos -= pos & -pos;
		}
		return res;
	}
};

class Node {
public:
	uint pos, val;
};

uint solve(const Config &config) {
	uint res = 0;
	vector<Node> arr(config.arr.size());
	for (auto &i : arr) {
		static uint k = 0;
		i.val = config.arr[k];
		i.pos = ++k;
	}

	stable_sort(arr.begin(), arr.end(), [](const auto &a, const auto &b){return a.val < b.val;});
	for	(auto &i : arr) {
		static uint k = 0;
		i.val = ++k;
	}

	sort(arr.begin(), arr.end(), [](const auto &a, const auto &b){return a.pos < b.pos;});

	BIT bit(arr.size());

	for (const auto &i : arr){
		bit.update(i.val, 1);
		res = max(res, i.pos - bit.query(i.pos));
	}

	return res == 0 ? 1 : res;
}
