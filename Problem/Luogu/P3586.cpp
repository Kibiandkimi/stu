//
// Created by kibi on 24-8-18.
//
// TODO terrible unique_ptr
#include <cctype>
#include <cstdio>
#include <memory>
#include <random>
#include <system_error>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

class Char {
	uint c;
public:
	Char (const uint t) : c(t) {}

	Char operator + (const Char &t) {
		c = t.c;
		return *this;
	}

	Char operator * (const Char) const {
		return *this;
	}

	Char operator * (const uint) const {
		return *this;
	}

	Char operator - (const uint) const {
		return *this;
	}

	bool operator == (const uint) const {
		return false;
	}

	uint get() const {
		return c;
	}
};

bool isdigit(const Char &c){
	return c.get() == 'U' || c.get() == 'Z';
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
	enum OptType {
		U,
		Z,
	};

	using Opt = tuple<OptType, uint, uint>;

	uint n;
	vector<Opt> opt;
};

vector<bool> solve(const Config &);

int main() {
	const auto n = read<uint>(), m = read<uint>();

	Config config{n, vector<Config::Opt>(m)};
	for (auto &i : config.opt) {
		get<0>(i) = read<Char>().get() == 'U' ? Config::U : Config::Z;
		get<1>(i) = read<uint>();
		get<2>(i) = read<uint>();
	}

	auto ans = solve(config);
	for (const auto i : ans) {
		printf(i ? "TAK\n" : "NIE\n");
	}

	return 0;
}

mt19937 rnd(random_device{}());

class FhqTreapNode;
using FTN = FhqTreapNode;

class FhqTreapNode {
	const uint value;
	const uint rnk;
	uint siz;
	unsigned long long sum;
	unique_ptr<FTN> ls, rs;

	void update() {
		siz = size(ls) + size(rs) + 1;
		sum = get_sum(ls) + get_sum(rs) + value;
	}

public:
	explicit FhqTreapNode(const uint value) : value(value), rnk(rnd()), siz(1), sum(value), ls(nullptr), rs(nullptr){}

	static uint size(const unique_ptr<FTN> &u) {
		return u != nullptr ? u->siz : 0;
	}

	static unsigned long long get_sum(const unique_ptr<FTN> &u) {
		return u != nullptr ? u->sum : 0;
	}

	static uint get_value(const unique_ptr<FTN> &u) {
		return u != nullptr ? u->value : 0;
	}

	/**
	 * split a TreeNode by value
	 * @param l left result of split
	 * @param r right result of split
	 * @param k value that split by
	 */
	void split(unique_ptr<FTN> &l, unique_ptr<FTN> &r, const uint k) {
		if (value <= k) {
			l.reset(this);
			l->rs != nullptr ? l->rs->split(l->rs, r, k) : static_cast<void>(0);
			l->update();
		} else {
			r.reset(this);
			r->ls != nullptr ? r->ls->split(l, r->ls, k) : static_cast<void>(0);
			r->update();
		}
	}

	void split_by_rnk(unique_ptr<FTN> &l, unique_ptr<FTN> &r, const uint rnk) {
		if (siz < rnk) {
			throw invalid_argument("rnk is out of range!");
		}
		if (size(ls) >= rnk) {
			r.get() != this ? r.reset(this) : static_cast<void>(0); // TODO maybe need to do like this
			r->ls != nullptr ? r->ls->split_by_rnk(l, r->ls, rnk) : static_cast<void>(0);
			r->update();
		}else {
			l.reset(this);
			l->rs != nullptr ? l->rs->split_by_rnk(l->rs, r, rnk - size(r->ls) - 1) : static_cast<void>(0);
			l->update();
		}
	}

	static unique_ptr<FTN> merge(unique_ptr<FTN> &l, unique_ptr<FTN> &r) {
		if ( l == nullptr || r == nullptr ) {
			return move(l == nullptr ? r : l);
		}
		if(l->rnk > r->rnk) {
			l->rs = merge(l->rs, r);
			l->update();
			return move(l);
		}
		r->ls = merge(l, r->ls);
		r->update();
		return move(r);
	}
};

class FhqTreap {;
	unique_ptr<FTN> rt;

public:
	FhqTreap() : rt(nullptr) {}

	void insert(uint value) {
		auto new_node = make_unique<FTN>(FTN(value));
		unique_ptr<FTN> l, r;
		rt->split(l, r, FTN::get_value(new_node));
		rt = FTN::merge(l, new_node);
		rt = FTN::merge(rt, r);
	}

	uint query_rnk(uint value) {
		if (value == 0) {
			return 1;
		}
		unique_ptr<FTN> l, r;
		rt->split(l, r, value - 1);
		auto res = FTN::size(l) + 1;
		rt = FTN::merge(l, r);
		return res;
	}

	/**
	 * remove one value from the tree
	 * you need to ensure the value exists
	 * @param value value to remove
	 */
	void remove(uint value) {
		if (value == 0) {
			unique_ptr<FTN> to_remove;
			rt->split_by_rnk(to_remove, rt, 1);
			return ;
		}
		unique_ptr<FTN> l, r, to_remove;
		rt->split(l, r, value - 1);
		r->split_by_rnk(to_remove, r, 1);
		rt = FTN::merge(l, r);
	}

	unsigned long long query_sum(uint value){
		unique_ptr<FTN> l, r;
		rt->split(l, r, value);
		auto res = FTN::get_sum(l);
		rt = FTN::merge(l, r);
		return res;
	}

};


vector<bool> solve(const Config &config) {
	vector<bool> res;
	vector<uint> list(config.n);
	// unsigned long long sum = 0;
	FhqTreap treap;

	for (auto &i : list) {
		treap.insert(i);
	}

	for (auto &i : config.opt) {
		switch (get<0>(i)) {
			case Config::U:
				treap.remove(list[get<1>(i) - 1]);
				treap.insert(get<2>(i));
				list[get<1>(i) - 1] = get<2>(i);
				break;
			case Config::Z:
				res.push_back(
					treap.query_sum(get<2>(i)) + static_cast<unsigned long long>(config.n - treap.query_rnk(get<2>(i) + 1)) * get<2>(i)
						>= static_cast<unsigned long long>(get<1>(i)) * get<2>(i)
				);

		}
	}

	return res;
}