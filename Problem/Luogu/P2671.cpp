//
// Created by kibi on 22-9-12.
//
#include <bits/stdc++.h>
using namespace std;
static const int mod = 10007;
int n, m, r[100005], sum[100005][2];
struct node{
    node(int s1, int s2){
        this -> s1 = s1, this -> s2 = s2;
    }
    long long s1, s2;
};
vector<node> g[100005][2];

void read(int &x);

int main(){
    read(n), read(m);
    for(int i = 1; i <= n; i++){
        read(r[i]);
    }
    for(int i = 1; i <= n; i++){
        int c;
        read(c);
        g[c][i%2].emplace_back(r[i]%mod, i%mod);
        sum[c][i%2] = (sum[c][i%2]+r[i])%mod;
    }
    long long finalAns = 0;
    for(int i = 1; i <= m; i++){
        for(int j = 0; j < 2; j++){
            long long ans1 = 0, ans2 = 0;
            int sg = g[i][j].size();
            for(auto k : g[i][j]) {
                ans1 = (ans1 + k.s1*k.s2*(sg-1))%mod;
                ans2 = (ans2 + k.s2 * ((sum[i][j]-k.s1)<0?(sum[i][j]-k.s1+mod):(sum[i][j]-k.s1)))%mod;
            }
            finalAns = (finalAns + ans1 + ans2) % mod;
        }
    }
    printf("%lld", finalAns);
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s*10 + c-'0';
        c = getchar();
    }
    x = s*w;
}