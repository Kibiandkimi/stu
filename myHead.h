//
// Created by kibi on 2022/10/17.
//

#ifndef STU_MYHEAD_H
#define STU_MYHEAD_H

#include <bits/stdc++.h>

using std::vector, std::pair, std::runtime_error;
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

class FhqTreap{
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
