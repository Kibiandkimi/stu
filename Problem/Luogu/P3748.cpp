//
// Created by kibi on 24-8-30.
//
// TODO tttttooodooooooo
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <queue>
#include <stack>
#include <stdexcept>
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

class Edge{
public:
	uint u, v;
};

class Config {
public:
	enum ConfigType {
		None,
		One,
		Both
	};
	ConfigType type;
	uint n;
	uint p0, p1, h0, h1;
	vector<Edge> edges;
};

uint solve(const Config&);

int main() {
	uint T = read<uint>();
	const uint x = read<uint>();
	Config::ConfigType type;
	switch (x) {
		case 0:
			type = Config::None;
			break;
		case 1:
			type = Config::One;
			break;
		case 2:
			type = Config::Both;
			break;
		default:
			throw runtime_error("Unexpected value x! ( x = " + to_string(x) + " )");
	}
	while (T--) {
		const auto n = read<uint>();
		Config config{type, n};
		switch (type) {
			case Config::None:
				break;
			case Config::One:
				config.p0 = read<uint>();
				config.p1 = read<uint>();
				break;
			case Config::Both:
				config.p0 = read<uint>();
				config.p1 = read<uint>();
				config.h0 = read<uint>();
				config.h1 = read<uint>();
		}
		config.edges.reserve(n - 1);
		for (uint i = 1; i < n; i++) {
			config.edges.push_back({read<uint>(), read<uint>()});
		}

		const auto ans = solve(config);
		printf("%u\n", ans);
	}
}

class Graph {
	class Edge {
	public:
		uint v;
		Edge *nxt;

		~Edge() {
			delete nxt;
		}
	};

	vector<Edge*> edges;
public:
	explicit Graph(const uint n) : edges(n) {}

	void add_edge(const uint u, const uint v, const bool flag = false) {
		edges[u] = new Edge{v, edges[u]};
		flag ? add_edge(v, u) : static_cast<void>(0);
	}

	auto begin(const uint u) const {
		return edges[u];
	}
};

vector<uint> get_path(const Graph &graph, const uint n, const uint u, const uint v) {
	vector<bool> vis(n);
	stack<tuple<decltype(graph.begin(0)), uint>> stack;
	stack.emplace(graph.begin(u), u);
	while (!stack.empty()) {
		// auto &[it, now] = stack.top();
		auto &it = get<0>(stack.top());
		const auto now = get<1>(stack.top());

		if(now == v) {
			break;
		}
			!vis[it->v] ? stack.emplace(graph.begin(it->v), it->v) : static_cast<void>(0);
			it = it->nxt;

		vis[now] = true;

		if (it) {
			!vis[it->v] ? stack.emplace(graph.begin(it->v), it->v) : static_cast<void>(0);
			it = it->nxt;
		}else {
			stack.pop();
		}
	}
	if (stack.empty()) {
		throw runtime_error("Can't find any way from u to v, where u = " + std::to_string(u) +
																   ", v = " + std::to_string(v));
	}
	vector<uint> res;
	res.reserve(stack.size());
	while (!stack.empty()) {
		res.emplace_back(get<1>(stack.top()));
		stack.pop();
	}
	reverse(res.begin(), res.end());
	return res;
}

uint solve_both(const Config &config, Graph &graph) {
	auto path_p = get_path(graph, config.n, config.p0 - 1, config.p1 - 1);
	auto path_h = get_path(graph, config.n, config.h0 - 1, config.h1 - 1);

	vector<bool> del(config.n);

	for (auto &i : path_p) {
		del[i] = true;
	}
	for (auto &i : path_h) {
		del[i] = true;
	}

	uint res = 0;
	for (uint i = 0; i < config.n; i++) {
		if (!del[i]) {
			res++;
			queue<uint> queue;
			queue.push(i);
			while (!queue.empty()) {
				auto now = queue.front();
				queue.pop();
				del[i] = true;
				for (auto j = graph.begin(now); j; j = j->nxt) {
					if (!del[j->v]) {
						queue.push(j->v);
					}
				}
			}
		}
	}

	return res;
}

uint solve(const Config &config) {
	Graph graph(config.n);
	for (auto &i : config.edges) {
		graph.add_edge(i.u - 1, i.v - 1, true);
	}

	switch (config.type) {
		case Config::Both:
			return solve_both(config, graph);
		case Config::One:{}
		case Config::None:{}
	}
}