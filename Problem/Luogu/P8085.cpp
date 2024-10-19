//
// Created by kibi on 24-8-14.
//
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <sys/types.h>
#include <vector>
using namespace std;

typedef unsigned long long ull;
mt19937_64 rnd(random_device{}());

class MyString {
	string s;
public:
	MyString(const uint a) {
		a != 0 ? s.push_back(static_cast<char>(a)) : void(0);
	}
	// MyString(MyString &other) {
	// 	this->s = move(other.s);
	// }

	MyString operator * (uint) {
		return *this;
	}

	MyString operator * (MyString) {
		return *this;
	}

	MyString operator - (uint) {
		return *this;
	}

	MyString operator + (const MyString &other) {
		s.append(other.s);
		return *this;
	}

	bool operator == (uint) const {
		return false;
	}

	const string& borrow () {
		return s;
	}

	string get() {
		return move(s);
	}
};

bool isdigit(MyString &s){
	return s.borrow()[0] >= 'a' && s.borrow()[0] <= 'z' || s.borrow()[0] == '$';
}

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
	vector<string> plain_text;
	vector<string> cipher_text;
};

uint solve (const Config&, ull);

int main () {
	Config config;
	auto s = read<MyString>();
	while (s.borrow()[0] != '$') {
		config.plain_text.emplace_back(s.get());
		s = read<MyString>();
	}
	s = read<MyString>();
	while (s.borrow()[0] != '$') {
		config.cipher_text.emplace_back(s.get());
		s = read<MyString>();
	}

	vector<decltype(solve(config, rnd()))> res(10);
	for(auto &i : res) {
		i = solve(config, rnd());
	}
	sort(res.begin(), res.end());

	auto ans = res.back();
	cout << ans;
}

uint solve (const Config &config, const ull BIG_NUM) {
	map<string, uint> pre;
	vector<uint> plain_text_pre(config.plain_text.size()),
				 plain_text_suc(config.plain_text.size(), config.plain_text.size()),
				 cipher_text_pre(config.cipher_text.size());
	for (uint i = 0; i < config.plain_text.size(); i++) {
		plain_text_pre[i] = pre[config.plain_text[i]];
		plain_text_pre[i] != 0 ? plain_text_suc[plain_text_pre[i] - 1] = i : i;
		pre[config.plain_text[i]] = i + 1;
	}
	for (uint i = 0; i < config.plain_text.size(); i++) {
		plain_text_pre[i] != 0 ? plain_text_pre[i] = i - plain_text_pre[i] + 1 : i;
	}
	pre.clear();
	for (uint i = 0; i < config.cipher_text.size(); i++) {
		cipher_text_pre[i] = pre[config.cipher_text[i]];
		pre[config.cipher_text[i]] = i + 1;
	}
	for (uint i = 0; i < config.cipher_text.size(); i++) {
		cipher_text_pre[i] != 0 ? cipher_text_pre[i] = i - cipher_text_pre[i] + 1 : i;
	}

	vector<ull> hash_base(config.plain_text.size());
	for (auto &i : hash_base) {
		i = rnd();
	}

	vector<ull> big_num(hash_base.size());
	big_num[0] = 1;
	for (uint i = 1; i < big_num.size(); i++) {
		big_num[i] = big_num[i - 1] * BIG_NUM;
	}

	auto &ptp = plain_text_pre, &pts = plain_text_suc, &ctp = cipher_text_pre;

	ull cipher_hash = 0;
	for(uint i = 0; i < config.cipher_text.size(); i++) {
		cipher_hash += hash_base[ctp[i]] * big_num[i];
	}

	ull plain_hash = 0;
	uint l = 0;
	for (uint i = 0; i < config.cipher_text.size(); i++) {
		plain_hash += hash_base[ptp[i]] * big_num[i];
	}

	while (cipher_hash != plain_hash) {
		assert(l + config.cipher_text.size() < config.plain_text.size());
		plain_hash -= hash_base[ptp[l]] * big_num[l];
		if (pts[l] < l + config.cipher_text.size()) {
			plain_hash -= hash_base[ptp[pts[l]]] * big_num[pts[l]];
			plain_hash += hash_base[0] * big_num[pts[l]];
		}
		pts[l] < config.plain_text.size() ? ptp[pts[l]] = 0 : 0;
		plain_hash += hash_base[ptp[l + config.cipher_text.size()]] * big_num[l + config.cipher_text.size()];
		l++;
		cipher_hash *= BIG_NUM;
	}

	return l + 1;
}