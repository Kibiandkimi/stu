//
// Created by kibi on 2022/10/17.
//

#ifndef STU_MYHEAD_H
#define STU_MYHEAD_H

#include <bits/stdc++.h>

using std::vector, std::pair, std::runtime_error, std::priority_queue, std::max, std::min, std::string;
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


class Integer {

    const static string basic[128];

    using lll = std::bitset<128>;
    lll val;

public:
    Integer() : val(0) {}
    explicit Integer(int n) : val(n) {}
    explicit Integer(ll n) : val(n) {}
    explicit Integer(lll n) : val(n) {}

    Integer operator+(const Integer &b) {
        lll res(0);
        for (int i = 0; i < 127; i++) {
            res[i + 1] = ((val[i] + b.val[i] + res[i]) > 1);
            res[i] = res[i] ^ val[i] ^ b.val[i];
        }
        return Integer(res);
    }

    bool operator<(const Integer &b) const {
        for (int i = 127; i >= 0; i--) {
            if (val[i] < b.val[i]) {
                return true;
            } else if (val[i] > b.val[i]) {
                return false;
            }
        }
        return false;
    }

    Integer pow_2(int p) {
        return Integer(val << p);
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

const string Integer::basic[128] = {
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
