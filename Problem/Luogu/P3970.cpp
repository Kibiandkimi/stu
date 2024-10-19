//
// Created by kibi on 24-8-27.
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
	vector<int> arr;
};

uint solve(const Config&);

int main() {
	auto n = read<uint>();
	Config config{vector<int>(n)};
	for (auto &i : config.arr) {
		i = read<int>();
	}

	const auto ans = solve(config);
	printf("%u\n", ans);
}

// constexpr uint MOD = 1000000007;

template<typename T>
void add(T &a, const T b) {
	a = a + b >= 1000000007 ? a + b - 1000000007 : a + b;
}

template<typename T>
T dec(const T a, const T b) {
	return a < b ? 1000000007 + a - b : a - b;
}

class BIT {
	vector<uint> value;
public:
	explicit BIT(const uint n) : value(n + 1) {}

	void update(uint pos, const uint val) {
		while (pos < value.size()) {
			add(value[pos], val);
			pos += pos & -pos;
		}
	}

	uint query(uint pos) const {
		uint res = 0;
		while (pos) {
			add(res, value[pos]);
			pos -= pos & -pos;
		}
		return res;
	}
};

class Node {
public:
	uint pos;
	int val;
};

uint solve(const Config &config) {

	// de-emphasize
	vector<Node> nodes;
	nodes.reserve(config.arr.size());

	for (auto &i : config.arr) {
		static uint k = 0;
		nodes.push_back({k++, i});
	}

	sort(nodes.begin(), nodes.end(), [](const auto &a, const auto &b) {return a.val < b.val;});

	for (auto &i : nodes) {
		static int lst = 1000000007, now = 0;
		if (i.val != lst) {
			++now;
		}
		lst = i.val;
		i.val = now;
	}

	vector<uint> lst_ans(nodes.back().val + 1, -1);
	vector<uint> dp(nodes.size());
	BIT bit(nodes.back().val);

	sort(nodes.begin(), nodes.end(), [](const auto &a, const auto &b) {return a.pos < b.pos;});

	for (const auto &i : nodes) {
		const uint temp = bit.query(i.val - 1);
		lst_ans[i.val] == -1 ? bit.update(i.val, temp + 1 + (lst_ans[i.val] = 0)) :
							   bit.update(i.val, dec(temp, lst_ans[i.val]));
		dp[i.pos] = dec(temp, lst_ans[i.val]);
		lst_ans[i.val] = temp;
	}

	uint res = 0;
	for (const auto &i : dp) {
		add(res, i);
	}
	return res;
}
