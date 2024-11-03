//
// Created by kibi on 24-11-3.
//
#include <cctype>
#include <cstdio>
#include <set>
#include <stack>
#include <string>
#include <sys/types.h>
#include <tuple>
#include <vector>

template<typename T>
using vec = std::vector<T>;
using u32 = const unsigned int;
using u64 = const unsigned long long;
using ull = unsigned long long;

using std::tuple;

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
    u32 n, p;
    vec<std::string> lines;
};

enum class Res {
    Yes,
    No,
    ERR,
};

Res solve(const Config &);
Config parse_config(std::string line) {
    uint pos = 0, n = 0, p = 0;
    while (line[pos] != ' ') {
        n = n * 10 + line[pos] - '0';
        ++pos;
    }
    ++pos; // pos -> O
    ++pos; // pos -> (
    ++pos; // pos -> (num)
    if (line[pos] == '1') {
        return {n, p};
    }
    ++pos; // pos -> ^
    ++pos; // pos -> (n^num)
    while (line[pos] != ')') {
        p = p * 10 + line[pos] - '0';
        ++pos;
    }
    return {n, p};
}

int main() {
    uint T = read<uint>();
    while (T--) {
        std::string str;
        uint c = getchar();
        while (c != '\n') {
            str.push_back(static_cast<char>(c));
            c = getchar();
        }
        Config config = parse_config(move(str));
        for (uint i = 0; i < config.n; i++) {
            c = getchar();
            while (c != 'F' && c != 'E') { // skip unexpected chars
                c = getchar();
            }
            config.lines.emplace_back("");
            while (c != '\n' && c != '\r') {
                config.lines.back().push_back(static_cast<char>(c));
                c = getchar();
            }
        }
        auto res = solve(config);
        printf(res == Res::Yes ? "Yes\n" : res == Res::No ? "No\n"
                                                          : "ERR\n");
    }
    return 0;
}

class LoopConfig {
public:
    uint var, st, ed;
};

LoopConfig parse_loop(std::string line) {
    uint pos = 0, var, st, ed;
    ++pos; // pos -> ' '
    ++pos; // pos -> 'i'
    var = static_cast<unsigned char>(line[pos]);
    ++pos; // pos -> ' '
    ++pos; // pos -> st
    if (line[pos] == 'n') {
        st = -1;
        ++pos;
    } else {
        st = 0;
        while (line[pos] != ' ') {
            st = st * 10 + line[pos] - '0';
            ++pos;
        }
    } // pos -> ' '
    ++pos; // pos -> ed
    if (line[pos] == 'n') {
        ed = -1;
        ++pos;
    } else {
        ed = 0;
        while (isdigit(line[pos])) { // note that there is not a ' ' after a line
            ed = ed * 10 + line[pos] - '0';
            ++pos;
        }
    } // pos -> ' '
    return {var, st, ed};
}

enum class Stat {
    Const = 0,
    N = 1,
    Zero = -1,
};

Res solve(const Config &config) {
    std::stack<Stat> stk;
    std::stack<uint> var;
    std::set<uint> st;
    uint p = 0, mxp = 0, zero_num = 0;
    for (const auto &line : config.lines) {
        if (line[0] == 'E') {
            // deal with time complexity
            if (stk.empty()) {
                return Res::ERR;
            }
            if (zero_num) {
                if (static_cast<int>(stk.top()) == -1) {
                    zero_num--;
                }
            } else {
                p -= static_cast<int>(stk.top());
            }
            stk.pop();

            // deal with the name of var
            st.erase(var.top());
            var.pop();

        } else {
            auto loop = parse_loop(line);
            // basic impl
            /*
            if (loop.st == -1) {
                if (loop.ed == -1) { // n -> n => 1
                    stk.emplace(Stat::Const);
                } else { // n -> 1 => 0
                    stk.emplace(Stat::Zero);
                    zero_num++;
                }
            } else {
                if (loop.ed == -1) {
                    stk.emplace(Stat::N);
                    if (zero_num == 0) { // not in zero loop
                        p++;
                        mxp = std::max(mxp, p);
                    }
                } else {
                    if (loop.ed < loop.st) {
                        stk.emplace(Stat::Zero);
                        zero_num++;
                    } else {
                        stk.emplace(Stat::Const);
                    }
                }
            }
            */
            // better impl
            if (loop.st > loop.ed) {
                stk.emplace(Stat::Zero);
                zero_num++;
            } else if (loop.ed - loop.st > 100){
                stk.emplace(Stat::N);
                if (zero_num == 0) {
                    // not in zero loop
                    p++;
                    mxp = std::max(mxp, p);
                }
            } else {
                stk.emplace(Stat::Const);
            }

            if (st.find(loop.var) != st.end()) {
                return Res::ERR; // loop var already exists
            }
            var.push(loop.var);
            st.insert(loop.var);
        }
    }
    if (!stk.empty()) {
        return Res::ERR; // not enough 'E'
    }
    if (mxp != config.p) {
        return Res::No; // wrong time complexity
    }
    return Res::Yes;
}


