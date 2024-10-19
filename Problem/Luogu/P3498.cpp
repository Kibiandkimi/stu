//
// Created by kibi on 24-8-12.
//
#include <algorithm>
#include <bits/unique_ptr.h>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <random>
#include <set>
#include <sys/types.h>
#include <vector>

using namespace std;
using ret = tuple<uint, uint, vector<uint>>;
using ull = unsigned long long;
mt19937_64 rnd(random_device{}());

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
	vector<uint> str;
};

unique_ptr<ret> solve(const Config &config, const ull BIG_NUM);

int main() {
	const auto n = read<uint>();

	Config config{vector<uint>(n)};
	for (auto &str : config.str) {
		str = read<uint>();
	}

	auto ans1 = solve(config, rnd());
	auto ans2 = solve(config, rnd());

	const uint T = 10;
	vector<decltype(solve(config, rnd()))> ans(T);
	for (auto &i : ans) {
		i = solve(config, rnd());
	}

	sort(ans.begin(), ans.end(), [](const auto &a, const auto &b) {return get<0>(*a) > get<0>(*b);});

	cout << get<0>(*ans[0]) << " " << get<1>(*ans[0]) << "\n";
	for(auto &i : get<2>(*ans[0])) {
		cout << i << "\n";
	}

	return 0;
}


unique_ptr<ret> solve(const Config &config, const ull BIG_NUM) {
	vector<ull> str_hash(config.str.size());
	for (auto &hash : str_hash) {
		hash = rnd();
	}

	vector<ull> big_num(config.str.size());
	big_num[0] = 1;
	for(uint i = 1; i < config.str.size(); i++) {
		big_num[i] = big_num[i - 1] * BIG_NUM;
	}

	vector<ull> sum1(config.str.size()), sum2(config.str.size());
	sum1[0] = str_hash[config.str[0] - 1];
	for (uint i = 1; i < config.str.size(); i++) {
		sum1[i] = sum1[i - 1] + str_hash[config.str[i] - 1] * big_num[i];
	}
	sum2[0] = str_hash[config.str.back() - 1];
	for (uint i = 1; i < config.str.size(); i++) {
		sum2[i] = sum2[i - 1] + str_hash[config.str[config.str.size() - i - 1] - 1] * big_num[i];
	}
	reverse(sum2.begin(), sum2.end());

	uint mx = 0;
	vector<uint> res(config.str.size());
	for(uint k = 1; k <= config.str.size(); k++) {
		set<ull> st;
		for (uint i = 0; i + k - 1 < config.str.size(); i += k) {
			// range from i to (i + k - 1)
			ull temp1 = (sum1[i + k - 1] - (i == 0 ? 0 : sum1[i - 1])) * big_num[config.str.size() - i - k],
				temp2 = (sum2[i] - (i + k == config.str.size() ? 0 : sum2[i + k])) * big_num[i];
			st.insert(temp1 > temp2 ? temp2 : temp1);
		}
		res[k - 1] = static_cast<uint>(st.size());
		mx = max(mx, static_cast<uint>(st.size()));
	}

	vector<uint> ans;
	for(auto &i : res) {
		if(i == mx) {
			ans.emplace_back(&i - &*res.begin() + 1);
		}
	}

	return make_unique<ret>(mx, static_cast<uint>(ans.size()), ans);
}