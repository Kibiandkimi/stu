//
// Created by kibi on 24-10-5.
//
#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <stdexcept>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
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

class Opt {
public:
    enum Type {
        insert = 1,
        erase = 2,
        query = 3,
    };

    Type type;
    uint u, v, x;
};

class Config {
public:
    uint n, m;
    vector<Opt> opts;
};

vector<bool> solve(const Config&);

namespace MyCode {
    vector<bool> main() {
        freopen("temp.in", "r", stdin);
        // freopen("ds.out", "w", stdout);

        auto n = read<uint>(), m = read<uint>();
        Config config{n, m, vector<Opt>(m)};
        for (auto& opt : config.opts) {
            auto type = read<uint>(), u = read<uint>(), v = read<uint>();
            switch (type) {
                case 1:
                    opt = {Opt::insert, u, v, read<uint>()};
                break;
                case 2:
                    opt = {Opt::erase, u, v, read<uint>()};
                break;
                case 3:
                    opt = {Opt::query, u, v};
                break;
                default:
                    throw runtime_error("invalid operation!");
            }
        }
        return solve(config);
        auto ans = solve(config);
        for (auto i : ans) {
            printf(i ? "YES\n" : "NO\n");
        }

        fclose(stdin);
        // fclose(stdout);
        // return 0;
    }
}

namespace StdCode{
    #include <ctime>
    using namespace std;
    const int N=100000;
    int n,m;
    int lowbit(int x){return x&-x;}
    struct BIT{
        long long c[N+5];
        void add(int p,long long x){
            for(int i=p;i<=n;i+=lowbit(i))c[i]+=x;
        }
        long long sum(int p){
            long long res=0;
            for(int i=p;i;i^=lowbit(i))res+=c[i];
            return res;
        }
    };
    long long v[N+5];
    unordered_set<long long>s;
    mt19937 rnd(time(0));
    vector<bool> main(){
        memset(v, 0, sizeof(v));
        s.clear();
        BIT sz, c;

        vector<bool> res;
        freopen("temp.in","r",stdin);
        // freopen("ds.out","w",stdout);
        scanf("%d%d",&n,&m);
        for(int i=0,op,l,r,x;i<m;++i){
            scanf("%d",&op);
            if(op==1){
                scanf("%d%d%d",&l,&r,&x);
                if(!v[x]){
                    v[x]=rnd();
                    s.insert(v[x]);
                }
                c.add(l,v[x]);c.add(r+1,-v[x]);
                sz.add(l,1);sz.add(r+1,-1);
            }else if(op==2){
                scanf("%d%d%d",&l,&r,&x);
                c.add(l,-v[x]);c.add(r+1,v[x]);
                sz.add(l,-1);sz.add(r+1,1);
            }else{
                scanf("%d%d",&l,&r);
                int lim=sz.sum(r)-sz.sum(l);
                long long d=c.sum(r)-c.sum(l);
                if(!lim)res.push_back(d?false:true);
                else if(lim==1)res.push_back(s.count(d)?true:false);
                else{
                    bool flag=0;
                    for(long long x:s)
                        if(s.count(d-x)){
                            flag=1;
                            break;
                        }
                    res.push_back(flag?true:false);
                }
            }
        }
        return res;
    }
}

void data_gen();

int main() {
    while (true) {
        data_gen();
        auto my_ans = MyCode::main();
        auto std_ans = StdCode::main();
        if (my_ans.size() != std_ans.size()) {
            freopen("temp.out", "w", stdout);
            printf("Error!\n");
            if (my_ans.size() != std_ans.size()) {
                printf("With diff size!\nYour size:%lu\nStd size:%lu\n", my_ans.size(), std_ans.size());
            }
            printf("Your code has output:\n");
            for (auto i : my_ans) {
                printf(i ? "YES\n" : "NO\n");
            }
            printf("Std code has output:\n");
            for (auto i : std_ans) {
                printf(i ? "YES\n" : "NO\n");
            }
            fclose(stdout);
            return 0;
        }
    }
}

template <typename Data>
class SegTree {
    /*
    * impl operator +, +=, -= for Data
    * use .clear() instead of -=
    * */

    class Node {
    public:
        Node() : ls(nullptr), rs(nullptr), l(0), r(0), val(Data()){}

        Node *ls, *rs;
        size_t l, r;
        Data val;

        void update() {
            val = ls->val + rs->val;
        }

        void push_down() {
            ls->val += val;
            rs->val += val;
            // val -= Data();
            val.clear();
        }
    };

    template <typename Iterator>
    static void build(Node *u, size_t l, size_t r, Iterator it) {
        u->l = l, u->r = r;
        if (l == r) {
            u->val = move(*(it + l));
            return;
        }
        size_t mid = (l + r) / 2;
        u->ls = new Node(), u->rs = new Node();
        build(u->ls, l, mid, it);
        build(u->rs, mid + 1, r, it);
        u->update();
    }

    template <typename Modifier>
    void modify(Node *u, size_t l, size_t r, Modifier modifier) {
        if (l <= u->l && u->r <= r) {
            modifier(u->val);
            return;
        }

        u->push_down();

        auto mid = (u->l + u->r) / 2;

        if (l <= mid) {
            modify(u->ls, l, r, modifier);
        }
        if (r > mid) {
            modify(u->rs, l, r, modifier);
        }
        u->update();
    }

    const Data& query(Node *u, size_t pos) {
        if (u->l == u->r) {
            return u->val;
        }

        u->push_down();

        size_t mid = (u->l + u->r) / 2;
        if (pos <= mid) {
            return query(u->ls, pos);
        }
        return query(u->rs, pos);
    }

    Node *rt;

    static void destroy (Node *u){
        u->ls ? destroy(u->ls) : static_cast<void>(0);
        u->rs ? destroy(u->rs) : static_cast<void>(0);
        delete u;
    }

public:
    template <typename Iterator>
    SegTree(uint n, Iterator it) {
        build(rt = new Node(), 0, n - 1, it);
    }

    ~SegTree() {
        destroy(rt);
    }

    template <typename Modifier>
    void modify(size_t l, size_t r, Modifier modifier) {
        modify(rt, l, r, modifier);
    }

    const Data& query(size_t pos) {
        return query(rt, pos);
    }
};

class MySet {
public:
    MySet():st(new set<uint>()), st2(new set<uint>()){}
    // ~MySet(){
    //     delete st;
    //     delete st2;
    // }

    // set<uint> *st, *st2;
    unique_ptr<set<uint>> st, st2;

    MySet operator + (const MySet &other) const {
        return {};
    }

    void operator += (const MySet & other) const {
        // if (!other.st->empty()) {
        for (auto &i : *other.st) {
            st->insert(i);
        }
        // }
        // if (!other.st2->empty()) {
        for (auto &i : *other.st2) {
            st->erase(i);
        }
        // }
    }

    void operator -= (const MySet & other) const {
        st->clear();
        st2->clear();
    }

    void clear() const {
        st->clear();
        st2->clear();
    }
};

class MyInt {
public:
    ull val{0};

    MyInt operator + (const MyInt &other) const {
        return {};
    }

    void operator += (const MyInt & other) {
        val ^= other.val;
    }

    void clear() {
        val = 0;
    }
};

class MyInt2 {
public:
    ull val{0};

    MyInt2 operator + (const MyInt2 &other) const {
        return {};
    }

    void operator += (const MyInt2 & other) {
        val += other.val;
    }

    void clear() {
        val = 0;
    }
};

vector<bool> solve(const Config& config) {
    if (config.n <= 2'000 && config.m <= 2'000) {
        vector<bool> res;
        vector<set<uint>> st_list(config.n);
        for (auto &i : config.opts) {
            switch (i.type) {
                case Opt::insert:
                    for (uint j = i.u - 1; j < i.v; ++j) {
                        st_list[j].insert(i.x);
                    }
                break;
                case Opt::erase:
                    for (uint j = i.u - 1; j < i.v; ++j) {
                        st_list[j].erase(i.x);
                    }
                break;
                case Opt::query: {
                    bool flag = true;
                    for (auto &j : st_list[i.u - 1]) {
                        if (st_list[i.v - 1].find(j) == st_list[i.v - 1].end()) {
                            flag = false;
                            break;
                        }
                    }
                    printf(flag ? "1\n" : "0\n");
                    res.push_back(flag);
                }
            }
        }
        printf("\n");
        return res;
    }
    if (all_of(config.opts.begin(), config.opts.end(), [](auto &opt){
        return opt.type == Opt::query || opt.x <= 10;
    })) {
        vector<bool> res;
        SegTree<MySet> seg_tree(config.n, vector<MySet>(config.n).begin());
        for (auto &i : config.opts) {
            switch (i.type) {
                case Opt::insert:
                    seg_tree.modify(i.u - 1, i.v - 1, [&i](const MySet &u){
                        u.st->insert(i.x);
                    });
                break;
                case Opt::erase:
                    seg_tree.modify(i.u - 1, i.v - 1, [&i](const MySet &u) {
                        u.st2->insert(i.x);
                    });
                break;
                case Opt::query: {
                    bool flag = true;
                    auto &u = seg_tree.query(i.u - 1), &v = seg_tree.query(i.v - 1);
                    for (auto &j : *u.st) {
                        if (v.st->find(j) == v.st->end()) {
                            flag = false;
                            break;
                        }
                    }
                    res.push_back(flag);
                }
            }
        }
        return res;
    }

    uint T = 25;

    mt19937_64 rnd(random_device{}());

    bool the_first_time = true;
    vector<bool> res;
    while (T--) {
        auto it = res.begin();
        unordered_map<uint, tuple<bool, ull>> mp;
        unordered_set<ull> st;
        st.insert(0);
        array<SegTree<MyInt>, 2> seg_tree{
            SegTree<MyInt>{config.n, vector<MyInt>(config.n).begin()},
            SegTree<MyInt>{config.n, vector<MyInt>(config.n).begin()},
        };
        array<SegTree<MyInt2>, 2> seg_tree_siz{
            SegTree<MyInt2>{config.n, vector<MyInt2>(config.n).begin()},
            SegTree<MyInt2>{config.n, vector<MyInt2>(config.n).begin()}
        };
        for (auto &i : config.opts) {
            ull tmp = 0;
            switch (i.type) {
                case Opt::insert:
                    if (mp.find(i.x) == mp.end()) {
                        mp[i.x] = {rnd() & 1, rnd()};
                        st.insert(get<1>(mp[i.x]));
                    }
                    tmp = get<1>(mp[i.x]);
                    seg_tree[get<0>(mp[i.x])]
                        .modify(i.u - 1, i.v - 1, [tmp](MyInt &u){
                            u.val ^= tmp;
                    });
                    seg_tree_siz[get<0>(mp[i.x])]
                        .modify(i.u - 1, i.v - 1, [tmp](MyInt2 &u){
                            u.val++;
                    });
                break;
                case Opt::erase:
                    tmp = get<1>(mp[i.x]);
                    seg_tree[get<0>(mp[i.x])]
                        .modify(i.u - 1, i.v - 1, [tmp](MyInt &u){
                            u.val ^= tmp;
                    });
                    seg_tree_siz[get<0>(mp[i.x])]
                        .modify(i.u - 1, i.v - 1, [tmp](MyInt2 &u){
                            u.val--;
                    });
                break;
                case Opt::query: {
                    const bool flag =
                    st.end() != st.find(
                        seg_tree[0].query(i.u - 1).val ^ seg_tree[0].query(i.v - 1).val
                    ) && st.end() != st.find(
                        seg_tree[1].query(i.u - 1).val ^ seg_tree[1].query(i.v - 1).val
                    ) && seg_tree_siz[0].query(i.u - 1).val <= seg_tree_siz[0].query(i.v - 1).val
                    && seg_tree_siz[1].query(i.u - 1).val <= seg_tree_siz[1].query(i.v - 1).val;
                    if (the_first_time) {
                        res.push_back(flag);
                    }else {
                        *it = *it || flag;
                    }
                }
            }
        }
        the_first_time = false;
    }
    return res;
}

void data_gen() {
    freopen("temp.in", "w", stdout);
    mt19937 rnd(random_device{}());
    uint n = rnd() % 2000 + 1, m = rnd() % 2000 + 1;
    printf("%u %u\n", n, m);
    multiset<tuple<uint, uint, uint>> mst;
    for (uint i = 0; i < m; i++) {
        uint type = rnd() % 3;
        switch (type) {
            case 2:{
                if (!mst.empty()) {
                    auto temp = mst.begin();
                    auto [l, r, x] = *temp;
                    printf("2 %u %u %u\n", l, r, x);
                    mst.erase(temp);
                    break;
                }
            }
            case 0: {
                uint l = rnd() % n + 1, r = rnd() % n + 1, x = rnd() % 100000 + 1;
                l > r ? swap(l, r) : static_cast<void>(0);
                mst.insert({l, r, x});
                printf("1 %u %u %u\n", l, r, x);
                break;
            }
            case 1: {
                uint l = rnd() % n + 1, r = rnd() % n + 1;
                printf("3 %u %u\n", l, r);
            }
        }
    }
    fclose(stdout);
}