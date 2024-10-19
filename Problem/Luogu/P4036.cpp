//
// Created by kibi on 24-8-20.
//
// TODO
#include <cassert>
#include <cctype>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <system_error>
#include <vector>
using namespace std;

class MyString{
	string str;
public:
	MyString(const uint &a){
		a == 0 ? static_cast<void>(0) : str.push_back(static_cast<char>(a));
	}

	bool operator == (uint) const {
		return false;
	}

	MyString operator * (uint) {
		return move(*this);
	}

	MyString operator + (MyString &x) {
		str.append(x.str);
		return move(*this);
	}

	MyString operator - (uint) {
		return move(*this);
	}

	MyString operator * (MyString&) {
		return move(*this);
	}

	string get() {
		return move(str);
	}

	const string& borrow() const {
		return str;
	}
};

bool isdigit(const MyString &str) {
	return islower(str.borrow()[0]) || str.borrow()[0] == 'Q' || str.borrow()[0] == 'R' || str.borrow()[0] == 'I';
}

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
	return s * w;
}

class Opt{
public:
	enum OptType {
		Q,
		R,
		I,
	};
	OptType type;
	uint x, y;
};

class Config{
public:
	uint m;
	string str;
	vector<Opt> opt;
};

vector<uint> solve(const Config&);

int main() {
	string str = read<MyString>().get();
	auto m = read<uint>();

	Config config{m, move(str), vector<Opt>(m)};
	for (auto &i : config.opt) {
		const uint type = read<MyString>().get()[0];
		const auto x = read<uint>();
		switch (type) {
			case 'Q':
				i = {Opt::Q, x, read<uint>()};
				break;
			case 'R':
				i = {Opt::R, x, static_cast<uint>(read<MyString>().get()[0])};
				break;
			case 'I':
				i = {Opt::I, x, static_cast<uint>(read<MyString>().get()[0])};
				break;
			default:
				throw runtime_error("Unexpected operation!");
		}
	}

	auto ans = solve(config);
	for (auto &i : ans) {
		printf("%u\n", i);
	}

	return 0;
}

vector<uint> solve(const Config &config) {
	vector<uint> res;
	auto str = config.str;
	str.reserve(min(config.m + str.size(), static_cast<size_t>(100'000)));

	for (auto &i : config.opt) {
		switch (i.type) {
			case Opt::Q:
				{
					uint len = 0;
					for (uint l = i.x - 1, r = i.y - 1; r < str.size() && str[l] == str[r]; l++, r++, len++);
					res.push_back(len);
				}
			break;
			case Opt::R:
				str[i.x - 1] = static_cast<char>(i.y);
			break;
			case Opt::I:
				str.insert(str.begin() + i.x, static_cast<char>(i.y));
			break;
			default:
				throw runtime_error("Unexpected operation in solve!");
		}
	}

	return move(res);
}