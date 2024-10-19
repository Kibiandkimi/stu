//
// Created by Kibi on 24-7-15.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;

    auto read = [](ll &x){
        ll s = 0, w = 1, c = getchar();
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
    };

    class Node{
    public:
        ll a, b, d;
    };

    ll T;
    read(T);

    while(T--){
        ll n;
        read(n);

        Node node[n];
        for (auto &i : node){
            read(i.a), read(i.b);
            i.d = (i.a - i.b) / abs(i.a - i.b);
        }

        sort(node, node + n, [](Node &a, Node &b){return a.d != b.d ? a.d < b.d : a.d < 0 ? a.a < b.a : a.b > b.b;});

        ll s = 0, lst = 0;
        for(auto &i : node){
            s += i.a;
            lst = max(s, lst) + i.b;
        }

        printf("%lld\n", lst);
    }

}