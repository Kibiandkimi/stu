//
// Created by Kibi on 24-5-26.
//
// TODO 24-5-26
#include <bits/stdc++.h>
using namespace std;

int main(){
    static auto read = [](int &x){
        int s = 0, w = 1, c = getchar();
        while (c < '0' || '9' < c){
            if (c == '-'){
                w = -1;
            }
            c = getchar();
        }
        while ('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        x = s * w;
    };

    class Graph{
        class Edge{
        public:
            Edge *nxt;
            int v, w;
        };

        vector<Edge*> head;

    public:
        explicit Graph(int n):head(n){}

        void add_edge(int u, int v, int w, bool flag = false){
            head[u] = new Edge{head[u], v, w};
            return flag ? add_edge(v, u, w) : void();
        }

        Edge* begin(int &u){
            return head[u];
        }
    };

    static int n, k, rt;
    read(n);

    static Graph graph(n);
    for(int i = 1; i < n; i++){
        static int u, v, w;
        read(u), read(v), read(w);
        u--, v--;
        graph.add_edge(u, v, w, true);
    }

    read(k);

    rt = int(random_device{}() % n);

    static auto solve = [](){
        static int ans;
        static stack<int> stk;
        static vector<int> siz(n);
        static vector<bool> vis(n);

        static auto init_siz = [](){};
        static auto get_barycentre = [](int u, int n){
            static int res;
            static stack<tuple<int, int, int>> stk; // 0->u, 1->fa, 2->stat

            res = -1;
            stk.emplace(u, -1, 0);
            while(!stk.empty()){
                auto [now, fa, stat] = stk.top();
                stk.pop();
                switch(stat){
                    case 0:
                        siz
                }
            }
            return res;
        };
        static auto calc = [](int u){};

        init_siz();

        ans = 0;
        stk.emplace(rt);
        while(!stk.empty()){
            static int now, barycentre;

            now = stk.top();
            stk.pop();
            barycentre = get_barycentre(now, siz[now]);
            calc(now);
            vis[barycentre] = true;

            for (auto i = graph.begin(now); i; i = i->nxt){
                if(!vis[i->v]){
                    stk.emplace(i->v);
                }
            }
        }
        return ans;
    };

    int ans = solve();
    printf("%d\n", ans);
}