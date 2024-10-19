//
// Created by kibi on 24-8-23.
//
// 一发次优解
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
#include <stack>
#include <sys/types.h>
#include <vector>
using namespace std;

using ull = unsigned long long;

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

ull solve(const Config&);

int main() {
	auto n = read<uint>();
	Config config{vector<uint>(n)};
	for (auto &i : config.arr) {
		i = read<uint>();
	}

	auto ans = solve(config);
	printf("%llu\n", ans);
}

class NodeData{
public:
	uint id, value;

	bool operator == (const NodeData& other) const {
		return value == other.value;
	}
};

class Node : public NodeData {
public:
	Node *ls, *rs;
};

class Query {
public:
	uint l, r, mx;
};

class BIT {
	vector<uint> value;
public:
	explicit BIT(const uint n):value(n + 1){}

	void update(uint pos, const uint val) {
		while (pos < value.size()) {
			value[pos] += val;
			pos += pos & -pos;
		}
	}

	uint query(uint pos) const {
		uint res = 0;
		while (pos) {
			res += value[pos];
			pos -= pos & -pos;
		}
		return res;
	}
};

ull solve(const Config &config) {
	ull res = 0;

	// build Cartesian Tree to recursive
	vector<Node> nodes(config.arr.size());
	stack<uint> stk; // store the right list of the tree
	for (uint i = 0; i < config.arr.size(); ++i) {
		nodes[i].id = i;
		nodes[i].value = config.arr[i];
		stk.empty() ? stk.push(i) : [&stk, &nodes, i] { // insert a node
			Node *pre = nullptr;
			while (!stk.empty() && nodes[stk.top()].value < nodes[i].value) {
				pre = &nodes[stk.top()];
				stk.pop();
			}
			stk.push(stk.empty() ? i : (nodes[stk.top()].rs = &nodes[i])->id);
			nodes[i].ls = pre;
		}();
	}

	uint rt = -1; // panic when stk is empty
	while (!stk.empty()) {
		rt = stk.top();
		stk.pop();
	}

	// off-line the queries
	vector<Query> queries;
	auto dfs = [&](Node *u, uint l, uint r, auto &&dfs) -> void {
		if(r - u->id > u->id - l) {
			for (uint i = l; i <= u->id; i++) {
				queries.push_back({u->id, r, u->value / nodes[i].value});
			}
		}else {
			for (uint i = u->id; i <= r; i++) {
				queries.push_back({l, u->id, u->value / nodes[i].value});
			}
		}
		u->ls ? dfs(u->ls, l, u->id - 1, dfs) : static_cast<void>(0);
		u->rs ? dfs(u->rs, u->id + 1, r, dfs) : static_cast<void>(0);
	};
	dfs(&nodes[rt], 0, nodes.size() - 1, dfs);

	// discretization
	/*map<uint, uint> mp;
	vector<NodeData> val(nodes.begin(), nodes.end());
	sort(val.begin(), val.end(), [](const auto &a, const auto &b) {return a.value < b.value;});
	val.resize(unique(val.begin(), val.end()) - val.begin());
	for (uint i = 0; i < val.size(); ++i) {
		mp[val[i].value] = i;
	}*/

	sort(nodes.begin(), nodes.end(), [](const auto &a, const auto &b) {return a.value < b.value;});

	BIT bit(nodes.size());
	sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) {return a.mx < b.mx;});
	for (auto &i : queries) {
		static uint now = 0; // lead to that the func solve can be only called once
		while (now < nodes.size() && nodes[now].value <= i.mx) {
			bit.update(nodes[now].id + 1, 1);
			now++;
		}
		res += bit.query(i.r + 1) - bit.query(i.l);
	}

	return res;
}
