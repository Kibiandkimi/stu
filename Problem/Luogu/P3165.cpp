//
// Created by kibi on 24-8-20.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <random>
#include <stack>
#include <sys/types.h>
#include <system_error>
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

vector<uint> solve(const Config&);

mt19937 rnd(random_device{}());

int main() {
	// auto n = read<uint>();

	Config config{vector<uint>(100000)};
	for (auto &i : config.arr) {
		// i = read<uint>();
		i = rnd();
	}

	auto ans = solve(config);
	for (auto &i : ans) {
		printf("%u ", i + 1);
	}

	return 0;
}

class FhqTreapNode;
class FhqTreap;

using FTN = FhqTreapNode;
using FT = FhqTreap;

class FhqTreapNode {
	friend FhqTreap;

	uint value, rnk, siz;
	FTN *ls, *rs;
	bool tag;

	void update() {
		siz = size(ls) + size(rs) + 1;
	}

	void push_down() {
		if(tag) {
			swap(ls, rs);
			modify(ls);
			modify(rs);
			tag = false;
		}
	}

public:
	explicit FhqTreapNode(uint value) :
		value(value),
		rnk(rnd()),
		siz(1),
		ls(nullptr),
		rs(nullptr),
		tag(false)
	{}

	~FhqTreapNode() {
		delete ls;
		delete rs;
	}

	static void modify(FTN* u) {
		u ? u->tag ^= true : false;
	}

	static uint size(const FTN *u) {
		return u == nullptr ? 0 : u->siz;
	}

	void split_by_rnk(FTN *&l, FTN *&r, const uint rnk) {
		push_down();
		if (size(ls) >= rnk) {
			r = this;
			ls ? ls->split_by_rnk(l, ls, rnk) : static_cast<void>(l = nullptr);
		}else {
			l = this;
			rs ? rs->split_by_rnk(rs, r, rnk - size(ls) - 1) : static_cast<void>(r = nullptr);
		}
		update();
	}

	static FTN* merge(FTN *l, FTN *r) {
		if (l == nullptr) {
			return r;
		}
		if (r == nullptr) {
			return l;
		}
		if (l->rnk > r->rnk) {
			l->push_down();
			l->rs = merge(l->rs, r);
			l->update();
			return l;
		}
		r->push_down();
		r->ls = merge(l, r->ls);
		r->update();
		return r;
	}
};

class FhqTreap {
	FTN *rt;

	// TODO fix
	void build(FTN* u, uint l, uint r) {
		if (l == r){
			return;
		}
		int mid = u->value;
		u->ls = l < mid ? new FhqTreapNode((l + mid) / 2) : nullptr;
		u->rs = mid < r ? new FhqTreapNode((mid + 1 + r) / 2) : nullptr;
		u->ls ? build(u->ls, l, mid - 1) : static_cast<void>(0);
		u->rs ? build(u->rs, mid + 1, r) : static_cast<void>(0);
	}

	static void reset(FTN* u, const uint pre) {
		if(u) {
			u->value = FTN::size(u->ls) + 1 + pre;
			reset(u->ls, pre);
			reset(u->rs, u->value);
		}
	}

public:
	FhqTreap() : rt(nullptr) {}
	FhqTreap(FTN *rt) : rt(rt){}
	explicit FhqTreap(const uint n) : rt(nullptr) {
		for (uint i = 1; i <= n; i++) {
			rt = FhqTreapNode::merge(rt, new FhqTreapNode(i));
		}
	}

	~FhqTreap() {
		delete rt;
	}

	void modify(uint begin, uint end) {
		FTN *l = nullptr, *r = nullptr, *to_modify = nullptr;
		rt->split_by_rnk(l, r, begin - 1);
		r->split_by_rnk(to_modify, r, end - begin + 1);
		FTN::modify(to_modify);
		r = FTN::merge(to_modify, r);
		rt = FTN::merge(l, r);
	}

	vector<uint>& res() {
		static vector<uint> res(FTN::size(rt));
		static vector<FTN*> v(FTN::size(rt));
		static vector<uint> pre(FTN::size(rt));
		uint pos = 0;
		v[0] = rt, pre[0] = 0;
		while (pos != UINT32_MAX) {
			auto u = v[pos];
			u->push_down();
			res[FTN::size(u->ls) + pre[pos]] = u->value;
			u->value = FTN::size(u->ls) + pre[pos] + 1;
			pos--;
			if(u->ls != nullptr) {
				v[++pos] = u->ls;
				// pre[pos] = pre[pos - 1];
			}
			if(u->rs != nullptr) {
				v[++pos] = u->rs;
				pre[pos] = u->value;
			}
		}
		return res;
	}

	void copy(FTN* raw, FTN* &to_copy) {
		to_copy = new FTN(*raw);
		raw->ls ? copy(raw->ls, to_copy->ls) : static_cast<void>(0);
		raw->rs ? copy(raw->rs, to_copy->rs) : static_cast<void>(0);
	}

	FhqTreap clone() {
		FhqTreap res;
		copy(rt, res.rt);
		return res;
	}

	void reset() {
		reset(rt, 0);
	}

};

class Point {
public:
	uint value, pos;
};

void calc(vector<uint> &arr, vector<uint> &res, const uint batch, uint l) {
	static FhqTreap treap(arr.size());
	vector<Point> point;
	point.reserve(batch);
	for (uint i = l, t = batch; t; i++) {
		if (arr[i] > l && arr[i] <= l + batch) {
			point.push_back({arr[i], i});
			t--;
		}
	}
	sort(point.begin(), point.end(), [](const Point &a, const Point &b) {return a.value < b.value;});
	for (uint i = 0; i < batch; i++) {
		res.push_back(point[i].pos);
		treap.modify(++l, point[i].pos + 1);
		for (uint j = i + 1; j < batch; j++) {
			if (point[j].pos < point[i].pos) {
				point[j].pos = point[i].pos - point[j].pos + l - 1;
			}
		}
	}
	const auto &arrange = treap.res();
	vector<uint> temp = arr;
	for (uint i = 0; i < arr.size(); i++) {
		temp[i] = arr[arrange[i] - 1];
	}
	arr = move(temp);
}

vector<uint> solve(const Config &config) {
	vector<uint> res;
	vector<uint> arr = config.arr;
	vector<Point> point(arr.size());

	for (uint i = 0; i < arr.size(); i++) {
		point[i] = {arr[i], i};
	}

	sort(point.begin(), point.end(),
	[](const Point &a, const Point &b) {return a.value == b.value ? a.pos < b.pos : a.value < b.value;}
	);

	for (uint i = 0; i < arr.size(); i++){
		arr[point[i].pos] = i + 1;
	}

	res.reserve(arr.size());

	uint n = config.arr.size();
	while (true) {
		const uint T = 1400;
		calc(arr, res, n > T ? T : n, config.arr.size() - n);
		if (n <= T) {
			break;
		}
		n -= T;
	}

	return move(res);
}
