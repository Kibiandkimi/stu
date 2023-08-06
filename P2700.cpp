//
// Created by kibi on 23-7-26.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

void read(int&);

int main(){

    class Edge{
    public:
        int u, v, w;
        static bool cmp(Edge a, Edge b){
            return a.w > b.w;
        }
    };

    class Bcj{
    public:
        int id{};
        Bcj* fa;
        Bcj* find(){
            if(fa != this){
                fa = fa -> find();
            }
            return fa;
        }

        Bcj(){
            fa = this;
        }
    };


    static Bcj bcj[N + 5];
    static Edge edge[N+5];

    int n, k;
    read(n), read(k);

    static bool bad[N + 5];

    for(int i = 1; i <= k; i++){
        int x;
        read(x);
        bad[x] = true;
    }

    long long ans = 0;

    for(int i = 1; i < n; i++){
        int u, v, w;
        read(u), read(v), read(w);
        edge[i] = {u, v, w};
        ans += w;
    }

    sort(edge+1, edge+n, Edge::cmp);

    for(int i = 0; i < n; i++){
        bcj[i].id = i;
    }

    for(int i = 1; i < n; i++){
        int u = edge[i].u, v = edge[i].v;
        int _u = bcj[u].find() -> id, _v = bcj[v].find() -> id;
        if(!(bad[_u] && bad[_v])){
            ans -= edge[i].w;
            bad[_u] = bad[_v] = (bad[_u] || bad[_v]);
            bcj[_u].fa = bcj[_v].fa;
        }
    }

    printf("%lld\n", ans);

}

void read(int &x){
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