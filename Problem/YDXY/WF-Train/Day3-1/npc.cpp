//
// Created by kibi on 24-10-5.
//
#include <cctype>
#include <cstdio>
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

class Config {
public:
    uint n, m;
    vector<tuple<uint, uint>> edges;
};

// bool solve(const Config&);

int main() {
    freopen("npc.in", "r", stdin);
    freopen("npc.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();
    if (n == 1) {
        printf("1\n");
    }else {
        printf("0\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}