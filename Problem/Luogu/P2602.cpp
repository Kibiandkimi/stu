//
// Created by kibi on 24-9-6.
//
#include <cctype>
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

using ull = unsigned long long;

class Config {
public:
	ull l, r;
};

vector<ull> solve(const Config&);

int main() {
	const auto l = read<ull>(), r = read<ull>();
	const Config config{l, r};
	const auto ans = solve(config);
	for (const auto &i : ans) {
		printf("%llu ", i);
	}
	return 0;
}

vector<ull> operator + (const vector<ull>& a, const vector<ull>& b) {
    vector<ull> ans;
    for (auto i = a.begin(), j = b.begin(); i != a.end() && j != b.end(); ++i, ++j) {
        ans.push_back(*i + *j);
    }
    return move(ans);
}

ull pow(const ull base, ull p) {
    ull res = 1;
    while (p) {
        res *= base;
        p--;
    }
    return res;
}

tuple<vector<vector<vector<ull>>>, vector<vector<ull>>> init() {
	vector<vector<vector<ull>>> res(12, vector<vector<ull>>(10, vector<ull>(10)));
	vector<vector<ull>> sum(12, vector<ull>(10));
	  res[0][0][0] = res[0][1][1] = res[0][2][2] = res[0][3][3] = res[0][4][4]
	= res[0][5][5] = res[0][6][6] = res[0][7][7] = res[0][8][8] = res[0][9][9] = 1;
	sum[0] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    for (uint i = 1; i < 12; i++) {
        for (uint j = 0; j < 10; j++) {
            res[i][0] = res[i][0] + res[i - 1][j];
        }
        sum[i] = sum[i - 1];
        for (uint j = 1; j < 10; j++) {
            res[i][j] = res[i][0];
            res[i][j][j] += pow(10, i);
            sum[i] = sum[i] + res[i][j];
        }
        res[i][0][0] += pow(10, i);
    }
    return {move(res), move(sum)};
}

vector<ull> calc(ull u) {
	static auto temp = init();
	static auto table = move(get<0>(temp));
	static auto sum = move(get<1>(temp));
	if (u == 1'000'000'000'000ull) {
	    return sum[11];
	}

	if (u == 0) {
	    return {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	}

    auto res = vector<ull>(10);

    if (u < 10) {
        res[0]++;
    }

    ull temp2 = 1;

	stack<uint> stk;
	while (u) {
	    stk.push(u % 10);
	    res[stk.top()] += temp2;
	    temp2 += stk.top() * pow(10, stk.size() - 1);
	    u /= 10;
	}

    res = stk.size() > 1 ? res + sum[stk.size() - 2] : move(res);
    for (uint j = 1; j < stk.top(); j++) {
        res = res + table[stk.size() - 1][j];
    }
    stk.pop();
    while (!stk.empty()) {
        for (uint j = 0; j < stk.top(); j++) {
            res = res + table[stk.size() - 1][j];
        }
        stk.pop();
    }

    return move(res);

}

vector<ull> operator - (const vector<ull>& u, const vector<ull>& v) {
	vector<ull> ans;
	for (auto i = u.begin(), j = v.begin(); i != u.end() && j != u.end(); ++i, ++j) {
		ans.push_back(*i - *j);
	}
	return ans;
}

vector<ull> solve(const Config &config) {
    // for (uint i = 1; i <= 1000; i++) {
    //     auto res = calc(i);
    //     res[0]--;
    //     for (auto &j : res) {
    //         printf("%llu ", j);
    //     }
    //     printf("\n");
    // }

	return calc(config.r) - calc(config.l - 1);
}
