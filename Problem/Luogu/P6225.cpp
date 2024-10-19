//
// Created by kibi on 24-8-26.
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

class Opt {
public:
	enum OptType : bool{
		M,
		Q
	};
	OptType type;
	uint l, r;
};

class Config {
public:
	vector<uint> arr;
	vector<Opt> opts;
};

vector<uint> solve(const Config&);

int main() {
	auto n = read<uint>(), q = read<uint>();
	Config config{vector<uint>(n), vector<Opt>(q)};
	for (auto &i : config.arr) {
		i = read<uint>();
	}
	for (auto &i : config.opts) {
		i = {read<uint>() == 1 ? Opt::M : Opt::Q, read<uint>(), read<uint>()};
	}

	auto ans = solve(config);
	for (auto &i : ans) {
		printf("%u\n", i);
	}
}

class BIT {
	vector<uint> value;
public:
	explicit BIT(const uint n): value(n + 1){}

	void update(uint pos, const uint val) {
		while (pos < value.size()) {
			value[pos] ^= val;
			pos += pos & -pos;
		}
	}

	uint query(uint pos) {
		uint res = 0;
		while (pos) {
			res ^= value[pos];
			pos -= pos & -pos;
		}
		return res;
	}
};

vector<uint> solve(const Config &config) {
	vector<uint> res;
	vector<uint> arr = config.arr;
	BIT bit_odd(config.arr.size() / 2 + config.arr.size() % 2), bit_even(config.arr.size() / 2);

	for (auto &i : config.arr) {
		static uint k = 1;
		k & 1 ? bit_odd.update(k / 2 + 1, i) : bit_even.update(k / 2, i);
		k++;
	}

	for (auto &i : config.opts) {
		switch (i.type) {
			case Opt::M:
				i.l % 2 ? bit_odd.update(i.l / 2 + 1, i.r ^ arr[i.l - 1]) : bit_even.update(i.l / 2, i.r ^ arr[i.l - 1]);
				arr[i.l - 1] = i.r;
				break;
			case Opt::Q:
				if((i.l & 1) != (i.r & 1)) {
					res.emplace_back(0);
				}else if(i.l & 1){
					res.emplace_back(bit_odd.query(i.r / 2 + 1) ^ bit_odd.query(i.l / 2));
				}else {
					res.emplace_back(bit_even.query(i.r / 2) ^ bit_even.query(i.l / 2 - 1));
				}
		}
	}

	return move(res);
}
