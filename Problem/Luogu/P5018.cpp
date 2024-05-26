//
// Created by kibi on 2022/10/21.
//
#include <bits/stdc++.h>
using namespace std;

class Solution{
    const long long v1 = 999999751, v2 = 299999827, v3 = 100000007, v4 = (long long)89999794200117649, v5 = (long long)999999786000011449;
    unsigned long long hal1[1000005], har1[1000005], hal2[1000005], har2[1000005];
    long long n, siz[1000005], *val, *ls, *rs;
    void dfs(long long x, long long fa){
        ls[x]?dfs(ls[x], x):void();
        rs[x]?dfs(rs[x], x):void();
        siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
        if(siz[ls[x]] == siz[rs[x]] && hal1[ls[x]] == har1[rs[x]] && hal2[ls[x]] == har2[rs[x]]){
            ans = max(ans, siz[x]);
        }
        hal1[x] = hal1[ls[x]] * v1 + val[x] * v2 + hal1[rs[x]] * v3;
        hal2[x] = hal2[ls[x]] * v1 + val[x] * v2 + hal2[rs[x]] * v3;
        hal1[x] = hal1[x] % v4;
        hal2[x] = hal2[x] % v5;
        har1[x] = har1[rs[x]] * v1 + val[x] * v2 + har1[ls[x]] * v3;
        har2[x] = har2[rs[x]] * v1 + val[x] * v2 + har2[ls[x]] * v3;
        har1[x] = har1[x] % v4;
        har2[x] = har2[x] % v5;
    }
public:
    long long ans;
    Solution(long long n, long long *valT, long long *lsT, long long *rsT){
        this -> n = n, val = valT, ls = lsT, rs = rsT;
        dfs(1, -1);
    }
};

void read(long long &x);

int main(){
    static long long n, val[1000005], ls[1000005], rs[1000005];
    read(n);
    for(int i = 1; i <= n; i++){
        read(val[i]);
    }
    for(int i = 1; i <= n; i++){
        read(ls[i]), read(rs[i]);
        ls[i] == -1 ? ls[i] = 0:0;
        rs[i] == -1 ? rs[i] = 0:0;
    }
    static Solution solve(n, val, ls, rs);
    printf("%lld", solve.ans);
}

void read(long long &x){
    static long long s;
    static int w, c;
    s = 0, w = 1, c = getchar();
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