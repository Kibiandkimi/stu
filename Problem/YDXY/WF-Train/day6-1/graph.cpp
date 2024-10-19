//
// Created by kibi on 24-10-8.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
#include <set>
#include <stack>
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

uint readc() {
    uint c = getchar();
    while (c != 'R' && c != 'B') {
        c = getchar();
    }
    return c;
}

enum Color {
    red = 0,
    blue = 1
};

using Edge = tuple<uint, uint>;
class Config {
public:
    uint n, m;
    vector<Edge> edges;
    vector<uint> val, aim_val;
    vector<Color> color, aim_color;
};

bool solve(const Config &);

int main() {
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);

    auto T = read<uint>();
    while (T--) {
        auto n = read<uint>(), m = read<uint>();
        Config config{
                n,
                m,
                vector<Edge>(m),
                vector<uint>(n),
                vector<uint>(n),
                vector<Color>(n),
                vector<Color>(n)
        };
        for (auto &i : config.edges) {
            i = { read<uint>() - 1, read<uint>() - 1};
        }
        for (auto &i : config.val) {
            i = read<uint>();
        }
        for (auto &i : config.color) {
            i = readc() == 'R' ? red : blue;
        }
        for (auto &i : config.aim_val) {
            i = read<uint>();
        }
        for (auto &i : config.aim_color) {
            i = readc() == 'R' ? red : blue;
        }
        auto ans = solve(config);
        printf(ans ? "YES\n" : "NO\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

class DSUNode {
    DSUNode *fa;
public:
    const uint id;
    explicit DSUNode(uint id = 0) : id(id), fa(this){}

    DSUNode* find() {
        if (fa != this) {
            fa = fa->find();
        }
        return fa;
    }

    static void merge(DSUNode *a, DSUNode *b) {
        if (a->find() != b->find()) {
            a->find()->fa = b->find();
        }
    }
};

class Graph {
    class Node {
    public:
        uint v;
        Node *nxt;
    };
    vector<Node *> head;

public:
    explicit Graph(uint n) : head(n) {}

    void add_edge(uint u, uint v, bool flag = false) {
        head[u] = new Node{v, head[u]};
        flag ? add_edge(v, u) : static_cast<void>(0);
    }

    const Node *begin(uint u) {
        return head[u];
    }
};

bool solve(const Config &config) {
    // ah

    Graph graph(config.n);
    vector<DSUNode*> nodes;
    nodes.reserve(config.n);
    for (uint i = 0; i < config.n; i++) {
        nodes.push_back(new DSUNode(i));
    }
    for (auto &i : config.edges) {
        graph.add_edge(get<0>(i), get<1>(i), true);
        DSUNode::merge(nodes[get<0>(i)], nodes[get<1>(i)]);
    }

    vector<uint> reflect(config.n);

    auto calc = [&config, &graph, &reflect](vector<uint> &node) {

        // check color
        uint res = 0;
        for (auto &i : node) {
            res += config.color[i] != config.aim_color[i];
        }
        if (res & 1) {
            return false;
        }

        // check val
        map<uint, int> mp;
        for (auto &i : node) {
            mp[config.val[i]]++;
            mp[config.aim_val[i]]--;
        }
        if (any_of(mp.begin(), mp.end(), [&](auto it) {return it.second != 0;})) {
            return false;
        }

        // paint
        vector<bool> vis(node.size());
        vector<bool> pre_vis(node.size());
        stack<uint> stk;
        vis[reflect[node.front()]] = true;
        stk.push(node.front());
        uint cnt = 0;
        while (!stk.empty()) {
            cnt++;
            auto u = stk.top();
            stk.pop();
            for (auto j = graph.begin(u); j; j = j->nxt) {
                if (pre_vis[reflect[j->v]]) {
                    continue;
                }
                pre_vis[reflect[j->v]] = true;
                for (auto k = graph.begin(j->v); k; k = k->nxt) {
                    if (vis[reflect[k->v]]) {
                        continue;
                    }
                    vis[reflect[k->v]] = true;
                    stk.push(k->v);
                }
            }
        }
        if (cnt == node.size()) {
            return true;
        }
        set<uint> st;
        for (uint i = 0; i < node.size(); i++) {
            if (vis[i]) {
                st.insert(node[i]);
            }
        }

        // check if two set have the same aiming_val
        // bool flag = false;
        multiset<uint> st1;
        for (auto &i : node) {
            if (st.find(i) != st.end()) {
                st1.insert(i);
            }
        }
        for (auto &i : node) {
            if (st.find(i) == st.end()) {
                if (st1.find(config.aim_val[i]) != st1.end()) {
                    return true;
                }
            }
        }

        bool flag = false;
        res = 0;
        for (auto &i : st) {
            if (st1.find(config.aim_val[i]) != st1.end()) {
                st1.erase(config.aim_val[i]);
            }else {
                flag = !flag;
            }
            if (config.color[i] != config.aim_color[i]) {
                res++;
            }
        }

        if (res + flag & 1) {
            return false;
        }
        return true;
    };

    vector<vector<uint>> node_set;
    map<uint, uint> mp_node_set;

    for (auto &i : nodes) {
        if (mp_node_set.find(i->find()->id) != mp_node_set.end()) {
            reflect[i->find()->id] = node_set[mp_node_set[i->find()->id]].size();
            node_set[mp_node_set[i->find()->id]].push_back(i->id);
        }else {
            mp_node_set[i->find()->id] = node_set.size();
            node_set.push_back({i->id});
            reflect[i->find()->id] = 0;
        }
    }

    for (auto &i : node_set) {
        if (!calc(i)) {
            return false;
        }
    }

    return true;

    /*
    vector<Color> color = config.color;
    map<uint, vector<uint>> mp;
    uint cnt = 0;
    for (auto &i : config.val) {
        mp[i] = cnt++;
    }

    auto trans = [](Color a) {
        return a == red ? blue : red;
    };

    auto val = config.val, aim_val = config.aim_val;

    for (uint i = 0; i < config.n; i++) {
        if (val[i] == aim_val[i]) {
            continue;
        }
        if (nodes[mp[config.aim_val[i]]].find() != nodes[i].find()) {
            return false;
        }
        color[i] = trans(color[i]);
        color[graph.begin(i)->v] = trans(color[graph.begin(i)->v]);
        swap(val[i], val[graph.begin(i)->v]);
        mp[val[i]] = mp[graph.begin(i)->v];
    }

    vector<bool> vis(config.n);
    vector<uint> pre_vis(config.n);
    for (uint i = 0; i < config.n; i++) {
        stack<uint> stk;
        vis[i] = true;
        stk.push(i);
        uint res = 0;
        while (!stk.empty()) {
            if (color[i] != config.aim_color[i]) {
                res++;
            }
            auto u = stk.top();
            stk.pop();
            for (auto j = graph.begin(u); j; j = j->nxt) {
                if (pre_vis[j->v] == i) {
                    continue;
                }
                pre_vis[j->v] = i;
                for (auto k = graph.begin(j->v); k; k = k->nxt) {
                    if (vis[k->v]) {
                        continue;
                    }
                    vis[k->v] = true;
                    stk.push(k->v);
                }
            }
        }
        if (res & 1) {
            return false;
        }
    }
    return true;*/
}