//
// Created by kibi on 23-8-13.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    class Tools{
    public:
        static void generator(int n, int m, int *in){
            static mt19937 rnd(random_device{}());
            int cnt = 0;
            for(int i = 1; i <= m; i++){
                in[cnt++] = (int)(rnd() % n);
            }
        }
    };

    const int N = 1e7;

    class Graph{
        vector<int> data[N+5];
    public:
        void add_edge(int u, int v, bool flag = false){
            data[u].emplace_back(v);
            flag ? (data[v].emplace_back(u)) : (void)(nullptr);
        }
    };

    static Graph graph;

    static int data[4 * N + 5];

    Tools::generator(N, 2*N, data);

    for(int i = 0; i < 2*N; i+=2){
        graph.add_edge(data[i], data[i+1]);
    }
}