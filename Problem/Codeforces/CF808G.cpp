//
// Created by kibi on 24-8-15.
//
// havn't been submit in Luogu due to the RMJ service broke down
#include <cctype>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

class MyString {
	string str;
public:

	MyString(const uint &a) {
		a == 0 ? static_cast<void>(0) : str.push_back(static_cast<char>(a));
	}

	MyString operator * (uint) {
		return move(*this);
	}

	MyString operator + (const MyString &a) {
		str.append(a.str);
		return move(*this);
	}

	MyString operator - (const MyString &a) {
		return move(*this);
	}

	MyString operator * (const MyString &a) {
		return move(*this);
	}

	bool operator == (uint) const {
		return true;
	}

	string get() {
		return move(str);
	}

	const string& borrow() const {
		return str;
	}
};

bool isdigit(const MyString &a) {
	return islower(a.borrow()[0]) || a.borrow()[0] == '?';
}

template<typename T>
T read () {
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
	string s, t;
};

template<typename T>
class KMP {
	friend uint solve(const Config&);

	vector<T> pat;
	vector<uint> pi;

	void init() {
		for (uint i = 1; i < pi.size(); i++) {
			uint j = pi[i - 1];
			while (j != 0 && pat[j] != pat[i]) {
				j = pi[j - 1];
			}
			pi[i] = j + (pat[i] == pat[j]);
		}
	}

public:
	explicit KMP(vector<T> &pat) : pat(move(pat)), pi(this->pat.size()) {init();}
	explicit KMP(const vector<T> &pat) : pat(pat), pi(this->pat.size()) {init();}

	vector<uint> match(const vector<T> &txt) {
		vector<uint> res;
		uint j = 0;
		for (auto i = txt.begin(); i != txt.end(); ++i) {
			while (j != 0 && pat[j] != *i) {
				j = pi[j - 1];
			}
			pat[j] == *i ? ++j : j;
			j == pat.size() ? static_cast<void>(res.emplace_back(i - txt.begin()), j = pi[j - 1]) : static_cast<void>(0);
		}
		return res;
	}

};

uint solve(const Config&);

int main() {
	Config config{read<MyString>().get(), read<MyString>().get()};

	auto ans = solve(config);

	cout << ans << endl;
}

uint solve(const Config& config) {
	vector<uint> f(config.s.size()), g(config.s.size()); // f[i] res from 0 to i, g[i] res from 0 to i with a pattern at last
	vector<char> str(config.t.size());

	for (auto &i : str) {
		i = config.t[&i - &*str.begin()];
	}

	KMP<char> kmp(str);

	for (uint i = 0; i + config.t.size() - 1 < config.s.size(); i++) {
		bool flag = true;
		for (uint j = i; j < i + config.t.size(); j++) {
			if (config.s[j] != config.t[j - i] && config.s[j] != '?') {
				flag = false;
				break;
			}
		}
		f[i + config.t.size() - 1] = i + config.t.size() >= 2 ? f[i + config.t.size() - 2] : 0;
		if (flag) {
			g[i + config.t.size() - 1] = i ? f[i - 1] : 0;
			for (uint j = config.t.size(); j; j = kmp.pi[j - 1]) {
				g[i + config.t.size() - 1] = max(g[i + config.t.size() - 1], g[i + j - 1]);
			}
			kmp.pat.front() == kmp.pat.back() ? g[i + config.t.size() - 1] = max(g[i + config.t.size() - 1], g[i]) : 0;
			g[i + config.t.size() - 1]++;
			f[i + config.t.size() - 1] = max(f[i + config.t.size() - 1], g[i + config.t.size() - 1]);
		}
	}

	return f.back();
}