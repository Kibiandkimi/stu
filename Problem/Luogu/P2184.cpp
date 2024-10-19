//
// Created by kibi on 24-8-25.
//
#include <cctype>
#include <cstdio>
#include <system_error>
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

class Opt{
public:
	uint q, l, r;
};

class Config {
public:
	uint n;
	vector<Opt> opts;
};

vector<uint> solve(const Config&);

int main() {
	auto n = read<uint>(), m = read<uint>();

	Config config{n, vector<Opt>(m)};
	for (auto &i : config.opts) {
		i = {read<uint>(), read<uint>(), read<uint>()};
	}

	auto ans = solve(config);
	for (auto &i : ans) {
		printf("%u\n", i);
	}

	return 0;
}

class BIT{
	vector<uint> value;
public:
	explicit BIT(const uint n) : value(n + 1) {}

	void add(uint pos, const uint val) {
		while(pos < value.size()) {
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

vector<uint> solve(const Config &config) {
	vector<uint> res;
	BIT bit_left(config.n), bit_right(config.n);

	res.reserve(config.opts.size());

	for (auto &i : config.opts) {
		switch (i.q) {
			case 1:
				bit_left.add(i.l, 1);
			bit_right.add(i.r, 1);
			break;
			case 2:
				res.push_back(bit_left.query(i.r) - bit_right.query(i.l - 1));
			break;
			default:
				throw runtime_error("Error operation code!");
		}
	}

	return move(res);
}
