//
// Created by kibi on 24-8-9.
//
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while (c < '0' || '9' < c) {
		if (c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while ('0' <= c && c <= '9') {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

class Config {
public:
	class Star {
	public:
		uint x, y, light;
	};

	uint n, W, H;
	vector<Star> stars;
};

class Solution {
	Config &config;

	template<typename Data>
	class SegTree {
	public:
		class Node {
		public:
			Node(uint l, uint r, Data data, Node *ls, Node *rs) : l(l), r(r), data(data), ls(ls), rs(rs) {}

			uint l, r;
			Data data;
			Node *ls, *rs;
		};

		SegTree(uint n, vector<Data> &raw_data) {
			rt = new Node(0, n - 1, Data(), nullptr, nullptr);
			build(rt, raw_data);
		}

		~SegTree() {
			destroy(rt);
		}

		void modify(uint l, uint r, typename Data::ModifyType type) {
			modify(rt, l, r, type);
		}

		Data query(uint l, uint r) {
			return query(rt, l, r).data;
		}

	private:
		Node *rt;

		void build(Node *u, vector<Data> &raw_data) {
			if (u->l == u->r) {
				u->data = raw_data[u->l];
				return;
			}

			uint mid = (u->l + u->r) / 2;
			u->ls = new Node(u->l, mid, Data(), nullptr, nullptr);
			u->rs = new Node(mid + 1, u->r, Data(), nullptr, nullptr);
			build(u->ls, raw_data);
			build(u->rs, raw_data);
			Data::update(u);
		}

		void modify(Node *u, uint l, uint r, typename Data::ModifyType type) {
			if (l <= u->l && u->r <= r) {
				Data::modify(u, type);
				return;
			}

			Data::push_down(u);

			uint mid = (u->l + u->r) / 2;
			if (l <= mid) {
				modify(u->ls, l, r, type);
			}
			if (r >= mid + 1) {
				modify(u->rs, l, r, type);
			}

			Data::update(u);
		}

		Node query(Node *u, uint l, uint r) {
			if (l <= u->l && u->r <= r) {
				return *u;
			}

			Data::push_down(u);

			uint mid = (u->l + u->r) / 2;
			if (l > mid) {
				return query(u->rs, l, r);
			}
			if (r <= mid) {
				return query(u->ls, l, r);
			}

			Node node_l = query(u->ls, l, r);
			Node node_r = query(u->rs, l, r);
			Node node(node_l.l, node_r.r, Data(), &node_l, &node_r);
			Data::update(&node);
			return node;
		}

		void destroy(Node *u) {
			u->ls ? destroy(u->ls) : static_cast<void>(0);
			u->rs ? destroy(u->rs) : static_cast<void>(0);
			delete u;
		}

	};

	class Data {
		uint mx, flag;

	public:
		Data() : mx(0), flag(0) {}
		explicit Data(const uint sum) : mx(sum), flag(0) {}

		class ModifyType {
		public:
			int sum;
			explicit ModifyType(const int sum) : sum(sum) {}
		};

		static void update(SegTree<Data>::Node *u) {
			u->data.mx = max(u->ls->data.mx, u->rs->data.mx);
		}

		static void push_down(SegTree<Data>::Node *u) {
			u->ls->data.mx += u->data.flag;
			u->rs->data.mx += u->data.flag;
			u->ls->data.flag += u->data.flag;
			u->rs->data.flag += u->data.flag;
			u->data.flag = 0;
		}

		static void modify(SegTree<Data>::Node *u, ModifyType type) {
			u->data.mx += type.sum;
			u->data.flag += type.sum;
		}

		uint get() const {
			return mx;
		}
	};

public:
	explicit Solution(Config &config) : config(config) {}

	uint solve() const {
		vector<uint> pos_x, pos_y;
		for (auto &i : config.stars) {
			pos_x.push_back(i.x);
			pos_x.push_back(i.x + config.W);
			pos_y.push_back(i.y);
			pos_y.push_back(i.y + config.H - 1);
		}

		sort(pos_x.begin(), pos_x.end());
		auto pos_x_siz = unique(pos_x.begin(), pos_x.end()) - pos_x.begin();
		pos_x.resize(pos_x_siz);
		sort(pos_y.begin(), pos_y.end());
		auto pos_y_siz = unique(pos_y.begin(), pos_y.end()) - pos_y.begin();
		pos_y.resize(pos_y_siz);

		map<uint, uint> pos_x_map, pos_y_map;
		for (auto &i : pos_x) {
			pos_x_map[i] = &i - &*pos_x.begin();
		}
		for (auto &i : pos_y) {
			pos_y_map[i] = &i - &*pos_y.begin();
		}

		vector<Data> temp(pos_y.size());

		SegTree<Data> seg_tree(pos_y.size(), temp);
		uint mx = 0;
		vector<tuple<uint, uint, uint, int>> opt;
		for(auto &i : config.stars) {
			opt.emplace_back(pos_x_map[i.x], pos_y_map[i.y], pos_y_map[i.y + config.H - 1], i.light);
			opt.emplace_back(pos_x_map[i.x + config.W], pos_y_map[i.y], pos_y_map[i.y + config.H - 1], -i.light);
		}
		sort(opt.begin(), opt.end(), [](auto &a, auto &b) {return get<0>(a) == get<0>(b) ? get<3>(a) < 0 : get<0>(a) < get<0>(b);});

		for(auto &i : opt) {
			seg_tree.modify(get<1>(i), get<2>(i), Data::ModifyType(get<3>(i)));
			mx = max(mx, seg_tree.query(0, pos_y.size()).get());
		}

		return mx;
	}
};

int main() {
	auto T = read<uint>();

	while (T--) {
		auto n = read<uint>(), W = read<uint>(), H = read<uint>();

		Config config{n, W, H, vector<Config::Star>(n)};
		for (auto &i : config.stars) {
			i = {read<uint>(), read<uint>(), read<uint>()};
		}

		auto ans = Solution(config).solve();
		printf("%u\n", ans);
	}
}