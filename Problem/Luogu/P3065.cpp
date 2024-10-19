//
// Created by kibi on 24-8-17.
//
#define NDEBUG
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <sys/types.h>
#include <vector>
using namespace std;

class MyString {
	string str;

public:
	MyString(const uint &x) {
		x ? str.push_back(static_cast<char>(x)) : static_cast<void>(0);
	}

	bool operator==(uint) const {
		return false;
	}

	MyString operator+(const MyString &other) {
		str.append(other.str);
		return move(*this);
	}

	MyString operator*(MyString &) {
		return move(*this);
	}

	MyString operator*(uint) {
		return move(*this);
	}

	MyString operator-(uint) {
		return move(*this);
	}

	string get() {
		return move(str);
	}

	const string &borrow() const {
		return str;
	}
};

bool isdigit(const MyString &str) {
	return islower(str.borrow()[0]);
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
	vector<string> str;
};

vector<uint> solve(const Config &);

int main() {
	const auto n = read<uint>();

	Config config{vector<string>(n)};
	for (auto &i : config.str) {
		i = read<MyString>().get();
	}

	auto ans = solve(config);
	cout << ans.size() << endl;
	for (const auto &i : ans) {
		printf("%s\n", config.str[i].c_str());
	}
}

class Trie {
	friend vector<uint> solve(const Config&);
	const uint MAX_VALUE;
	class Node {
	public:
		uint sum;
		vector<unique_ptr<Node>> children;
	};
	unique_ptr<Node> rt;

	unique_ptr<Node> new_node() const {
		return make_unique<Node>(Node{0, vector<unique_ptr<Node>>(MAX_VALUE)});
	}

public:
	explicit Trie(const uint n) : MAX_VALUE(n), rt(new_node()) {}

	void insert(const vector<uint> &str) const {
		auto it = rt.get();
		for (auto &i : str) {
			if (it->children[i] == nullptr) {
				it->children[i] = new_node();
			}
			it = it->children[i].get();
		}
		it->sum++;
	}
};

class Graph {
	class Node {
		friend class Graph;
		vector<weak_ptr<Node>> nxt;
	public:
		uint id{};
	};

	vector<shared_ptr<Node>> node;

public:
	explicit Graph(const uint n) : node(n) {
		for (uint i = 0; i < n; i++) {
			node[i] = make_shared<Node>();
			node[i]->id = i;
		}
	}

	void add_edge(uint a, uint b) {
		assert(a < node.size());
		assert(b < node.size());
		node[a]->nxt.emplace_back(node[b]);
	}

	const auto& nxt(const uint u) const {
		return node[u]->nxt;
	}
};

vector<uint> solve(const Config &config) {
	vector<uint> res;
	const Trie trie(26);
	for (auto &i : config.str) {
		trie.insert(
				[i]() -> vector<uint> {
					vector<uint> temp{i.begin(), i.end()};
					for (auto &j : temp) {
						j -= 'a';
					}
					return move(temp);
				}());
	}

	for (auto &i : config.str) {
		Graph graph(26);
		vector<uint> in(26);
		auto now = trie.rt.get();
		bool flag = true;
		for (auto &j : i) {
			for (auto &k : now->children) {
				if (k != nullptr && &k - now->children.begin().base() != j - 'a') {
					graph.add_edge(j - 'a', &k - now->children.begin().base());
					in[&k - now->children.begin().base()]++;
				}
			}
			if (now->sum > 0) {
				flag = false;
				break;
			}
			now = now->children[j - 'a'].get();
		}
		if(!flag) {
			continue;
		}
		if ( [&graph, &in]() -> bool{
			queue<uint> q;
			for (auto &j : in) {
				j == 0 ? q.push(&j - in.begin().base()) : static_cast<void>(0);
			}
			while (!q.empty()) {
				const auto u = q.front();
				q.pop();
				for (auto &j : graph.nxt(u)) {
					--in[j.lock()->id] == 0 ? q.push(j.lock()->id) : static_cast<void>(0);
				}
			}
			return all_of(in.begin(), in.end(), [](const auto &j){return j == 0;});
		}()) {
			res.push_back(&i - config.str.begin().base());
		}
	}

	return move(res);
}