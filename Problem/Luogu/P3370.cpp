//
// Created by kibi on 24-8-9.
//
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(c < '0' || '9' < c){
		if(c == '-'){
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
	vector<string> str;
};

uint solve(Config &config);

int main() {
	auto n = read<uint>();

	Config config{vector<string>(n)};
	for(auto &i : config.str) {
		cin >> i;
	}

	auto ans = solve(config);
	printf("%u\n", ans);
}

uint solve(Config &config) {
	set<int> st;
	hash<string> hasher;
	for(auto &i : config.str) {
		st.insert(hasher(i));
	}
	return st.size();
}