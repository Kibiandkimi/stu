//
// Created by kibi on 23-11-1.
//

// TODO not finish

#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());

    class Tools{
    public:
        static void read(int &x){
            int s = 0, w = 1, c = getchar();
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

        static int deal(int x){
            return (int)((rnd() % x + x) % x + 1);
        }
    };

    class Graph{
        class Node{
        public:
            int v;
            Node *nxt;
        };

        vector<Node*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(int u, int v, bool flag = true){
            head[u] = new Node{v, head[u]};

            if(!flag){
                return;
            }

            add_edge(v, u);
        }

        Node* begin(int u){
            return head[u];
        }
    };

    class Tarjan{
        class Node{
        public:
            int id, dfn, low, bel;
            bool vis;
        };

        Graph *graph;
        vector<int> num;
        vector<Node> node;

        void dfs(Node *u, Node *fa){
            static int cnt = 0, p = 0;
            static stack<int> stk;
            u->dfn = u->low = ++cnt;
            u->vis = true;
            stk.push(u->id);
            for(auto i = graph->begin(u->id); i; i = i->nxt){
                auto v = &node[i->v];
                if(v == fa){
                    continue;
                }
                if(!v->dfn){
                    dfs(v, u);
                    u->low = min(u->low, v->low);
                }else if(v->vis){
                    u->low = min(u->low, v->dfn);
                }
            }
            if(u->dfn == u->low){
                ++p;
                num.emplace_back(0);
                int x;
                do {
                    x = stk.top();
                    node[x].vis = false;
                    node[x].bel = p;
                    num[p]++;
                } while(x != u->id);
            }

        }

    public:
        Tarjan(int n, int rt, Graph *graph):graph(graph), num(1, 0), node(n + 1){
            for(int i = 1; i <= n; i++){
                node[i].id = i;
                node[i].vis = false;
            }
            dfs(&node[rt], nullptr);
        }
    };

    auto rand = Tools::deal;
    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    static Graph graph(n);
    for(int i = 0; i < m; i++){
        int u, v;
        read(u), read(v);
        graph.add_edge(u, v, true);
    }

    int rt = rand(n);
    Tarjan tarjan(n, rt, &graph);


}

// 24-10-30
// TODO
/*
#include <cctype>
#include <cstdio>
#include <map>
#include <random>
#include <stack>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;

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

using Edge = std::tuple<uint, uint>;

class Config {
public:
    uint n, m;
    vec<Edge> edges;
};

uint solve(const Config&);

int main() {
    auto n = read<uint>(), m = read<uint>();
    Config config{n, m};
    config.edges.reserve(m);
    for (uint i = 0; i < m; i++) {
        auto u = read<uint>(), v = read<uint>();
        config.edges.emplace_back(u, v);
    }
    auto ans = solve(config);
    printf("%u\n", ans);
    return 0;
}

class Node {
public:
    uint id, dfn, low, belongs;
};

class ItGraph{

    class Edge{
    public:
        uint v;
        Edge *nxt;
    };

    class Iterator {
        Edge *nxt;
    public:
        explicit Iterator(Edge *nxt) :nxt(nxt) {}

        bool operator != (const Iterator &other) const {
            return nxt != other.nxt;
        }

        uint operator * () const {
            return nxt->v;
        }

        const Iterator &operator++ () {
            nxt = nxt->nxt;
            return *this;
        }

    };

    class MyList {
        Edge *head;

    public:
        MyList() : head {nullptr} {}
        explicit MyList(Edge* head) : head(head) {}

        Iterator begin() const {
            return Iterator(head);
        }

        static Iterator end() {
            return Iterator(nullptr);
        }
    };

    vec<Edge*> head;

    static void destroy(Edge* ptr) {
        ptr->nxt != nullptr ? destroy(ptr->nxt) : static_cast<void>(0);
        delete ptr;
    }

public:
    explicit ItGraph(size_t n):head(n, nullptr){}

    ~ItGraph() {
        for (auto &i: head) {
            i != nullptr ? destroy(i) : static_cast<void>(0);
        }
    }

    void add_edge(uint u, uint v, bool flag = false){
        head[u] = new Edge{v, head[u]};

        flag ? add_edge(v, u) : static_cast<void>(0);
    }

    MyList begin(uint u){
        return MyList{head[u]};
    }
};

void add(uint &a, uint b) {
    static constexpr uint MOD = 1'000'000'007;
    a = (a + b >= MOD) ? a + b - MOD : a + b;
}

uint add_(uint a, uint b) {
    static constexpr uint MOD = 1'000'000'007;
    return (a + b >= MOD) ? a + b - MOD : a + b;
}

uint sub(uint a, uint b) {
    return static_cast<uint>(1ull * a * b % 1'000'000'007);
}

uint quick_pow(unsigned long long a, uint p) {
    static constexpr uint MOD = 1'000'000'007;
    unsigned long long res = 1;
    while (p) {
        if (p & 1) {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        p >>= 1;
    }
    return static_cast<uint>(res);
}

std::mt19937 rnd(std::random_device{}());

uint solve(const Config& config) {
    ItGraph graph(config.n);
    for (auto &i : config.edges) {
        auto [u, v] = i;
        graph.add_edge(u - 1, v - 1, true);
    }

    vec<Node*> nodes;
    nodes.reserve(config.n);
    for (uint i = 0; i < config.n; i++) {
        nodes.emplace_back(new Node{i, 0, 0});
    }

    uint cnt = 0, cnt2 = 0;
    std::stack<Node*> stk;
    vec<bool> in_stk(config.n);

    auto tarjan = [&cnt, &cnt2, &stk, &in_stk, &nodes, &graph](Node *u, Node *fa, auto &&tarjan) -> void{
        u->dfn = ++cnt;
        u->low = u->dfn;
        in_stk[u->id] = true;
        stk.push(u);
        for (auto i : graph.begin(u->id)) {
            if (nodes[i] == fa) {
                continue;
            }
            if (!nodes[i]->dfn) {
                tarjan(nodes[i], u, tarjan);
                u->low = std::min(u->low, nodes[i]->low);
            } else if (in_stk[i]) {
                u->low = std::min(u->low, nodes[i]->dfn);
            }
        }

        if (u->dfn == u->low) {
            u->belongs = cnt2;
            Node *now;
            do {
                now = stk.top();
                stk.pop();
                now->belongs = cnt2;
                in_stk[now->id] = false;
            } while (now != u);
            cnt2++;
        }
    };

    tarjan(nodes[rnd() % config.n], nullptr, tarjan);

    uint res = 0;

    ItGraph new_graph(cnt2);
    vec<uint> edge_num(cnt2), node_num(cnt2);

    // std::map<std::tuple<uint, uint>, uint> mp;

    for (uint i = 0; i < config.n; i++) {
        node_num[nodes[i]->belongs]++;
        for (auto j : graph.begin(i)) {
            if (nodes[i]->belongs != nodes[j]->belongs) {
                // uint u = nodes[i]->belongs, v = nodes[j]->belongs;
                // if (u > v) {
                //     std::swap(u, v);
                // }
                // if (!mp[{u, v}]) {
                // }

                new_graph.add_edge(nodes[i]->belongs, nodes[j]->belongs);
                // mp[{u, v}]++;
            } else {
                edge_num[nodes[i]->belongs]++;
            }
        }
    }

    for (uint i = 0; i < cnt2; i++) {
        edge_num[i] >>= 1;
    }

    vec<std::tuple<uint, uint>> f(cnt2);
    vec<bool> vis(cnt2);
    vec<uint> tree_edge_sum = edge_num;
    uint m = config.m;

    using std::get;

    auto dfs = [&m, &vis, &new_graph, &edge_num, &node_num, &tree_edge_sum, &res, &f](uint u, auto &&dfs) -> uint {
        for (auto i : new_graph.begin(u)) {
            if (!vis[i]) {
                vis[i] = true;
                tree_edge_sum[u] += dfs(i, dfs) + 1;
                vis[i] = false;
                add(res, sub(get<1>(f[i]), quick_pow(2, m - tree_edge_sum[i] - 1)));
            }
        }

        get<0>(f[u]) = quick_pow(2, edge_num[u]);
        get<1>(f[u]) = quick_pow(2, (edge_num[u] + node_num[u])) - get<0>(f[u]);
        for (auto i : new_graph.begin(u)) {
            if (!vis[i]) {
                get<1>(f[u]) = add_(sub(get<0>(f[u]), get<1>(f[i])), sub(get<1>(f[u]), add_(2 * get<0>(f[i]), get<1>(f[i]))));
                get<0>(f[u]) = sub(get<0>(f[u]), 2 * get<0>(f[i]));
            }
        }

        return tree_edge_sum[u];
    };

    uint rt = rnd() % cnt2;
    vis[rt] = true;
    tree_edge_sum[rt] += dfs(rt, dfs) + 1;
    add(res, get<1>(f[rt]));

    return res;
}
 */