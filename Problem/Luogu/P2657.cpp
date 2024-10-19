//
// Created by kibi on 24-8-29.
//
#include <cctype>
#include <cmath>
#include <cstdio>
#include <stack>
#include <sys/types.h>
#include <tuple>
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
	uint l, r;
};

uint solve(const Config&);

int main() {
	Config config = {read<uint>(), read<uint>()};
	auto ans = solve(config);
	printf("%u\n", ans);
}

tuple<vector<vector<uint>>, vector<uint>> init() {
	vector<vector<uint>> res(10, vector<uint>(10));
	vector<uint> sum(10);
	for (uint j = 0; j < 10; j++) {
		res[0][j] = 1;
	}

	for (uint i = 1; i < 10; i++) {
		// res[i][0] = [i, &res] {
		// 	uint temp = 0;
		// 	for (auto &j : res[i - 1]) {
		// 		temp += j;
		// 	}
		// 	return temp;
		// }();
		for (uint j = 0; j < 10; j++) {
			for (uint k = 0; k < 10; k++) {
				if (abs(static_cast<int>(j) - static_cast<int>(k)) >= 2) {
					res[i][j] += res[i - 1][k];
				}
			}
		}
	}

	sum[0] = 1;
	for (uint i = 1; i < 10; i++) {
		sum[i] = sum[i - 1];
		for(uint j = 1; j < 10; j++) {
			sum[i] += res[i - 1][j];
		}
	}

	return {move(res), move(sum)};
}

uint calc(uint u) {
	static auto temp = init();
	static auto table = get<0>(temp);
	static auto sum = get<1>(temp);
	if (u == 0) {
		return 1;
	}
	stack<uint> stk;
	while (u) {
		stk.push(u % 10);
		u /= 10;
	}
	uint res = 0;
	res += sum[stk.size() - 1];
	for (uint i = 1; i < stk.top(); i++) {
		res += table[stk.size() - 1][i];
	}
	while (!stk.empty()) {
		u = stk.top();
		stk.pop();
		if(stk.empty()) {
			res++;
			break;
		}
		for (uint i = 0; i < stk.top(); i++) {
			if (abs(static_cast<int>(u) - static_cast<int>(i)) >= 2) {
				res += table[stk.size() - 1][i];
			}
		}
		if(abs(static_cast<int>(u) - static_cast<int>(stk.top())) < 2) {
			break;
		}
	}

	return res;
}

uint solve(const Config &config) {
	// for (uint i = 1; i <= 2000; i++) {
	// 	printf("%u: %u\n", i, calc(i) - calc(0));
	// }

	return calc(config.r) - calc(config.l - 1);
}