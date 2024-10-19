//
// Created by kibi on 24-8-11.
//
#include <cstdio>
#include <cctype>
#include <sys/types.h>
#include <vector>
#include <stdexcept>
using namespace std;

using ull = unsigned long long;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(!isdigit(c)) {
		if(c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while(isdigit(c)) {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return w * s;
}

class Config {
public:
	vector<bool> bits;
};

ull solve(Config &config);

int main() {
	// freopen("temp.in", "r", stdin);

	auto n = read<uint>();

	Config config{vector<bool>(n)};
	for(uint i = 0; i < n; ++i) {
		config.bits[i] = getchar() == '1';
	}

	// fclose(stdin);

	// throw runtime_error("?!");

	auto ans = solve(config);
	printf("%llu\n", ans);
}

enum Str{
	One,
	Zero,
	None,
};

bool operator == (const Str &a, const Str &b) {
	switch (a) {
		case One:
			switch (b) {
				case Zero:
					return true;
				default:
					return false;
			}
		case Zero:
			switch (b) {
				case One:
					return true;
				default:
					return false;
			}
		case None:
			switch (b) {
				case None:
					return true;
				default:
					return false;
			}
	}
}

template<typename T>
vector<int> manacher(const vector<T> &str, const T no_used) {
	vector<T> new_str(str.size() * 2 + 1, no_used);
	for(uint i = 0; i < str.size(); ++i) {
		new_str[i * 2 + 1] = str[i];
	}

	vector<int> res(new_str.size());
	int right = -1, left = 0;
	for (int i = 0; i < new_str.size(); i += 2) {
		int k = i > right ? 1 : min(res[left + right - i], right - i + 1);
		while(i >= k && i + k < new_str.size() && operator==(new_str[i - k], new_str[i + k])) {
			++k;
		}
		res[i] = k--;
		if(i + k > right) {
			right = i + k;
			left = i - k;
		}
	}

	return res;
}

ull solve(Config &config){
	vector<Str> strs(config.bits.size());
	for(uint i = 0; i < strs.size(); ++i) {
		strs[i] = config.bits[i] ? One : Zero;
	}
	ull ans = 0;
	auto res = manacher(strs, None);
	for(uint i = 0; i < res.size(); i += 2) {
		ans += (res[i] - 1) / 2;
	}
	return ans;
}