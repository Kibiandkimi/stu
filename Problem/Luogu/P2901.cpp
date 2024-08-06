//
// Created by kibi on 24-7-27.
//
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
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, int w){
            head[u] = new Edge{v, w, head[u]};
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    int n, m, k;
    read(n), read(m), read(k);

    Graph graph(n);
    for(int i = 0; i < m; i++){
        int u, v, d;
        read(u), read(v), read(d);
        u--, v--;
        (u < v) ? swap(u, v) : void(0);
        graph.add_edge(u, v, d);
    }

    vector<int> ans;

    using T = tuple<int, int>;

    class Cmp{
    public:
        bool operator () (const T &a, const T &b){
            return get<0>(a) + get<1>(a) > get<0>(b) + get<1>(b); // TODO maybe wrong A*
        }
    };

    priority_queue<T, vector<T>, Cmp> q;
    q.emplace(n - 1, 0);

    while(!q.empty()){
        auto [u, step] = q.top();
        q.pop();

        for(auto i = graph.begin(u); i; i = i->nxt){
            q.emplace(i->v, step + i->w);
        }

        if(u == 0){
            ans.emplace_back(step);
            if(ans.size() == k){
                break;
            }
        }
    }

    while(ans.size() < k){
        ans.emplace_back(-1);
    }

    for(auto &i : ans){
        printf("%d\n", i);
    }
}