//
// Created by Lenovo on 24-4-18.
//
// TODO 24-4-18
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](int &x){
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
    };

    class Graph{
        class Edge{
        public:
            int v, w;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n + 1, nullptr){}

        void add_edge(const int &u, const int &v, const int &w, bool flag = false){
            head[u] = new Edge{v, w, head[u]};
            return flag ? add_edge(v, u, w) : void();
        }

        Edge* begin(int u) const{
            return head[u];
        }
    };

    int n, k;
    read(n);

    Graph graph(n);
    for(int i = 1; i < n; i++){
        int u, v, w;
        read(u), read(v), read(w);
        graph.add_edge(u, v, w, true);
    }

    read(k);


}