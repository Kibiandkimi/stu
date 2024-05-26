//
// Created by kibi on 23-11-17.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    static mt19937 rnd(random_device{}());

    auto read = [](initializer_list<int*> x){
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

        for(auto &i : x){
            read(*i);
        }
    };

    auto rand = [](int val){
        return (int)((rnd() % val + val) % val);
    };

    class Graph{
        class Edge{
        public:
            int v;
            Edge *nxt;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, bool flag = false){
            head[u] = new Edge{v, head[u]};
            flag ? add_edge(v, u) : void(0);
        }

        Edge* begin(int u){
            return head[u];
        }
    };

    static int n, m, k;
    read({&n, &m, &k});

    static Graph graph(n);

    for(int i = 0; i < m; i++){
        int u, v;
        read({&u, &v});
        u--, v--;
        graph.add_edge(u, v, true);
    }

    static int res = 0;
    static vector<int> ans;

    auto work = [](int rt, bool *vis, bool *ins){
        stack<int> stk;
        stk.emplace(rt);
        while (!stk.empty()) {
            int u = stk.top();
            stk.pop();
            for(auto i = graph.begin(u); i; i = i->nxt){
                if(!ins[i->v]) {
                    stk.emplace(i->v);
                    ins[i->v] = true;
                }
            }
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            res++;
            ans.emplace_back(u);
            for (auto i = graph.begin(u); i; i = i->nxt) {
                vis[i->v] = true;
                for (auto j = graph.begin(i->v); j; j = j->nxt) {
                    vis[j->v] = true;
                }
            }
        }
    };

    bool vis[n], ins[n];
    memset(vis, 0, sizeof vis);
    memset(ins, 0, sizeof ins);

    int rt = rand(n);
    work(rt, vis, ins);

    for(int id = 0; id < n; id++) {
        if(vis[id]){
            continue;
        }
        work(id, vis, ins);
    }

    printf("%d\n", res);
    for (auto &i : ans) {
        printf("%d ", i + 1);
    }

}