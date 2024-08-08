//
// Created by kibi on 2022/10/17.
//

#ifndef STU_MYHEAD_H
#define STU_MYHEAD_H

#include <bits/stdc++.h>

using std::vector, std::tuple, std::pair, std::stack,
        std::runtime_error,
        std::priority_queue,
        std::max, std::min,
        std::string;
using ll = long long;

static const int Mod = 1000000007;

void add(int &x, int y){
    x = (x + y) % Mod;
}

int sub(int x, int y){
    return (int)((ll)x * y);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}

void read(long long &x){
    long long s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}

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


class DSUNode{
    DSUNode *fa;
public:
    explicit DSUNode(int val):fa(this), val(val){}
    int val;

    DSUNode* find(){
        return fa == this ? this : fa->find();
    }

    void merge(DSUNode *v){
        fa = v;
    }
};

const int Size = 1000005;
static const int MaxN = 500005;
class Graph{
    class Edge{
    public:
        int v, w;
        Edge *nxt;
    };

    std::vector<Edge*> head;

public:
    explicit Graph(int n):head(n + 1, nullptr){}

    void add_edge(int u, int v, int w, bool flag = false){
        head[u] = new Edge{v, w, head[u]};

        flag ? add_edge(v, u, w) : (void)0;
    }

    Edge* begin(int u){
        return head[u];
    }
};

// incomplete Graph with iterator
/*
class Graph{
    class Edge{
    public:
        int v;
        Edge *nxt;
    };

    vector<Edge*> head;

public:
    class iterator{
        Edge *now;
        Graph* obj;
    public:
        iterator(Graph* ptr, Edge *now):obj(ptr), now(now){}

        iterator():obj(nullptr), now(nullptr){}

        void operator++(){
            now = now->nxt;
        }

        void operator++(Edge *i){
            now = now->nxt;
        }

        int operator * () const{
            return now->v;
        }

        bool operator != (const iterator &it){
            return it.now != now;
        }

        bool operator == (const iterator &it){
            return it.now == now;
        }
    };

    Graph(int n):head(n){}

    void add_edge(int u, int v){
        head[u] = new Edge{v, head[u]};
    }

    Edge* begin(int u){
        return head[u];
    }
};
*/

class Lca {
    int fa[Size][20]{}, dep[Size]{};
    Graph *g;
    void f(int u) {
        for (int i = 1; (1 << i) <= dep[u]; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        }
        for (auto i = g->begin(u); i; i = i->nxt) {
            static int v;
            v = i->v;
            if (v != fa[u][0]) {
                fa[v][0] = u;
                dep[v] = dep[u] + 1;
                f(v);
            }
        }
    }

public:
    explicit Lca(Graph *gT, int u = 1) {
        dep[u] = 1, fa[u][0] = 1;
        g = gT;
        f(u);
    }
    int getLca(int x, int y) {
        if (x == y) {
            return x;
        }
        if (dep[x] < dep[y]) {
            std::swap(x, y);
        }

        for (int i = log(dep[x] - dep[y]) / log(2); i >= 0; i--) {
            if (dep[fa[x][i]] >= dep[y]) {
                x = fa[x][i];
            }
            if (x == y) {
                return x;
            }
        }
        for (int i = log(dep[x]) / log(2); i >= 0; i--) {
            if (fa[x][i] != fa[y][i]) {
                x = fa[x][i], y = fa[y][i];
            }
        }
        return fa[x][0];
    }
    int getDis(int u, int v, int lca = -1) {
        if (lca == -1) {
            lca = getLca(u, v);
        }
        return dep[u] + dep[v] - 2 * dep[lca];
    }
    int getFa(int x) {
        return fa[x][0];
    }
    int _getDep(int x) {
        return dep[x];
    }
};

std::mt19937 rnd(std::random_device{}());

class __not_used_FhqTreap{
    static const int Size = 1000005;
    int siz[Size], ls[Size], rs[Size], val[Size], pri[Size], cnt;
    unsigned int rnk[Size];
    void updSize(int u){
        siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
    }
public:
    int root;
    int addNode(int v, int w){
        cnt++;
        siz[cnt] = 1, val[cnt] = v, pri[cnt] = w, rnk[cnt] = rnd();
        return cnt;
    }
    void split(int &x, int &y, int k, int pos){
        if(!pos){
            x = y = 0;
        }else{
            if(pri[pos] <= k){
                x = pos;
                split(rs[pos], y, k, rs[pos]);
            }else{
                y = pos;
                split(x, ls[pos], k, ls[pos]);
            }
            updSize(pos);
        }
    }
    //    TODO Do not use it, need to repair
    void splitBySiz(int &x, int &y, int k, int pos){
        if(!pos){
            x = y = 0;
        }else{
            if(siz[ls[pos]] >= k){
                y = pos;
                split(x, ls[pos], k, ls[pos]);
            }else{
                x = pos;
                split(rs[pos], y, k, rs[pos]);
            }
            updSize(pos);
        }
    }
    int merge(int x, int y){
        if(!(x&&y)){
            return x+y;
        }
        if(rnk[x] < rnk[y]){
            rs[x] = merge(rs[x], y);
            updSize(x);
            return x;
        }else{
            ls[y] = merge(x, ls[y]);
            updSize(y);
            return y;
        }
    }
    int delLast(){
        int now = root;
        while(rs[now]){
            now = rs[now];
        }
        static int tem, rootT;
        split(rootT, tem, pri[now]-1, root);
        root = rootT;
        return pri[tem];
    }
    int delFirst(){
        int now = root;
        while(ls[now]){
            now = ls[now];
        }
        static int tem, rootT;
        split(tem, rootT, pri[now], root);
        root = rootT;
        return pri[tem];
    }
    int delRnk(int k){
        static int a, b, c, tem;
        splitBySiz(a, b, k-1, root);
        splitBySiz(tem, c, 1, b);
        root = merge(a, c);
        return pri[b];
    }

    void add(int x){
        static int a, b;
        split(a, b, x, root);
        root = merge(merge(a, addNode(0, x)), b);
    }
    int queryByRnk(int k){

        /*
         * another way, but need to fix
        static int a, b, c, tem, res;
        splitBySiz(a, b, k-1, root);
        splitBySiz(tem, c, 1, b);
        res = pri[tem];
        root = merge(a, merge(tem, c));
        return res;
        */

        static int now;
        now = root;
        while(true){
            if(siz[ls[now]] >= k){
                now = ls[now];
            }else if(siz[ls[now]] + 1 == k){
                return pri[now];
            }else{
                k -= siz[ls[now]] + 1;
                now = rs[now];
            }
        }
    }

};

class FhqTreapNode {
    using Node = FhqTreapNode;

    unsigned int rnk;
    FhqTreapNode *ls, *rs;
    int siz;

    FhqTreapNode(unsigned int rnk, int val, int id) : rnk(rnk), ls(nullptr), rs(nullptr), val(val), siz(1), id(id) {}

public:
    int id;
    const int val;

    static Node *new_node(int id, int val) {
        return new Node{rnd(), val, id};
    }

    void upd_siz() {
        siz = 1 + (ls ? ls->siz : 0) + (rs ? rs->siz : 0);
    }

    bool operator<=(const int &t) const {
        return val <= t;
    }

    bool operator<(const Node &t) const {
        return rnk < t.rnk;
    }

    static int size(Node *u) {
        return u ? u->siz : 0;
    }

    void split(int k, Node *&l, Node *&r) {
        if (val <= k) {
            l = this;
            rs ? rs->split(k, rs, r) : (void) (r = nullptr);
        } else {
            r = this;
            ls ? ls->split(k, l, ls) : (void) (l = nullptr);
        }
        upd_siz();
    }

    void split_(int k, Node *&l, Node *&r) {
        stack<tuple<Node *, Node *&, Node *&>> stk;
        stack<Node *> changed;
        stk.emplace(this, l, r);
        while (!stk.empty()) {
            auto [now, tl, tr] = stk.top();
            changed.emplace(now);
            stk.pop();
            if (*now <= k) {
                tl = now;
                now->rs ? stk.emplace(now->rs, now->rs, tr) : (void) (tr = nullptr);
            } else {
                tr = now;
                now->ls ? stk.emplace(now->ls, tl, now->ls) : (void) (tl = nullptr);
            }
        }
        while (!changed.empty()) {
            changed.top()->upd_siz();
            changed.pop();
        }
    }

    static Node *merge(Node *l, Node *r) {
        if (!(l && r)) {
            return l ? l : r;
        } else if (*l < *r) {
            l->rs = merge(l->rs, r);
            l->upd_siz();
            return l;
        } else {
            r->ls = merge(l, r->ls);
            r->upd_siz();
            return r;
        }
    }

    static Node *merge_(Node *&l, Node *&r) {
        stack<tuple<Node *&, Node *&, Node *&>> stk;// l, r, res
        stack<Node *> changed;
        Node *res = nullptr;
        stk.emplace(l, r, res);
        while (stk.empty()) {
            auto [tl, tr, tres] = stk.top();
            stk.pop();
            if (!(tl && tr)) {
                tres = tl ? tl : tr;
            } else if (tl < tr) {
                stk.emplace(tl->rs, tr, tl->rs);
                changed.emplace(tl);
                tres = tl;
            } else {
                stk.emplace(tl, tr->ls, tr->ls);
                changed.emplace(tr);
                tres = tr;
            }
        }
        return res;
    }

    Node *query_by_rnk(int k) {
        if (size(ls) == k - 1) {
            return this;
        } else if (ls && size(ls) > k - 1) {
            return ls->query_by_rnk(k);
        } else {
            return rs->query_by_rnk(k - size(ls) - 1);
        }
    }

    Node *query_by_rnk_(int k) {
        auto now = this;
        while (k - 1 != size(ls)) {
            if ((ls ? ls->siz : 0) > k - 1) {
                now = ls;
            } else {
                k -= size(ls) + 1;
                now = rs;
            }
        }
        return now;
    }

    Node *separate_son(){
        Node *tl = ls, *tr = rs;
        ls = nullptr, rs = nullptr, siz = 1;
        return merge(tl, tr);
    }
};

class FhqTreapTools{
    using Node = FhqTreapNode;
public:
    static Node* add_node(Node *rt, Node* node){
        if(!rt){
            return node;
        }
        Node *a = nullptr, *b = nullptr;
        rt->split(node->val, a, b);
        a = Node::merge(a, node);
        return Node::merge(a, b);
    }

    static Node* remove_node(Node *&rt, int k){
        Node *a = nullptr, *b = nullptr, *res = nullptr;
        rt->split(k, a, b);
        a->split(k - 1, a, res);
        a = Node::merge(a, res->separate_son());
        rt = Node::merge(a, b);
        return res;
    }

    static int query_rnk(Node *rt, int k){
        Node *a = nullptr, *b = nullptr;
        rt->split(k - 1, a, b);
        int res = Node::size(a) + 1;
        Node::merge(a, b);
        return res;
    }

    static Node* query_pre(Node *rt, int k){
        Node *a = nullptr, *b = nullptr;
        rt->split(k - 1, a, b);
        Node *res = a->query_by_rnk(Node::size(a));
        Node::merge(a, b);
        return res;
    }

    static Node* query_suc(Node *rt, int k){
        Node *a = nullptr, *b = nullptr;
        rt->split(k, a, b);
        Node *res = b->query_by_rnk(1);
        Node::merge(a, b);
        return res;
    }
};

// TODO classes Trie and AC are not complete, they may have some mistake, maybe another way to make it
// TODO class not update after change Graph
// TODO why does Trie require Graph

class Trie{
    Graph g{};
    int cntNode, cntWord, rt;
    char c[Size]{};
    int y[Size][26]{}, id[Size]{}, fa[Size]{};

public:
    Trie(){
        rt = 0;
        c[cntNode++] = 0;
    }

    int addWord(const char *word){
        int u = rt;
        for(int i = 0; word[i]; i++){
            char str = word[i] - 'a';
            if(y[u][str]){
                u = y[u][str];
            }else{
                g.addEdge(u, cntNode++);
                y[u][str] = g.get(g.begin(u));
                fa[y[u][str]] = u;
                u = y[u][str];
                c[u] = str;
            }
        }
        id[u]++;
        if(!id[u]){
            id[u] = ++cntWord;
        }
        return u;
    }
    int getFa(int x){
        return fa[x];
    }

    int queryPos(const char *str, int u) {
        for(int i = 0; str[i]; i++){
            if(!y[u][str[i]-'a']){
                return -1;
            }
            u = y[u][str[i]-'a'];
        }
        return u;
    }

    int queryPos(char str, int u) {
        return y[u][str] ? y[u][str] : -1;
    }

    int getVal(int x){
        return c[x];
    }

    int isEnd(int u){
        return id[u];
    }

    int _addId(){
        return cntWord++;
    }

    int _getCntWord(){
        return cntWord;
    }

    int begin(int u){
        return g.begin(u);
    }

    int next(int u){
        return g.next(u);
    }

    int get(int u){
        return g.get(u);
    }
};

class AC{
    Trie tr;
    int nxt[Size]{};
    std::vector<int> sameId[205];
    int getFail(int u){
        static int c, now, res;
        c = tr.getVal(u);
        now = nxt[tr.getFa(u)];
        while(now != -1 && tr.queryPos(c, now) == -1 && now){
            now = nxt[now];
        }
        if(now == -1){
            return 0;
        }
        res = tr.queryPos(c, now);
        res = res == -1 ? 0 : res;
        return res;
    }
    void f(int u){
        for(int i = tr.begin(u); i; i = tr.next(i)){
            static int str, now;
            str = tr.getVal(tr.get(i));
            now = tr.queryPos(str, u);
            nxt[now] = nxt[now] !=-1 ? nxt[now] : getFail(now);
            f(now);
        }
    }
public:
    int ans[Size]{};
    AC(){
        memset(nxt, -1, sizeof nxt);
    }
    void addWord(char *word){
        static int tem, now, beforeCnt;
        static bool flag;
        now = 0;
        beforeCnt = tr._getCntWord();
        tem = tr.addWord(word);
        flag = beforeCnt == tr._getCntWord();
        if(flag){
            sameId[tr.isEnd(tem)].push_back(tr._addId());
        }
    }
    void build(){
        f(0);
    }
    void match(const char *str, int r = -1){
        static int now;
        now = 0;
        memset(ans, 0, sizeof ans);
        for(int i = 0; r == -1 ? str[i]: i < r; i++){
            static int c, tem;
            c = str[i] - 'a';
            while(tr.queryPos(c, now) == -1 && now != 0){
                now = nxt[now];
            }
            now = tr.queryPos(c, now);
            tem = now;
            while(tem){
                int id = tr.isEnd(tem);
                if(id){
                    ans[id]++;
                    for(auto &j : sameId[id]){
                        ans[j]++;
                    }
                }
                tem = nxt[tem];
            }
        }
    }
};

class KMP {
    class Pat {
        const size_t len, n;
        const vector<int> str;
        vector<vector<int>> nxt;

        class Res {
        public:
            int num{0};
            vector<int> pos{vector<int>(0)};
        };

    public:
        Pat(vector<int> str, int n) : str(str),
                                      n(n),
                                      len(str.size()),
                                      nxt(len + 1, vector<int>(n)) {
            if (str.empty()) {
                throw runtime_error("ErrorSize!");
            }

            int pre = 0;
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < n; j++) {
                    nxt[i][j] = nxt[pre][j];
                }
                nxt[i][str[i]] = i + 1;
                pre = nxt[pre][str[i]];
            }
            for (int j = 0; j < n; j++) {
                nxt[len][j] = nxt[pre][j];
            }
        }

        Res search(vector<int> txt) {
            size_t len_txt = txt.size();
            int stat = 0;
            Res res;
            for (int i = 0; i < len_txt; i++) {
                if (txt[i] >= n) {
                    stat = 0;
                } else {
                    stat = nxt[stat][txt[i]];
                    if (stat == len) {
                        res.num++;
                        res.pos.emplace_back(i);
                    }
                }
            }
            return res;
        }
    };
};

class Manacher{

    int readStr(char *c){
        int tem = getchar();
        while(tem < 'a' || 'z' < tem){
            tem =getchar();
        }
        static int i = 0;
        while('a' <= tem && tem <= 'z'){
            c[i++] = (char)tem;
            tem = getchar();
        }
        return i;
    }

    int main(){
        static char raw[24000005], str[46000005];
        static int len = readStr(raw+1), d[46000005], ans = 0;
        str[0] = '#';
        for(int i = 1; i <= len; i++){
            str[i*2] = raw[i];
            str[i*2 - 1] = '*';
        }
        str[len*2+1] = '*';
        len = len*2+1;
        for(int i = 1; i <= len; i++){
            static int mid = 0, r = 0;
            if(i <= r){
                d[i] = std::min(d[(mid<<1)-i], r-i+1);
            }
            while(str[i - d[i]] == str[i + d[i]] && i + d[i] <= len){
                ++d[i];
            }
            if(d[i] + i > r){
                r = d[i] + i - 1, mid = i;
            }
            if(d[i] > ans){
                ans = d[i];
            }
        }
        printf("%d", ans-1);
        return 0;
    }
public:
    Manacher(){
        main();
    }

};

class Matrix{
    size_t n, m;
    vector<vector<int>> data;

public:
    Matrix(size_t n, size_t m):n(n), m(m), data(n, vector<int>(m)){}
    explicit Matrix(size_t n):n(n), m(n), data(n, vector<int>(n)){
        for(int i = 0; i < n; i++){
            data[i][i] = 1;
        }
    }
    explicit Matrix(vector<vector<int>> &x):data(x), n(x.size()), m(x.front().size()){}

    Matrix operator * (const Matrix &b){
        if(m != b.n){
            throw runtime_error("Error sub Matrix with wrong length!");
        }
        Matrix res(n, b.m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < m; k++) {
                    add(res.data[i][j], sub(data[i][k], b.data[k][j]));
                }
            }
        }
        return res;
    }

    void operator *= (const Matrix &b){
        *this = (*this) * b;
    }

    pair<int, int> size(){
        return {n, m};
    }

    int get(int x, int y){
        if(x >= n || y >= m || x < 0 || y < 0){
            throw runtime_error("Error with wrong index!");
        }
        return data[x][y];
    }
};

class HuffmanTree{
    class Node{
    public:
        int dep;
        ll val, w;
        vector<Node*> son;

        class Cmp{
        public:
            bool operator ()(const Node *a, const Node *b){
                return a->val == b->val ? a->dep > b->dep : a->val > b->val;
            }
        };
    };

public:
    Node *rt;

    HuffmanTree(const ll *w, int n, int k = 2){
        priority_queue<Node*, vector<Node*>, Node::Cmp> q;
        for(int i = 0; i < n; i++){
            q.emplace(new Node{0, w[i], 0});
        }

        int sz;
        sz = (n - 1) % (k - 1) != 0 ? n - ((n - 1) % (k - 1)) + (k - 1) : n;
        for(int i = n; i < sz; i++){
            q.emplace(new Node{0, 0, 0});
        }

        while(q.size() >= k){
            auto temp = new Node{0, 0, 0};
            temp->son.resize(k);
            for(int i = 0; i < k; i++){
                temp->son[i] = q.top();
                temp->dep = max(temp->dep, temp->son[i]->dep + 1);
                temp->val = temp->val + temp->son[i]->val;
                temp->w += temp->son[i]->w + temp->son[i]->val;
                q.pop();
            }
            q.emplace(temp);
        }

        rt = q.top();
        q.pop();
    }
};

// Not used for now
// TODO finish Integer
// not work well with negative, maybe have some mistake
class Int{
    /*
     * use vector
     * only support + and pow10
     * can output as a string
     * not support negative
     * */

    vector<uint> val;

public:
    Int():val{0}{}
    explicit Int(uint x){
        while(x){
            val.emplace_back(x % 10);
            x /= 10;
        }
    }

    Int operator+(const Int& other) const {
        Int result;
        result.val.resize(1 + max(other.val.size(), val.size()));
        for(size_t i = 0; i < result.val.size() - 1; ++i){
            result[i + 1] = (result[i] + other[i] + (*this)[i]) / 10;
            result[i] = (result[i] + other[i] + (*this)[i]) % 10;
        }
        result.removeLeadingZeros();
        return result;
    }

    Int pow10(uint k){
        Int result;
        result.val.resize(k);
        for(auto &i : val){
            result.val.emplace_back(i);
        }
        return result;
    }

    string to_string() const{
        string s;
        s.reserve(val.size());
        for(auto &i : val){
            s.push_back((char)(i + '0'));
        }
        reverse(s.begin(), s.end());
        return s;
    }

private:
    void removeLeadingZeros(){
        while(!val.empty() && val.back() == 0){
            val.pop_back();
        }
    }

    uint operator[](uint i) const{
        return i < val.size() ? val[i] : 0;
    }

    uint& operator[](uint i){
        return val[i];
    }
};

template<std::size_t n>
class Integer{
    /*
     * use bitset
     * n as sizeof bitset
     * support + - * / and pow2
     * also support == and >
     * use Int to output as a string
     * not work well with negative, wait to fix
     * */

    std::bitset<n> val;
    bool sign;

public:
    Integer() : val(0), sign(false){}
    explicit Integer(long x) : val(std::abs(x)), sign(std::abs(x) != std::abs(x)){}
    explicit Integer(string x){
        if(x.empty()){
            throw std::invalid_argument("Empty string!");
        }

        Integer<n> temp;

        sign = (x[0] == '-');
        if(x[0] == '+' || x[0] == '-'){
            x[0] = '0';
        }

        for(auto &i : x){
            temp = (temp * Integer<n>(10)) + Integer<n>(i - '0');
            if(i < '0' || '9' < i){
                throw std::invalid_argument("Error char in string!");
            }
        }

        temp.sign = sign;
        *this = temp;
    }

    Integer<n> operator+(const Integer<n>& other) const {
        if(sign == other.sign){
            Integer result;
            result.sign = sign;
            for(size_t i = 0; i < n - 1; ++i){
                result[i + 1] = (((short)val[i] + other[i] + result[i]) > 1);
                result[i] = val[i] ^ other[i] ^ result.val[i];
            }
            if((short)result[n - 1] + val[n - 1] + other[n - 1] > 1){
                throw std::out_of_range("The integer is too big!");
            }
            result[n - 1] = result[n - 1] + val[n - 1] + other[n - 1];
            return result;
        }

        if(sign) {
            return *this - (-other);
        }
        return other - (-*this);
    }

    Integer<n> operator-(const Integer<n>& other) const {
        if(sign == other.sign){
            if(*this == other){
                return Integer<n>{};
            }
            Integer<n> result;
            result.sign = (other > *this);
            const Integer<n>& larger = (result.sign ^ sign ^ 1) ? *this : other;
            const Integer<n>& smaller = (result.sign ^ sign ^ 1) ? other : *this;
            bool borrow = false;
            for(size_t i = 0; i < n; ++i){
                result[i] = larger[i] ^ smaller[i] ^ borrow;
                borrow = (smaller[i] + borrow > larger[i]);
            }
            return result;
        }
        return *this + (-other);
    }

    Integer<n> operator*(const Integer<n>& other) const {
        Integer<n> result;
        result.sign = (sign != other.sign);
        for(size_t i = 0; i < n; i++){
            if(other[i]){
                result = result + ((*this).pow2(i));
            }
        }
        return result;
    }

    Integer<n> operator/(const Integer<n>& other) const {
        if(other == Integer<n>{}){
            throw std::invalid_argument("Division by zero!");
        }else if(other == Integer<n>(1)){
            return *this;
        }
        Integer<n> l(0), r(*this);
        r.val >>= 1;
        while(r > l){ // avoid l <= r here
            Integer<n> mid = l + r;
            mid.val >>= 1;
            try{
                auto tem = other * mid;
                if(tem > *this){
                    r = mid - Integer(1);
                }else{
                    l = mid + Integer(1);
                }
            }catch(std::out_of_range){
                r = mid - Integer(1);
            }
        }

        // to avoid l <= r which cause check to l == r every time
        Integer<n> mid = l + r;
        mid.val >>= 1;
        try{
            auto tem = other * mid;
            if(tem > *this){
                r = mid - Integer(1);
            }else{
                l = mid + Integer(1);
            }
        }catch(std::out_of_range){
            r = mid - Integer(1);
        }

        r.sign = sign ^ other.sign;

        return r;
    }

    Integer<n> pow2(size_t k) const {
        if(k > n){
            throw std::out_of_range("The k is too big!");
        }
        Integer<n> result = *this;
        for(uint i = 0; i < k; ++i){
            if(result.val[n - i - 1] == true){
                throw std::out_of_range("The k is too big!");
            }
        }
        result.val <<= k;
        return result;
    }

    string to_string(){
        Int base(1), res;
        for(uint i = 0; i < n; i++){
            if(val[i]){
                res = res + base;
            }
            base = base + base;
        }
        string ret;
        if(sign){
            ret.push_back('-');
        }
        ret.append(res.to_string());
        return ret;
    }

    bool operator == (const Integer<n>& other) const {
        return val == other.val && sign == other.sign;
    }

    bool operator > (const Integer<n>& other) const {
        if(sign != other.sign){
            return other.sign;
        }

        for(int i = n - 1; i >= 0; --i){
            if(val[i] != other[i]){
                return val[i];
            }
        }

        return false;
    }

    Integer<n> operator-() const {
        Integer result = *this;
        result.sign = !sign;
        return result;
    }

private:
    bool operator[](size_t i) const{
        return val[i];
    }

    typename std::bitset<n>::reference operator[](size_t i) {
        return val[i];
    }
};

// gen by AI with a lot of mistake, just not use
/*class Integer {
public:
    // 默认构造函数
    Integer() : digits(1, 0), sign(true) {}

    // 从字符串构造
    Integer(const std::string& number) {
        if (number.empty()) {
            throw std::invalid_argument("Empty string");
        }
        sign = (number[0] != '-');
        size_t start = (number[0] == '+' || number[0] == '-') ? 1 : 0;
        digits.reserve(number.size() - start);
        for (size_t i = start; i < number.size(); ++i) {
            if (!isdigit(number[i])) {
                throw std::invalid_argument("Invalid character in number");
            }
            digits.push_back(number[i] - '0');
        }
        std::reverse(digits.begin(), digits.end());
        removeLeadingZeros();
    }

    // 打印大整数
    void print() const {
        if (digits.empty()) {
            std::cout << "0";
        } else {
            if (!sign) {
                std::cout << "-";
            }
            for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
                std::cout << *it;
            }
        }
    }

    // 高精度加法
    Integer operator+(const Integer& other) const {
        if (sign == other.sign) {
            Integer result;
            result.sign = sign;
            size_t size = std::max(digits.size(), other.digits.size());
            result.digits.resize(size, 0);
            int carry = 0;
            for (size_t i = 0; i < size; ++i) {
                int sum = carry;
                if (i < digits.size()) {
                    sum += digits[i];
                }
                if (i < other.digits.size()) {
                    sum += other.digits[i];
                }
                carry = sum / 10;
                result.digits[i] = sum % 10;
            }
            if (carry) {
                result.digits.push_back(carry);
            }
            return result;
        }
        // Handle different signs
        if (sign) {
            return *this - (-other);
        }
        return other - (-*this);
    }

    // 高精度减法
    Integer operator-(const Integer& other) const {
        // Handle signs and absolute values
        if (sign == other.sign) {
            if (*this == other) {
                return Integer("0");
            }
            bool resultSign = *this > other;
            const Integer& larger = resultSign ? *this : other;
            const Integer& smaller = resultSign ? other : *this;
            Integer result;
            result.sign = resultSign;
            result.digits.resize(larger.digits.size(), 0);
            int borrow = 0;
            for (size_t i = 0; i < larger.digits.size(); ++i) {
                int diff = larger.digits[i] - borrow;
                if (i < smaller.digits.size()) {
                    diff -= smaller.digits[i];
                }
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                result.digits[i] = diff;
            }
            result.removeLeadingZeros();
            return result;
        }
        return *this + (-other);
    }

    // 高精度乘法
    Integer operator*(const Integer& other) const {
        Integer result;
        result.sign = (sign == other.sign);
        result.digits.resize(digits.size() + other.digits.size(), 0);
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size(); ++j) {
                int prod = digits[i] * other.digits[j] + result.digits[i + j] + carry;
                carry = prod / 10;
                result.digits[i + j] = prod % 10;
            }
            if (carry) {
                result.digits[i + other.digits.size()] += carry;
            }
        }
        result.removeLeadingZeros();
        return result;
    }

    // 高精度除法
    // maybe wrong
    Integer operator/(const Integer& other) const {
        if (other == Integer("0")) {
            throw std::invalid_argument("Division by zero");
        }
        Integer result;
        result.sign = (sign == other.sign);
        Integer divisor = other;
        divisor.sign = true; // Ensure divisor is positive

        Integer current;
        current.digits.clear();
        for (size_t i = digits.size(); i-- > 0;) {
            current.digits.push_back(digits[i]);
            current.removeLeadingZeros();

            int quotient = 0;
            while (current >= divisor) {
                current = current - divisor;
                ++quotient;
            }
            result.digits.push_back(quotient);
        }
        std::reverse(result.digits.begin(), result.digits.end());
        result.removeLeadingZeros();
        return result;
    }

    // 高精度取模
    // maybe wrong
    Integer operator%(const Integer& other) const {
        if (other == Integer("0")) {
            throw std::invalid_argument("Division by zero");
        }
        Integer divisor = other;
        divisor.sign = true; // Ensure divisor is positive

        Integer current;
        current.digits.clear();
        for (size_t i = digits.size(); i-- > 0;) {
            current.digits.push_back(digits[i]);
            current.removeLeadingZeros();

            while (current >= divisor) {
                current = current - divisor;
            }
        }
        return current;
    }

    bool operator==(const Integer& other) const {
        return sign == other.sign && digits == other.digits;
    }

    bool operator>(const Integer& other) const {
        if (sign != other.sign) {
            return sign;
        }
        if (digits.size() != other.digits.size()) {
            return (sign == (digits.size() > other.digits.size()));
        }
        for (size_t i = digits.size(); i-- > 0;) {
            if (digits[i] != other.digits[i]) {
                return (sign == (digits[i] > other.digits[i]));
            }
        }
        return false;
    }

    bool operator>=(const Integer& other) const {
        return *this > other || *this == other;
    }

    // 负数化简
    Integer operator-() const {
        Integer result = *this;
        result.sign = !sign;
        return result;
    }

private:
    std::vector<int> digits; // 存储数字的向量
    bool sign; // 符号，true 表示正数，false 表示负数

    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.empty()) {
            sign = true;
        }
    }
};*/

class Integer128 {

    /*
     * int128 based on string and bitset ?
     * */

    const static string basic[128];

    using lll = std::bitset<128>;
    lll val;

public:
    Integer128() : val(0) {}
    explicit Integer128(int n) : val(n) {}
    explicit Integer128(ll n) : val(n) {}
    explicit Integer128(lll n) : val(n) {}

    Integer128 operator+(const Integer128 &b) {
        lll res(0);
        for (int i = 0; i < 127; i++) {
            res[i + 1] = ((val[i] + b.val[i] + res[i]) > 1);
            res[i] = res[i] ^ val[i] ^ b.val[i];
        }
        return Integer128(res);
    }

    bool operator<(const Integer128 &b) const {
        for (int i = 127; i >= 0; i--) {
            if (val[i] < b.val[i]) {
                return true;
            } else if (val[i] > b.val[i]) {
                return false;
            }
        }
        return false;
    }

    Integer128 pow_2(int p) {
        return Integer128(val << p);
    }

    string to_dec() {
        string res = "0000000000000000000000000000000000000000";
        for(int i = 0; i < 128; i++){
            if(val[i]){
                for(int j = 0; j < basic[i].size(); j++){
                    res[j] = (char)(res[j] + (basic[i][j] - '0'));
                    while(res[j] > '9') {
                        res[j] -= 10;
                        res[j + 1] += 1;
                    }
                }
                for(auto j = basic[i].size(); j < 128; j++){
                    if(res[j] < '9'){
                        break;
                    }
                    while(res[j] > '9') {
                        res[j] -= 10;
                        res[j + 1] += 1;
                    }
                }
            }
        }
        return res;
    }
};

const string Integer128::basic[128] = {
        "1",
        "2",
        "4",
        "8",
        "61",
        "23",
        "46",
        "821",
        "652",
        "215",
        "4201",
        "8402",
        "6904",
        "2918",
        "48361",
        "86723",
        "63556",
        "270131",
        "441262",
        "882425",
        "6758401",
        "2517902",
        "4034914",
        "8068838",
        "61277761",
        "23445533",
        "46880176",
        "827712431",
        "654534862",
        "219078635",
        "4281473701",
        "8463847412",
        "6927694924",
        "2954399858",
        "48196897171",
        "86383795343",
        "63767491786",
        "274359834731",
        "449609778472",
        "888318557945",
        "6777261159901",
        "2555523209912",
        "4011156408934",
        "8022203906978",
        "61444068129571",
        "23888027348153",
        "46677144786307",
        "823553884737041",
        "656017679474182",
        "213124359949265",
        "4262486099985211",
        "8425863189971522",
        "6940737269953054",
        "2990474529917009",
        "48918490589341081",
        "86936981079782063",
        "63972973049575027",
        "278558570881511441",
        "447117151673032882",
        "884324303257064675",
        "6796486064051292511",
        "2593963129003485032",
        "4097837248106861164",
        "8085774586302733229",
        "61615590737044764481",
        "23230191474188439863",
        "46460283849267968737",
        "829214676985259375741",
        "658528253971509741592",
        "217156507853018592095",
        "4243031147170261950811",
        "8486062284341423811632",
        "6963125469682846632274",
        "2937240929375692374449",
        "48745808587413956498881",
        "86590716175926813987773",
        "63191432341952736875557",
        "272838646828154727511151",
        "445676392756309454132203",
        "880353785413708909264406",
        "6716074719264169185298021",
        "2532149438529229361587142",
        "4074288966158548723075384",
        "8049467933307196556041769",
        "61889259766043831131824391",
        "23679509533186672262658683",
        "46259118176263355425217377",
        "825093263435276019405247451",
        "650187427860543128900584903",
        "211265944731096246910079816",
        "4224219984720835829300497321",
        "8448428979450670758700885742",
        "6986946959901251417510671594",
        "2973992919912403824130253099",
        "48578958389348066582604070891",
        "86157917769786123175218041693",
        "63305934539573346241526182297",
        "276009780781576825820523654851",
        "443108571473053750750056219613",
        "886206153847007411411003528336",
        "6735023076941049228220060567621",
        "2570146043992088546540021035352",
        "4051282186895067192190042060705",
        "80034652637911253852810840214101",
        "61068215274932407615630690428202",
        "23027520549874804330370291846504",
        "46044150098759618660641483692118",
        "821882010875193363312928672952261",
        "652675020651387627624856355815423",
        "215251140213665354358613701730946",
        "4205032804262317096073364124708921",
        "8400164618425624183147629248416952",
        "6900229236940358267284358586922915",
        "29104485629906075255696071739548301",
        "48308861358912141501393143478196702",
        "86706733607934282012687286847383514",
        "63512576214978465024275563794767038",
        "270340535288579211484411374994351661",
        "441680070567159522869822649899603233",
        "882271041035309154639754298799316466",
        "6754430820607083092785194875997229231",
        "2519860650214167085471389651995548562",
        "4038731211428225161943669313891196135",
        "80665724228465403238962397266932833601",
        "61231558446921906466935685523974676212",
        "23462017982952812923970371156859253524",
        "46825024975815634856851643203719507058",
        "827501488517303786137132964064381141071"
};

// TODO finish splay
// not finish
/*
class Splay{
    class Node{
    public:
        Node *fa, *ls, *rs;
        int val, cnt, siz;

        void update(){
            siz = cnt + ls->siz + rs->siz;
        }

        bool isLson() const{
            return fa ? fa->ls == this : false;
        }
    };

    Node *rt{nullptr};

public:
    void spin(Node *u){
        if(u->fa == nullptr){
            throw runtime_error("Already been root!");
        }

    }
};
 */

class SparseTable{
    vector<int> f[21], lg;

public:
    template<typename Cmp>
    SparseTable(int n, const int *data, Cmp cmp){
        for(auto &i : f){
            i.resize(n);
        }
        for(int i = 0; i < n; i++){
            f[0][i] = data[i];
        }
        for(int i = 1; i <= 20; i++){
            for(int j = 0; j + (1 << i) - 1 < n; j++){
                f[i][j] = cmp(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
            }
        }
        lg.resize(n + 1);
        for(int i = 2; i <= n; i++){
            lg[i] = lg[i / 2] + 1;
        }
    }

    template<typename Cmp>
    int query(int l, int r, Cmp cmp){
        const int &t = lg[r - l + 1];
        return cmp(f[t][l - 1], f[t][r - (1 << t)]);
    }
};

class MonotonicQueue{
    std::deque<pair<int, int>> q;
    int cnt{0};

public:
    template<typename Cmp>
    void push(int v, Cmp cmp){
        while(!q.empty() && cmp(q.back().second, v)){
            q.pop_back();
        }
        q.emplace_back(++cnt, v);
    }

    void update(int v){
        while(!q.empty() && q.front().first <= v){
            q.pop_front();
        }
    }

    int get() const{
        return q.front().second;
    }
};

#endif//STU_MYHEAD_H
