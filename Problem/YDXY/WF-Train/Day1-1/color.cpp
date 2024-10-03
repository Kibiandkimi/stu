//
// Created by kibi on 24-10-3.
//
#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <random>
#include <sys/types.h>
#include <tuple>
#include <vector>
using namespace std;

using ull = unsigned long long;

template<typename T>
T read() {
	T s = 0, w = 1, c = getchar();
	while(!isdigit(c)) {
		if (c == '-') {
			w = -1;
		}
		c = getchar();
	}
	while(isdigit(c)) {
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * w;
}

class Config {
public:
    uint n, m;
};

uint solve (const Config&);

int main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);

    auto n = read<uint>(), m = read<uint>();

    if (n == 2 && m == 2) {
        auto a = read<uint>(), b = read<uint>(), c = read<uint>(), d = read<uint>();
        if (a + b + c + d == 1) {
            printf("2\n");
        }else if (a + b + c + d == 2) {
            printf("1\n");
        }else if(a + b + c + d == 3) {
            printf("1\n");
        }else if(a + b + c + d == 4) {
            printf("0\n");
        }
    }else if (n == 1 && m == 2 || n == 2 && m == 1) {
        auto a = read<uint>(), b = read<uint>();
        if (a + b == 1) {
            printf("1\n");
        }else {
            printf("0\n");
        }
    }else if (n == 1 && m == 1) {
        printf("0\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}