//
// Created by kibi on 2022/10/24.
//
#include <bits/stdc++.h>
using namespace std;

const int Size = 1000005, mod = 998244353;

class Tree{
    int tr[Size];
public:
    void add(int u, int v){
        for(int i = u; i < Size; i += i&(-i)){
            tr[i] += v;
        }
    }
    int query(int u){
        int res = 0;
        for(int i = u; i; i -= i&(-i)){
            res += tr[i];
        }
        return res;
    }
};

void read(int &x);

int main(){
    static int n, raw[1000005], prod[1000005];
    static Tree tree;
    prod[0] = 1;
    read(n);
    for(int i = 1; i <= n; i++){
        read(raw[i]);
        tree.add(i, 1);
        prod[i] = (int)(((long long)prod[i-1] * i) % mod);
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        ans = (int)(((long long)tree.query(raw[i]-1) * prod[n-i] + ans) % mod);
        tree.add(raw[i], -1);
    }
    printf("%d", (ans+1)%mod);
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