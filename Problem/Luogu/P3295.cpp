//
// Created by kibi on 24-8-7.
//
// TODO P3295
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(c < '0' || '9' < c){
		if(c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while('0' <= c && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

class Config {
public:
	class Constraint {
	public:
		uint l1, r1, l2, r2;
	};
	uint n;
	vector<Constraint> constraint;
};

uint solve(Config &config);

int main() {
	auto n = read<uint>(), m = read<uint>();

	Config config{n, vector<Config::Constraint>(m)};
	for(auto &i : config.constraint) {
		i = {read<uint>(), read<uint>(), read<uint>(), read<uint>()};
	}

	auto ans = solve(config);
	printf("%u\n", ans);
}

uint solve(Config &config) {

}