//
// Created by kibi on 24-8-7.
//
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(c < '0' || '9' < c) {
		if(c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while('0' <= c && c <= '9'){
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

class Config {
public:
	class Opt {
	public:
		bool type;
		uint l, r;
	};
	vector<uint> val;
	vector<Opt> opt;
	uint pos;
};

class Solution{
	Config &config;

	template<typename Data>
	class SegTree {
	public:
		class Node {
		public:
			const uint l, r;
			Data data;
			Node *ls, *rs;
		};
	private:

		Node *rt;

		void build(Node *u, vector<Data> &val) {
			if(u->l == u->r) {
				u->data = val[u->l];
				return;
			}
			auto mid = u->l + u->r >> 1;
			u->ls = new Node{u->l, mid}, u->rs = new Node{mid + 1, u->r};
			build(u->ls, val);
			build(u->rs, val);
			Data::update(u);
		}

		void modify(Node *u, uint l, uint r, typename Data::ModifyType type){
			if(l <= u->l && u->r <= r) {
				Data::modify(u, type);
				return;
			}

			Data::push_down(u);

			auto mid = u->l + u->r >> 1;

			if(l <= mid) {
				modify(u->ls, l, r, type);
			}
			if(r > mid) {
				modify(u->rs, l, r, type);
			}

			Data::update(u);
		}

		Node query(Node *u, uint l, uint r) {
			if(l <= u->l && u->r <= r) {
				return *u;
			}

			Data::push_down(u);

			auto mid = u->l + u->r >> 1;

			if(l > mid) {
				return query(u->rs, l, r);
			}
			if(r <= mid) {
				return query(u->ls, l, r);
			}

			Node node_l = query(u->ls, l, r);
			Node node_r = query(u->rs, l, r);
			Node node{node_l.l, node_r.r, Data(), &node_l, &node_r};

			Data::update(&node);

			return node;
		}

	public:
		explicit SegTree(vector<Data> &val) {
			rt = new Node{0, val.size() - 1, Data(), nullptr, nullptr};
			build(rt, val);
		}

		void modify(uint l, uint r, typename Data::ModifyType type){
			modify(rt, l, r, type);
		}

		Data query(uint l, uint r) {
			return query(rt, l, r).data;
		}

	};

	class Data {
		uint sum;

	public:
		Data() : sum(0) {}
		explicit Data(uint sum):sum(sum){}

		enum ModifyType{
			Zero,
			One,
		};

		static void update(SegTree<Data>::Node *u) {
			u->data.sum = u->ls->data.sum + u->rs->data.sum;
		}

		static void push_down(const SegTree<Data>::Node *u) {
			if(u->data.sum == u->r - u->l + 1) {
				u->ls->data.sum = u->ls->r - u->ls->l + 1;
				u->rs->data.sum = u->rs->r - u->rs->l + 1;
			}else if(u->data.sum == 0) {
				u->ls->data.sum = 0;
				u->rs->data.sum = 0;
			}
		}

		static void modify(SegTree<Data>::Node *u, ModifyType type) {
			switch(type) {
				case ModifyType::One :
					u->data.sum = u->r - u->l + 1;
				break;
				case ModifyType::Zero :
					u->data.sum = 0;
			}
		}

		uint get() const {
			return sum;
		}

	};

	bool check(uint p) const {
		vector<Data> data(config.val.size());
		for(uint i = 0; i < config.val.size(); i++) {
			if(config.val[i] >= p) {
				data[i] = Data(1);
			}else{
				data[i] = Data(0);
			}
		}

		SegTree<Data> seg_tree(data);
		for(auto &i : config.opt) {
			auto sum = seg_tree.query(i.l, i.r).get();
			if(i.type) {
				sum > 0 ? seg_tree.modify(i.l, i.l + sum - 1, Data::ModifyType::One) : static_cast<void>(0);
				sum < i.r - i.l + 1 ? seg_tree.modify(i.l + sum, i.r, Data::ModifyType::Zero) : static_cast<void>(0);
			}else {
				sum > 0 ? seg_tree.modify(i.r - sum + 1, i.r, Data::ModifyType::One) : static_cast<void>(0);
				sum < i.r - i.l + 1 ? seg_tree.modify(i.l, i.r - sum, Data::ModifyType::Zero) : static_cast<void>(0);
			}
		}

		return seg_tree.query(config.pos - 1, config.pos - 1).get() == 1;
	}

public:
	explicit Solution(Config &config):config(config){}

	uint solve() const {
		uint l = 1, r = config.val.size();

		for(auto &i : config.opt) {
			i.l--;
			i.r--;
		}

		while(l <= r) {
			uint mid = l + r >> 1;
			if(check(mid)) {
				l = mid + 1;
			}else {
				r = mid - 1;
			}
		}

		return r;
	}
};

int main() {

	auto n = read<uint>(), m = read<uint>();

	Config config{vector<uint>(n), vector<Config::Opt>(m)};
	for(auto &i : config.val) {
		i = read<uint>();
	}
	for(auto &i : config.opt) {
		i = {static_cast<bool>(read<uint>()), read<uint>(), read<uint>()};
	}

	config.pos = read<uint>();

	auto ans = Solution(config).solve();
	printf("%u\n", ans);
}

