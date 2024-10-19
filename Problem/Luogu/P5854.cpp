//
// Created by kibi on 24-8-22.
//
#include <algorithm>
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

class Config {
public:
	vector<uint> arr;
};

tuple<unsigned long long, unsigned long long> solve(const Config &);

int main() {
	auto n = read<uint>();

	Config config{vector<uint>(n)};
	for (auto &i : config.arr) {
		i = read<uint>();
	}

	auto [l, r] = solve(config);
	printf("%llu %llu\n", l, r);
}

class Node {
public:
	uint id;
	Node *ls, *rs;
};

tuple<unsigned long long, unsigned long long> solve(const Config &config) {
	stack<uint> stk;
	vector<Node> nodes(config.arr.size());
	all_of(nodes.begin(), nodes.end(), [](Node &n) {static uint i = 0; n.id = i++; return true;});
	for (auto &i : nodes) {
		Node* ls = nullptr;
		while (!stk.empty() && config.arr[nodes[stk.top()].id] > config.arr[i.id]) {
			ls = &nodes[stk.top()];
			stk.pop();
		}
		i.ls = ls;
		!stk.empty() ? nodes[stk.top()].rs = &i : &i;
		stk.push(i.id);
	}

	unsigned long long l = 0, r = 0;
	for (auto &i : nodes) {
		static unsigned long long cnt = 1;
		l ^= cnt * (i.ls ? i.ls->id + 2 : 1);
		r ^= cnt * (i.rs ? i.rs->id + 2 : 1);
		cnt++;
	}

	return {l, r};
}
