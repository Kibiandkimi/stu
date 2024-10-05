//
// Created by kibi on 24-10-4.
//
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stack>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <tuple>
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

class Config {
public:
    uint n, q;
    string s;
    vector<uint> queries;
};

vector<bool> solve(const Config &);

int main() {
    freopen("expr.in", "r", stdin);
    freopen("expr.out", "w", stdout);

    auto n = read<uint>(), q = read<uint>();
    Config config{n, q, string(), vector<uint>(q)};
    config.s.reserve(n);
    {
        auto judge = [](uint c) {
            return isdigit(c) || c == '[' || c == ']' || c == '(' || c == ')' || c == '!' || c == '^' || c == '&' || c == '|';
        };
        uint c = getchar();
        while (!judge(c)) {
            c = getchar();
        }
        while (judge(c)) {
            config.s.push_back(c);
            c = getchar();
        }
    }
    for (auto &i : config.queries) {
        i = read<uint>();
    }
    auto ans = solve(config);
    for (auto i : ans) {
        printf(i ? "True\n" : "False\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

class Interval {
public:
    uint l{1}, r{1'000'000'000};
};

// Not impl
/*
class MultiInterval {
public:
    vector<Interval> intervals;

    void operator ! () const {
        vector<uint> seg;
        seg.reserve(2 * intervals.size() + 2);
        for (auto &i : intervals) {
            seg.push_back(i.l);
            seg.push_back(i.r);
        }
        uint i = 0;
        if (seg[0] != 1) {
            seg.insert(seg.begin(), 1);
        }else {
            i++;
        }
        uint mxi = seg.size();
        if (seg.back() != 1'000'000'000) {
            seg.push_back(1'000'000'000);
        }else {
            mxi--;
        }
        for (; i <= mxi; i += 2) {

        }
    }
};
*/

class Query {
public:
    uint id, x, ans;
};

class Node {
public:
    enum Type {
        Or,
        Xor,
        And,
        Not,
        Num
    };
    Node *ls, *rs;
    bool flag;
    uint x;
    Type type;
};

Node *calc(string::const_iterator &i) {
    stack<Node *> stk;
    while (*i != ')') {
        if (*i == '[') {
            uint temp = 0;
            ++i;
            while (*i != ']') {
                temp = temp * 10 + (*i - '0');
                ++i;
            }
            auto new_node = new Node{nullptr, nullptr, false, temp, Node::Num};
            stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
        } else if (*i == '(') {
            ++i;
            auto new_node = calc(i);
            stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
        } else if (*i == '!') {
            auto new_node = new Node{nullptr, nullptr, false, 0, Node::Not};
            stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
        } else if (*i == '&' || *i == '^' || *i == '|') {
            auto new_node = new Node{
                    nullptr,
                    nullptr,
                    false,
                    0,
                    *i == '&' ? Node::And : *i == '^' ? Node::Xor
                                                      : Node::Or};
            Node *pre = nullptr;
            while (!stk.empty() && (stk.top()->type > new_node->type || stk.top()->flag)) {
                pre = stk.top();
                stk.pop();
            }
            new_node->ls = pre;
            stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
        } else {
            throw runtime_error("What?! It's impossible! Got" + *i + string{static_cast<char>(*i)});
        }
        ++i;
    }
    Node *rt = nullptr;
    while (!stk.empty()) {
        rt = stk.top();
        stk.pop();
    }
    rt->flag = true;
    return rt;
}

vector<bool> solve(const Config &config) {
    if (!any_of(config.s.begin(), config.s.end(), [](uint c) { return c == '&' || c == '|'; })) {
        vector<Interval> intervals;
        vector<uint> numbers;
        numbers.push_back(1);
        numbers.push_back(1'000'000'000);
        bool flag = false;
        for (auto i = config.s.begin(); i != config.s.end(); ++i) {
            if (*i == '[') {
                uint temp = 0;
                ++i;
                while (*i != ']') {
                    temp = temp * 10 + (*i - '0');
                    ++i;
                }
                if (!flag) {
                    intervals.push_back(Interval{temp, 1'000'000'000});
                    numbers.push_back(temp);
                } else {
                    intervals.push_back(Interval{1, temp - 1});
                    numbers.push_back(temp - 1);
                    flag = false;
                }
            } else if (*i == '!') {
                flag = !flag;
            }
        }
        vector<uint> segments;
        for (auto &i : intervals) {
            segments.emplace_back(i.l);
            segments.emplace_back(i.r + 1);
        }
        sort(segments.begin(), segments.end());
        vector<Query> queries(config.q);
        for (uint i = 0; i < config.q; i++) {
            queries[i] = {i, config.queries[i]};
        }
        sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) { return a.x < b.x; });
        uint now = 0;
        bool pre = false;
        for (auto &i : queries) {
            while (now < segments.size() && segments[now] <= i.x) {
                pre = !pre;
                now++;
            }
            i.ans = pre;
        }
        sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) { return a.id < b.id; });
        vector<bool> res(config.q);
        for (uint i = 0; i < config.q; i++) {
            res[i] = queries[i].ans;
        }
        return res;
    }
    if (config.q == 1) {
        stack<Node *> stk;// for r chain
        for (auto i = config.s.begin(); i != config.s.end(); ++i) {
            if (*i == '[') {
                uint temp = 0;
                ++i;
                while (*i != ']') {
                    temp = temp * 10 + (*i - '0');
                    ++i;
                }
                auto new_node = new Node{nullptr, nullptr, false, temp, Node::Num};
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            } else if (*i == '(') {
                ++i;
                auto new_node = calc(i);
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            } else if (*i == '!') {
                auto new_node = new Node{nullptr, nullptr, false, 0, Node::Not};
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            } else if (*i == '&' || *i == '^' || *i == '|') {
                auto new_node = new Node{
                        nullptr,
                        nullptr,
                        false,
                        0,
                        *i == '&' ? Node::And : *i == '^' ? Node::Xor
                                                          : Node::Or};
                Node *pre = nullptr;
                while (!stk.empty() && (stk.top()->type > new_node->type || stk.top()->flag)) {
                    pre = stk.top();
                    stk.pop();
                }
                new_node->ls = pre;
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            }
        }
        Node *rt = nullptr;
        while (!stk.empty()) {
            rt = stk.top();
            stk.pop();
        }
        auto x = config.queries.front();
        auto dfs = [x](Node *node, auto &&dfs) -> bool {
            switch (node->type) {
                case Node::Num:
                    return x >= node->x;
                case Node::Not:
                    return !dfs(node->rs, dfs);
                case Node::And:
                    return dfs(node->ls, dfs) && dfs(node->rs, dfs);
                case Node::Xor:
                    return dfs(node->ls, dfs) ^ dfs(node->rs, dfs);
                case Node::Or:
                    return dfs(node->ls, dfs) || dfs(node->rs, dfs);
            }
        };
        auto res = dfs(rt, dfs);
        return {res};
    }
    if (config.n <= 10'000) {
        stack<Node *> stk;// for r chain
        for (auto i = config.s.begin(); i != config.s.end(); ++i) {
            if (*i == '[') {
                uint temp = 0;
                ++i;
                while (*i != ']') {
                    temp = temp * 10 + (*i - '0');
                    ++i;
                }
                auto new_node = new Node{nullptr, nullptr, false, temp, Node::Num};
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            } else if (*i == '(') {
                ++i;
                auto new_node = calc(i);
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            } else if (*i == '!') {
                auto new_node = new Node{nullptr, nullptr, false, 0, Node::Not};
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            } else if (*i == '&' || *i == '^' || *i == '|') {
                auto new_node = new Node{
                        nullptr,
                        nullptr,
                        false,
                        0,
                        *i == '&' ? Node::And : *i == '^' ? Node::Xor
                                                          : Node::Or};
                Node *pre = nullptr;
                while (!stk.empty() && (stk.top()->type > new_node->type || stk.top()->flag)) {
                    pre = stk.top();
                    stk.pop();
                }
                new_node->ls = pre;
                stk.emplace(!stk.empty() ? stk.top()->rs = new_node : new_node);
            }
        }
        Node *rt = nullptr;
        while (!stk.empty()) {
            rt = stk.top();
            stk.pop();
        }
        // No time to do!
        /*
        auto dfs = [](Node *node, auto &&dfs) -> MultiInterval {
            switch (node->type) {
                case Node::Num:
                    return {{Interval{node->x, 1'000'000'000}}};
                case Node::Not:
                    return !dfs(node->rs, dfs);
                case Node::And:
                    return dfs(node->ls, dfs) && dfs(node->rs, dfs);
                case Node::Xor:
                    return dfs(node->ls, dfs) ^ dfs(node->rs, dfs);
                case Node::Or:
                    return dfs(node->ls, dfs) || dfs(node->rs, dfs);
            }
        };
        auto res = dfs(rt, dfs);
         */

        // use precious sol
        vector<bool> res;
        res.reserve(config.queries.size());
        for (auto &i : config.queries) {
            auto dfs = [i](Node *node, auto &&dfs) -> bool {
                switch (node->type) {
                    case Node::Num:
                        return i >= node->x;
                    case Node::Not:
                        return !dfs(node->rs, dfs);
                    case Node::And:
                        return dfs(node->ls, dfs) && dfs(node->rs, dfs);
                    case Node::Xor:
                        return dfs(node->ls, dfs) ^ dfs(node->rs, dfs);
                    case Node::Or:
                        return dfs(node->ls, dfs) || dfs(node->rs, dfs);
                }
            };
            res.push_back(dfs(rt, dfs));
        }
    }
}