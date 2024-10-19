//
// Created by kibi on 24-8-14.
//
#include <algorithm>
#include <bits/unique_ptr.h>
#include <cassert>
#include <cstdio>
#include <cctype>
#include <random>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <vector>
using namespace std;

class MyString {
	/*
	* a string class adapt to read<T>()
	* with unique_ptr
	* */

	unique_ptr<string> s;
	explicit MyString(unique_ptr<string> s):s(move(s)){}
public:
	MyString() : s(make_unique<string>()) {}
	MyString(const uint n){
		s = make_unique<string>();
		n == 0 ? static_cast<void>(0) : s->push_back(static_cast<char>(n));
	}

	MyString operator * (const uint &n) {
		// n == 10 ? s->push_back(' ') : static_cast<void>(0);
		return MyString(move(s));
	}

	MyString operator * (const MyString &n) {
		return MyString(move(s));
	}

	MyString operator + (const uint &n) {
		s->push_back(static_cast<char>(n + '0'));
		return MyString(move(s));
	}

	MyString operator + (const MyString &n) {
		s->push_back(n.s->back());
		return MyString(move(s));
	}

	MyString operator - (const uint &n) {
		return MyString(move(s));
	}

	bool operator == (uint _) const {
		return false;
	}

	unique_ptr<string> get() {
		return move(s);
	}

	const string& borrow() const {
		return *s;
	}
};

bool isdigit(const MyString& temp) {
	return isalpha(temp.borrow()[0]) || isdigit(temp.borrow()[0]) || temp.borrow()[0] == '_' || temp.borrow()[0] == '@';
}

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
	const uint L, S;
	vector<string> names;
};

typedef unsigned long long ull;

mt19937_64 rnd(random_device{}());

uint solve(const Config&, ull);

int main () {
	const auto n = read<uint>(), L = read<uint>(), S = read<uint>();

	Config config{L, S, vector<string>(n)};
	for (auto &i : config.names) {
		i = move(*read<MyString>().get());
	}

	vector<uint> res(5);
	for (auto &i : res){
		i = solve(config, rnd());
	}
	sort(res.begin(), res.end());

	const auto ans = res.front();
	cout << ans;
	return 0;
}

uint map(uint c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	if ('a' <= c && c <= 'z') {
		return c - 'a' + 10;
	}
	if ('A' <= c && c <= 'Z') {
		return c - 'A' + '9' - '0' + 1 + 'z' - 'a' + 1;
	}
	if (c == '_') {
		return 62;
	}
	if (c == '@') {
		return 63;
	}
	throw invalid_argument("Invalid character!");
}

uint solve(const Config &config, const ull BIG_NUM) {
	vector<ull> hash_base(64);
	for (auto &i : hash_base) {
		i = rnd();
	}

	vector<ull> big_num(config.L);
	big_num[0] = BIG_NUM;
	for (uint i = 1; i < config.L; i++) {
		big_num[i] = big_num[i - 1] * BIG_NUM;
	}

	vector<ull> hash(config.names.size());
	for (uint i = 0; i < config.names.size(); i++) {
		for (uint j = 0; j < config.L; j++) {
			hash[i] += hash_base[map(config.names[i][j])] * big_num[j];
		}
	}

	uint res = 0;
	for (uint j = 0; j < config.L; j++) {
		vector<ull> new_hash(hash);
		for (uint i = 0; i < config.names.size(); i++) {
			new_hash[i] -= hash_base[map(config.names[i][j])] * big_num[j];
		}
		sort(new_hash.begin(), new_hash.end());
		ull lst = new_hash[0] + 1;
		uint num = 0;
		for (const auto &i : new_hash) {
			if (i != lst) {
				res += num * (num - 1) / 2;
				lst = i;
				num = 0;
			}
			num++;
		}
		res += num * (num - 1) / 2;
	}

	return res;
}