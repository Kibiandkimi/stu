//
// Created by kibi on 24-8-22.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stack>
#include <sys/types.h>
#include <vector>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while (!isdigit(c)) {
		if (w == '-') {
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

vector<uint> solve(const Config&);

int main() {
	auto n = read<uint>();
	Config config{vector<uint>(n)};
	// all_of(config.arr.begin(), config.arr.end(), [](uint &x){static uint i = 0; x = ++i; return true;});
	for (auto &i : config.arr) {
		i = read<uint>();
	}

	auto ans = solve(config);
	for (auto &i : ans) {
		printf("%u ", i);
	}

	return 0;
}

class Node {
public:
	uint value, id;
	Node *ls, *rs;
};

vector<uint> solve(const Config &config) {
	vector<uint> arr(config.arr.size());
	for (uint i = 0; i < config.arr.size(); i++) {
		arr[config.arr[i] - 1] = i;
	}

	stack<Node*> rs;
	Node *rt = nullptr;
	uint id = 1;
	for (auto &i : arr) {
		rs.empty() ? rs.emplace(rt = new Node{i, id++, nullptr, nullptr}) : [&rs, &id, &rt, i]{
			Node *son = nullptr;
			while(!rs.empty() && rs.top()->value > i) {
				son = rs.top();
				rs.pop();
			}
			auto new_node = new Node{i, id++, son, nullptr};
			rs.emplace(!rs.empty() ? rs.top()->rs = new_node : rt = new_node);
		}();
	}

	vector<uint> res;
	res.reserve(config.arr.size());
	stack<Node*> stk;
	stk.emplace(rt);
	while (!stk.empty()) {
		auto u = stk.top();
		stk.pop();
		res.emplace_back(u->id);
		u->rs ? stk.emplace(u->rs) : static_cast<void>(0);
		u->ls ? stk.emplace(u->ls) : static_cast<void>(0);
	}

	return move(res);
}
